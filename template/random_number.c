/*
 * =====================================================================================
 *
 *       Filename:  random_number.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/23/2010 05:24:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
 *  Generate a random number in range x
 */
int random_num(int start, int range)
{
    return (start + rand()%range);
}

int main()
{
    int i, j, sum;
    float average, exp;
    srand(time(0));
    for (i = 0; i < 1000; i++)
    {
        sum = 0;
        for (j = 0; j < 1000; j++)
        {
            sum += random_num(1, 11);
        }
        average = ((float)sum)/1000.0;
//        printf("%d average is %f\n", i, average);
        if (i != 0)
            exp = (exp + average)/2.0;
        else
            exp = average;
    }
    printf("average is %f\n", average);
    return 0;
}
