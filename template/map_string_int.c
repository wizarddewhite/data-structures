/*
 * =====================================================================================
 *
 *       Filename:  map_string_int.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/05/2010 08:35:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include	<stdio.h>
#include	<string.h>

char A[13];

void int_to_string(int digit, char* A)
{
    char buf[13] = {0};
    int  i, len, sign = 0;
    if (digit < 0)
    {
        digit = -digit;
        sign = 1;
    }

    for (i=0; digit != 0; i++)
    {
        buf[i] = (digit%10) + 48;
        digit /= 10;
    }
//    printf("buf: %s\n", buf);

    len = strlen(buf);
    if (sign)
    {
        len++;
        A[0] = '-';
    }

    i = sign?1:0;
    for(; i < len; i++)
    {
        A[i] = buf[len-i-1];
    }
}

int string_to_int(char* A)
{
    int sum = 0;
    int index = 1;
    int len = strlen(A);
    int sign = 0;
    int i;

    if (A[0] == '-')
        sign = 1;

    for (i = len -1; i >= (sign)?1:0; i--)
    {
        sum += index * (A[i] - 48);
        index *= 10;
    }
    return (sign)?-sum:sum;
}
int main()
{
    int_to_string(-50, A);
    printf("digit %d is string %s\n", -50, A);
    printf("string 12345 is digit %d\n",string_to_int("-12345"));
    return 0;
}
