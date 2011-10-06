// =====================================================================================
// 
//       Filename:  Stack.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/2010 09:47:52 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================

#include	<iostream>
#include	"Stack.h"
using namespace std;

int
main ( int argc, char *argv[] )
{
    int i;
    Stack<char> string;
    string.push('a');
    string.push('b');
    string.push('c');
    string.push('d');
    for (i=0;i<5;i++)
        cout << string.pop() << endl;

    return 0;
}				// ----------  end of function main  ----------
