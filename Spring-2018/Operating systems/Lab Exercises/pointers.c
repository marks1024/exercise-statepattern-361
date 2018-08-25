//
//  pointers.c
//  
//
//  Created by Dana on 01.03.2018.
//

#include <stdio.h>
#include <stdlib.h>
void swapPointers (int **i, int **j)
{
    int *temp;
    temp = *j;
    *j = *i;
    *i = temp;
}
int main(void){
    int *i = (int*) malloc(sizeof(int));
    i[0]=2;
    int *j = (int*) malloc(sizeof(int));
    j[0]= 3;
    printf("Address of I is %p, Value of I is %p, Address of I[0] is %p, Value of I[0] is %i\n",&i,i,&i[0], i[0]);
    
    printf("Address of J is %p, Value of J is %p, Address of J[0] is %p, Value of J[0] is %i\n",&j,j,&j[0], j[0]);
    swapPointers(&i,&j);
    printf("Address of I is %p, Value of I is %p, Address of I[0] is %p, Value of I[0] is %i\n",&i,i,&i[0], i[0]);
    
    printf("Address of J is %p, Value of J is %p, Address of J[0] is %p, Value of J[0] is %i\n",&j,j,&j[0], j[0]);
}
