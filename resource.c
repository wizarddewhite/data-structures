/*
 * =====================================================================================
 *
 *       Filename:  resource.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/29/2011 09:06:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#define IORESOURCE_MEM		0x00000200

#define EBUSY    16
#define EINVAL   22

typedef unsigned long resource_size_t;

/*
 * Resources are tree-like, allowing
 * nesting etc..
 */
struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	struct resource *parent, *sibling, *child;
};

struct resource_constraint {
	resource_size_t min, max, align;
	resource_size_t (*alignf)(void *, const struct resource *,
			resource_size_t, resource_size_t);
	void *alignf_data;
};

struct resource iomem_resource = {
	.name	= "PCI mem",
	.start	= 0,
	.end	= 999,
	.flags	= IORESOURCE_MEM,
};

/* Return the conflict entry if you can't request it */
static struct resource * __request_resource(struct resource *root, struct resource *new)
{
	resource_size_t start = new->start;
	resource_size_t end   = new->end;
	struct resource *tmp, **p;

	if (end < start)
		return root;
	if (start < root->start)
		return root;
	if (end > root->end)
		return root;

	p = &root->child;
	for (;;) {
		tmp = *p;
		if (!tmp || tmp->start > end) {
			new->sibling = tmp;
			*p = new;
			new->parent = root;
			return NULL;
		}
		p = &tmp->sibling;
		if (tmp->end < start)
			continue;
		return tmp;
	}
}

static int __release_resource(struct resource *old)
{
	struct resource *tmp, **p;

	p = &old->parent->child;
	for (;;) {
		tmp = *p;
		if (!tmp)
			break;
		if (tmp == old) {
			*p = tmp->sibling;
			old->parent = NULL;
			return 0;
		}
		p = &tmp->sibling;
	}
	return -EINVAL;
}


/**
 * request_resource_conflict - request and reserve an I/O or memory resource
 * @root: root resource descriptor
 * @new: resource descriptor desired by caller
 *
 * Returns 0 for success, conflict resource on error.
 */
struct resource *request_resource_conflict(struct resource *root, struct resource *new)
{
	struct resource *conflict;

	//write_lock(&resource_lock);
	conflict = __request_resource(root, new);
	//write_unlock(&resource_lock);
	return conflict;
}


/**
 * request_resource - request and reserve an I/O or memory resource
 * @root: root resource descriptor
 * @new: resource descriptor desired by caller
 *
 * Returns 0 for success, negative error code on error.
 */
int request_resource(struct resource *root, struct resource *new)
{
	struct resource *conflict;

	conflict = request_resource_conflict(root, new);
	return conflict ? -EBUSY : 0;
}

/**
 * release_resource - release a previously reserved resource
 * @old: resource pointer
 */
int release_resource(struct resource *old)
{
	int retval;

	//write_lock(&resource_lock);
	retval = __release_resource(old);
	//write_unlock(&resource_lock);
	return retval;
}

struct resource * __request_region(struct resource *parent, 
		resource_size_t start, resource_size_t n,
		const char *name, int flags)
{
	struct resource *res = malloc(sizeof(*res));

	if (!res)
		return NULL;

	res->name = name;
	res->start = start;
	res->end = start + n - 1;
	//res->flags = IORESOURCE_BUSY;
	res->flags |= flags;

	for (;;) {
		struct resource *conflict;

		conflict = __request_resource(parent, res);
		if (!conflict)
			break;
		if (conflict != parent) {
			parent = conflict;
			//if (!(conflict->flags & IORESOURCE_BUSY))
				continue;
		}

		free(res);
		res = NULL;
		break;
	}

	return res;
}

void __release_region(struct resource *parent, resource_size_t start,
		resource_size_t n)
{
	struct resource **p;
	resource_size_t end;
	int count = 0;

	p = &parent->child;
	end = start + n - 1;

	for(;;) {
		struct resource *res = *p;

		if (!res)
			break;
		if (res->start > start)
			break;
		if (res->start <= start && res->end >= end) {
			if (res->child) {
				p = &res->child;
				count = 0;
				continue;
			}
			if (res->start != start || res->end != end)
				break;
			*p = res->sibling;
			free(res);
			return;
		}
		p = &res->sibling;
		count++;
	}

	printf("Warning: Trying to free nonexistent resource"
			"<%ld-%ld>, %d times iteration\n", 
			start, end, count);
}

void show_child_first(struct resource *res, int width) {
	if (!res)
		return;
	printf("%*s%ld-%ld\n", width*4, "", res->start, res->end);
	show_child_first(res->child, width+1);
	show_child_first(res->sibling, width);
}

void show(struct resource *root) {
	printf("------------------ Dump the resource tree ----------------\n");
	printf("Total resource is %ld-%ld\n", root->start, root->end);
	show_child_first(root->child, 0);
}

static int __find_resource(struct resource *root, struct resource *old,
		struct resource *new,
		resource_size_t size,
		struct resource_constraint *constraint)
{
	struct resource *this = root->child;
	struct resource tmp = *new, avail, alloc;

	//tmp.flags = new->flags;
	tmp.start = root->start;

	/*
	 * Skip past an allocated resource that starts at 0, since the assignment
	 * of this->start - 1 to tmp->end below would cause an underflow.
	 */
//	if (this && this->start == root->start) {
//		tmp.start = (this == old) ? old->start : this->end + 1;
//		this = this->sibling;
//	}
	for(;;) {
		if (this)
			tmp.end = (this == old) ? this->end : this->start - 1;
		else
			tmp.end = root->end;

		if (tmp.end < tmp.start)
			goto next;

		if (tmp.end - tmp.start + 1 >= size) {
			printf("--%lu-%lu meet requirement\n", tmp.start, tmp.end);
			return 0;
		}

next:		if (!this || this->end == root->end)
			break;
		if (this != old)
			tmp.start = this->end + 1;
		this = this->sibling;
	}

	return -EBUSY;
}

void test_request_resource()
{
	struct resource res[10] = {{0}, };
	res[0].start = 10;
	res[0].end   = 90;
	res[1].start = 150;
	res[1].end   = 190;
	res[2].start = 20;
	res[2].end   = 80;
	res[3].start = 30;
	res[3].end   = 50;
	res[4].start = 55;
	res[4].end   = 60;

	request_resource(&iomem_resource, &res[0]);
	request_resource(&iomem_resource, &res[1]);
	request_resource(&res[0], &res[2]);
	request_resource(&res[2], &res[3]);
	request_resource(&res[2], &res[4]);
	show(&iomem_resource);
}

void test_request_region()
{
	__request_region(&iomem_resource, 0, 70, NULL, 0);
	__request_region(&iomem_resource, 100, 900, NULL, 0);
	__request_region(&iomem_resource, 80, 10, NULL, 0);
	__request_region(&iomem_resource, 20, 50, NULL, 0);
	__request_region(&iomem_resource, 30, 20, NULL, 0);
	__request_region(&iomem_resource, 55, 5, NULL, 0);
	__request_region(&iomem_resource, 60, 5, NULL, 0);
	__request_region(&iomem_resource, 65, 5, NULL, 0);

	show(&iomem_resource);

}

void test_release()
{
	//__release_region(&iomem_resource, 30, 20);
	//show(&iomem_resource);

	__release_region(&iomem_resource, 50, 10);
	show(&iomem_resource);

}

void test_request()
{
	if(!__request_region(&iomem_resource, 1000, 20, NULL, 0))
		printf("Error! 1000, 20\n");

	if(!__request_region(&iomem_resource, 80, 20, NULL, 0))
		printf("Error! 80, 20\n");

	return;
}

int main()
{
	struct resource res;

	test_request_region();
//	test_release();

	__find_resource(&iomem_resource, iomem_resource.child->sibling, &res, 
			40, NULL);
	
	return 0;
}
