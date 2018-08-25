//Cat Family
//#include<stdio.h>
//#include<stdlib.h>
//
//void callCatFamily(int r, int c);
//
//int main(){
//
//    int column;
//    int row;
//
//    scanf("%i%2i", &row, &column);
//
//    if(row < 1 || column > 20){
//        printf("Out of bound!\n");
//        exit(-1);
//    }
//
//
//    callCatFamily(row,column);
//
//    return 0;
//}
//
//void callCatFamily(int r, int c){
//
//    char o = 111;
//    char l_slash = 47;
//    char r_slash = 92;
//    char dot = 46;
//    char more = 62;
//    char less = 60;
//    char mouse = 94;
//    char under = 95;
//    char l_brack = 40;
//    char r_brack = 41;
//
//    for(int i = 0; i < r; i++){
//        for(int j = 0; j < c; j++){
//            printf( " %2c%c%c%c%c ", l_slash, r_slash, under,l_slash, r_slash);
//        }
//        printf("\n");
//        for(int j = 0; j < c; j++){
//            printf(" %c%2c%c%c%2c", l_brack, o, dot, o, r_brack);
//        }
//        printf("\n");
//        for(int j = 0; j < c; j++){
//            printf( " %2c%2c%2c ", more, mouse, less);
//        }
//        printf("\n");
//    }
//}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int findLeastSweet(int *sweets, int n);
int findSecondLeastSweet(int *sweets, int n);
int checkSweetness(int *sweets, int n, int k);
int **increaseSweetness(int *sweets, int n, int l, int s);

int main() {
        int N;
        int K;
        int **arr = int* malloc(sizeof(int));
    //int *arr;
        int operations;
    
        scanf("%i%2i", &N, &K);
    int cookies[N];
    
    for(int i = 0; i < N; i++){
        
        scanf("%d", &cookies[i]);
    }

    int sweetness = checkSweetness(cookies, N, K);
    *arr = cookies;
    
   
    
    while( sweetness != 1){
        int least = findLeastSweet(arr, sizeof(arr));
        int secondLeast = findSecondLeastSweet(arr, sizeof(arr));
        arr = increaseSweetness(*arr, sizeof(*arr), least, secondLeast);
        operations++;
    }
    
    printf("\n%i\n", findLeastSweet(cookies, N));
    printf("%i\n", findSecondLeastSweet(cookies, N));
    printf("\n%i\n", checkSweetness(cookies, N, K));
    printf("%i\n", operations);
    
    return 0;
}

    int findLeastSweet(int *sweets, int n){
        int least = 100000;
        int index;

        for(int i = 0; i < n; i++){
            
            if(sweets[i]<least){
                
                index = i;
                least = sweets[i];
               
                
            }
            
    }
        return index;
    }
        
        int findSecondLeastSweet(int *sweets, int n){
            int least = 10000000;
            int secondLeast = 1000000;
            int index;
            
            
            for(int i = 0; i < n; i++){
                
                if(least < sweets [i]){
                    secondLeast = least;
                    least = sweets[i];
                    index = i;
                    

                }
                
            }
            return index;
        }

    int checkSweetness(int *sweets, int n, int k){
      
        for(int i = 0; i < n; i++){
            if(sweets[i] < k){
                return 0;
            }
           
            
        }
        return 1;
    }

int **increaseSweetness(int *sweets, int n, int l, int s){
    int value = sweets[l] + 2*sweets[s];
    int **array;
    array[0] = value;
    for(int i ; i<n; i++){
        if(i != l || i != s){
            array[i+1] = sweets[i];
        }
    }
    return array;
}













