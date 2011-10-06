/*
 * =====================================================================================
 *
 *       Filename:  list_head.c
 *
 *    Description:  abstract the behavior of kernel double link list
 *
 *        Version:  1.0
 *        Created:  12/18/2010 10:53:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>

struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
       struct list_head name = LIST_HEAD_INIT(name)

#define  INIT_LIST_HEAD(ptr)  do {  \
    (ptr)->next = (ptr); \
    (ptr)->prev = (ptr);  \
}while(0)

#define  list_for_each(pos, head)  \
    for(pos = (head)->next; pos != (head);  \
    pos = pos->next)

#define  list_for_each_entry(pos, head, member)  \
    for(pos=list_entry((head)->next, typeof(*pos), member);  \
         &pos->member != (head);  \
           pos = list_entry(pos->member.next, typeof(*pos), member))

#define  list_entry(ptr, type, member)  \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

static  inline  void  __list_add(struct  list_head  *new,
                                 struct  list_head  *prev,
                                 struct  list_head  *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static  inline  void  list_add(struct  list_head  *new,  struct  list_head  *head)
{
    __list_add(new, head, head->next);
}

/* use example */
struct kool_list
{
    struct list_head list;
    int              num;
};

struct kool_list list[10];

static LIST_HEAD(one_list);

int main()
{
    int i;
    struct kool_list *lptr;
    
    for(i = 0; i<10; i++)
    {
        list[i].num = i;
        list_add(&list[i].list, &one_list);
    }

    list_for_each_entry(lptr, &one_list, list)
    {
        printf("number is %d\n", lptr->num);
    }
    return 0;
}
