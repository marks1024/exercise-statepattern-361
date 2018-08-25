//
//  main.c
//  SimpleC
//
//  Created by Dana on 24.01.2018.
//  Copyright © 2018 Dana Zhumabekova. All rights reserved.
//
//
//  LabSimpleC.c
//
//
//  Created by Dana on 24.01.2018.
//
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINES        10
#define BUFSZ        128


void reverse(char *str){

    int n;
    n = (int) (strlen(str));
    char *str1 = str;
    
    char *str2 = str + n - 1;
    char temp;
    
    while(str2 > str1){
        temp = *str2;
        *str2-- = *str1;
        *str1++ = temp;
        
    }
}


int main()
{
    int    i = 0, count = 0;
    char    *lines[MAX_LINES];
    char    buf[BUFSZ];
    
    FILE    *fp;
    
    if ( ( fp = fopen( "something.txt", "rw" )) == NULL ){
        printf("Hello");
        exit( -1 );
        
    }
  
    
    while ( fgets( buf, BUFSZ-1, fp ) != NULL && i < MAX_LINES )
    {
        lines[i] = (char *) malloc( strlen(buf) + 1 );
        strcpy( lines[i], buf );
        i++;
        count++;
    }
    
    for(int i = 0; i < count; i++ ){
        printf("%s\n\n", lines[i]);
        reverse(lines[i]);
    }
    
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count-1; j++){
            if(strlen(lines[j]) < strlen(lines[j+1])){
                char *temp;
                temp = lines[j];
                lines[j] = lines[j+1];
                lines[j+1] = temp;

            }
        }
    }
    
    for(int i = 0; i < count; i++ ){
        printf("%s\n", lines[i]);
        free(lines[i]);
    }
    
    
    
}

        


