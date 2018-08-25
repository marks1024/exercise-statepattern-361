//
//  threads.c
//  
//
//  Created by Dana on 01.03.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREADS 10


int main()
{
    int pid;
    int status, i;
    
    printf( "bird\n" );
    
    pid = fork();
    if ( pid != 0 )
    {
        waitpid( pid, &status, 0 );
        pid = fork();
        printf( "dog\n" );
    }
    else
    {
        printf( "fish\n" );
        execlp( "date", "date", NULL );
        printf( "cow\n" );
    }
    
    printf( "end\n" );
}

//int main()
//{
//    char *sentences;
//    int a;
//
//    sentences = (char *) malloc(sizeof(char)*10);
//
//    for (a = 0; a < 12; a++){
//        sentences[a] = 'b' + a;
//    }
//
//    for (a = 0; a < 12; a++){
//        printf( "%c\n", sentences[a] );
//    }
//
//    printf("\n");
//    sentences = (char *) malloc(sizeof(char)*5);
//
//    for (a = 0; a < 5; a++){
//        sentences[a] = 'l' + a;
//    }
//
//    for (a = 0; a < 10; a++){
//        printf( "%c\n", sentences[a]);
//    }
//    free(sentences);
//}
////
//int main()
//{
//    int pid;
//    int status, i;
//
//    printf( "bird\n" );
//
//    pid = fork();
//    if ( pid != 0 )
//    {
//        waitpid( pid, &status, 0 );
//        pid = fork();
//        if(pid == 0)
//            printf("nyan\n");
//        printf( "dog\n" );
//    }
//    else
//    {
//        printf( "fish\n" );
//        execlp( "date", "date", NULL );
//        printf( "cow\n" );
//    }
//
//    printf( "end\n" );
//}


//int main()
//{
//    pid_t           pid;
//    int             x = 3;
//    int             status;
//    if ( ( pid = fork() ) == 0 )
//    {
//        x++;
//        printf( "x is %d.\n", x );
//        if ( ( pid = fork() ) == 0 )
//        {
//            x++;
//            printf( "x is %d.\n", x );
//        }else{
//            waitpid( pid, &status, 0 );
//            printf( "x is %d.\n", x );
//        }
//    }else{
//        waitpid( pid, &status, 0 );
//        printf( "x is %d.\n", x );
//    }
//    printf( "x is %d.\n", x );
//}

//pthread_mutex_t mutex;
//
//int x = 2;
//void *thread_A( void *arg )
//{
//    int y=3;
//    //pthread_mutex_lock( &mutex);
//
//    x = x + y;
//    printf( "x is %d, y is %d.\n", x, y );
//    //pthread_mutex_unlock( &mutex);
//    pthread_exit( NULL );
//}
//    void *thread_B( void *arg ){
//        //pthread_mutex_lock( &mutex);
//
//        int y=x;
//        x = x + y;
//        printf( "x is %d, y is %d.\n", x, y );
//        //pthread_mutex_unlock( &mutex );
//        pthread_exit( NULL );
//    }
//
//int main() {
//
////     pthread_mutex_init(&mutex, NULL);
//    pthread_t tid; int y = 1;
//    pthread_create( &tid, NULL, thread_A, NULL );
//    pthread_create( &tid, NULL, thread_B, NULL );
//    printf( "x is %d, ", x );
//    printf( "y is %d.\n", y );
//    pthread_exit( 0 );
//}

//void *print_hello( void *tid )
//{
//    int *id = (int *) tid;
//
//    printf( "Hello from thread %d.\n", *id );
//    pthread_exit( NULL );
//}
//
//int main( int argc, char **argv )
//{
//    pthread_t threads[THREADS];
//    int status, i;
//
//    for ( i = 0; i < THREADS; i++ )
//    {
////        int *index = (int *) malloc(sizeof(int));
////        *index = i;
//        int indexes[THREADS];
//        printf( "Creating thread %d.\n", i );
////        status = pthread_create( &threads[i], NULL,
////                                print_hello, (void *) &i );
//        status = pthread_create( &threads[i], NULL, print_hello, (void*)indexes[i]);
//        if ( status != 0 )
//            exit( -1 );
//    }
//    pthread_exit( 0 );
//}




//Test 1 333
//pthread_mutex_t mutexA, mutexB;
//int x = 5;
//
//void *thread_A( void *arg )
//{
//     pthread_mutex_lock( &mutexA);
//    x = x + 1;
//    printf("%i\n", x);
//    pthread_mutex_unlock( &mutexA);
//    pthread_exit( NULL );
//}
//
//void *thread_B( void *arg )
//{
//     pthread_mutex_lock( &mutexB);
//    x = x + 2;
//     printf("%i\n", x);
//    pthread_mutex_unlock( &mutexB);
//    pthread_exit( NULL );
//}
//
//int main()
//{
//    pthread_t tid[2];
//    pthread_mutex_init( &mutexA, NULL );
//    pthread_mutex_init( &mutexB, NULL );
//
//
//
//    pthread_mutex_lock( &mutexA);
//    pthread_mutex_lock( &mutexB);
//
//    pthread_create(&tid[0], NULL, thread_A, NULL );
//    pthread_create( &tid[1], NULL, thread_B, NULL);
//
//    pthread_mutex_unlock( &mutexB);
//    pthread_mutex_unlock( &mutexA);
//
//    pthread_join( tid[0], NULL );
//    pthread_join( tid[1], NULL );
//
//
//
//    pthread_mutex_destroy( &mutexA );
//    pthread_mutex_destroy( &mutexB );
//    pthread_exit( 0 );
//}

//
//int x = 2;
//void *thread_A( void *arg )
//{
//    int y=3;
//    pthread_mutex_lock( &mutex);
//
//    x = x + y;
//    printf( "x is %d, y is %d.\n", x, y );
//    pthread_mutex_unlock( &mutex);
//    pthread_exit( NULL );
//}
//    void *thread_B( void *arg ){
//        pthread_mutex_lock( &mutex);
//
//        int y=x;
//        x = x + y;
//        printf( "x is %d, y is %d.\n", x, y );
//        pthread_mutex_unlock( &mutex );
//        pthread_exit( NULL );
//    }
//
//int main() {
//
//     pthread_mutex_init(&mutex, NULL);
//    pthread_t tid; int y = 1;
//    pthread_create( &tid, NULL, thread_A, NULL );
//    pthread_create( &tid, NULL, thread_B, NULL );
//    printf( "x is %d, ", x );
//    printf( "y is %d.\n", y );
//    pthread_exit( 0 );
//}

