/*
 ============================================================================
 Name        : DanaNew.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
        // TODO code application logic here

       // Scanner scan = new Scanner(System.in);
    //int n = scan.nextInt();
	int n;
    scanf("%i", &n);
    int count=0;
    int x=0;
    int y=0;

    if(n > 0 && n <= 1000000){
    		if( n<=1000000 && n>0 ){
    			for(int i=1; i<=n; i++){
    				for(int j=1; j<=n; j++){
    					if ((i*j==n)&& (i!=j) ){
    						count++;
    						x = i;
    						y = j;
    					}
    				}
    			}
    		}



    if(count==2){
    		printf("%i ", x);
		printf("%i", y);

    }
    else{
    		printf("%i", -1);
    }

   }
}
