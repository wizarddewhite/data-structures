// =====================================================================================
// 
//       Filename:  maze_recur.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/27/2010 09:06:31 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================

#include<stdio.h>
#include<stdlib.h>
#define M 16
#define N 16
typedef struct mark//0908060201080101020308000802????03????¡§??08¡§¡è0401
{
    int x;
    int y;
}mark;

typedef struct Element//"0908"09030809090105010202020203050305
{
    int x,y; //x0404,y0904
    int d; //d0300060305040802??¡è0403¡§¡ã
}Element;

typedef struct LStack //09050903
{
    Element elem;
    struct LStack *next;
}LStack, *PLStack;

/*************090302040805****************/
int InitStack(PLStack &S)//010108¡§??07090903
{
    S=NULL;
    return 1;
}

int StackEmpty(PLStack S)//0304090309030805??¡è0902090709
{
    if(S==NULL)
        return 1;
    else
        return 0;
}

int Push(PLStack &S, Element e)//0501060504000805000608090901
{
    PLStack p;
    p=(PLStack)malloc(sizeof(LStack));
    p->elem=e;
    p->next=S;
    S=p;
    return 1;
}

int Pop(PLStack &S,Element &e) //090309060809090106020903
{
    PLStack p;
    if(!StackEmpty(S))
    {
        e=S->elem;
        p=S;
        S=S->next;
        free(p);
        return 1;
    }
    else
        return 0;
}

int maze[][16] =
{
            /*0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15  */
    /*  0 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  1 */{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  2 */{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  3 */{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  4 */{1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    /*  5 */{1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    /*  6 */{1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1},
    /*  7 */{1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    /*  8 */{1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    /*  9 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
    /* 10 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 11 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 12 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 13 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 14 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 15 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/*
 *  A recursive version of Maze
 *  Return Value:
 *  1 means find a path
 *  0 means no path
 */
PLStack stack;
int recur_maze(mark cur, mark end, int maze[M][N])
{
    mark    next;
    Element e;
    e.x = cur.x;
    e.y = cur.y;
    Push(stack, e);
    e.x = end.x;
    e.y = end.y;

    /* try east */
    next.x = cur.x;
    next.y = cur.y + 1;
    /* we have got the end */
    if (next.x == end.x && next.y == end.y )
    {
        Push(stack, e);
        return 1;
    }
    /* try if we can go this way */
    if (maze[next.x][next.y] == 0)
    {
        maze[next.x][next.y] = 2;
        if (recur_maze(next, end, maze))
        {
            return 1;
        }
    }

    /* try south */
    next.x = cur.x + 1;
    next.y = cur.y;
    /* we have got the end */
    if (next.x == end.x && next.y == end.y )
    {
        Push(stack, e);
        return 1;
    }
    /* try if we can go this way */
    if (maze[next.x][next.y] == 0)
    {
        maze[next.x][next.y] = 2;
        if (recur_maze(next, end, maze))
        {
            return 1;
        }
    }

    /* try west */
    next.x = cur.x;
    next.y = cur.y - 1;
    /* we have got the end */
    if (next.x == end.x && next.y == end.y )
    {
        Push(stack, e);
        return 1;
    }
    /* try if we can go this way */
    if (maze[next.x][next.y] == 0)
    {
        maze[next.x][next.y] = 2;
        if (recur_maze(next, end, maze))
        {
            return 1;
        }
    }

    /* try north */
    next.x = cur.x - 1;
    next.y = cur.y;
    /* we have got the end */
    if (next.x == end.x && next.y == end.y )
    {
        Push(stack, e);
        return 1;
    }
    /* try if we can go this way */
    if (maze[next.x][next.y] == 0)
    {
        maze[next.x][next.y] = 2;
        if (recur_maze(next, end, maze))
        {
            return 1;
        }
    }

    /* come to here? Poor guy, no path! */
    Pop(stack, e);
    return 0;

}

int main()
{
    int i, j;
    struct mark start,end; //start,end060507030201060207030802????03????¡§??
    Element e;

    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
            printf("%d ",maze[i][j]);
        printf("\n");
    }
    printf("start point, sperate by comma\n");
    scanf("%d,%d",&start.x,&start.y);
    printf("ent point, sperate by comma\n");
    scanf("%d,%d",&end.x,&end.y);

    InitStack(stack);
    if (!recur_maze(start, end, maze))
    {
        printf("no path for this maze!\n");
        return 1;
    }
    while(stack)
    {
        Pop(stack,e);
        printf("<--(%d,%d,%d)",e.x,e.y,e.d);
    }
    printf("\n");
    return 1;
}


