#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINES        10
#define BUFSZ        128
void reverse(char *str){
    int n = 0;
    //char *temp[MAX_LINES];
    char *temp = malloc(strlen(str) + 1);
    strcpy(temp, str);
    
    while(*str != '\0'){
        str++;
        n++;
    }
    
    for(int i = n-1; i >= 0; i--){
        *str = *(temp+i);
        str++;
    }
    
}

int main()
{
    int    i = 0, count = 0;
    char    *lines[MAX_LINES];
    char    buf[BUFSZ];
    FILE    *fp;
    //printf("Hello");
    
    if ( ( fp = fopen( "something.txt", "rw" )) == NULL ){
        printf("Hello");
        exit( -1 );
        
    }
    
    
    while ( fgets( buf, BUFSZ-1, fp ) != NULL && i < MAX_LINES )
    {
        lines[i] = (char *) malloc( strlen(buf) + 1 );
        strcpy( lines[i], buf );
        printf("Hello");
        printf("%s", lines[i]);
        i++;
        count++;
    }
    
    for(int i = 0; i < (strlen(buf) + 1); i++ ){
        reverse(lines[i]);
    }
    
    for(int i = 0; i < (strlen(buf) + 1); i++ ){
        printf("%s", lines[i]);
    }
    
    
    
}
