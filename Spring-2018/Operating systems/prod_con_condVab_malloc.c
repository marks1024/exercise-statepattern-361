//
//  prod_con_condVab_malloc.c
//  
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define THREADS    100
#define BUFSIZE 20
#define ITEM "Some Item Name"

typedef struct item
{
    char *name;
    int size;
} item_t;

int count;
item_t *buffer[BUFSIZE];

pthread_mutex_t  mutex;
pthread_cond_t c;

void *produce( void *ign )
{
    item_t *item;
    
    // produce an item
    item = (item_t *) malloc( sizeof(item_t) );
    item->name = (char *) malloc( strlen(ITEM)+1 );
    strcpy( item->name, ITEM );
    item->size = strlen(ITEM);
    // produce an item
    
    sem_wait( &empty );
    sem_wait( &mutex );
    
    printf( "P count is %d\n", count );
    fflush( stdout );
    
    buffer[count] = item;
    count++;
    
    sem_post( &mutex );
    sem_post( &full );
    
    pthread_exit( NULL );
}

void *consume( void *ign )
{
    item_t *item;
    
    sem_wait( &full );
    sem_wait( &mutex );
    
    printf( "C count is %d\n", count );
    fflush( stdout );
    
    item = buffer[count-1];
    buffer[count-1] = NULL;
    count--;
    
    sem_post( &mutex );
    sem_post( &empty );
    
    // CONSUMING
    // dispose of the item
    free( item->name );
    free( item );
    // CONSUMING
    
    pthread_exit( NULL );
}

int main( int argc, char **argv )
{
    pthread_t threads[THREADS*2];
    pthread_mutex_init( &mutex, NULL );
    pthread_cond_init( &c, NULL );
    int status, i, j;
    
    sem_init( &mutex, 0, 1 );
    sem_init( &full, 0, 0 );
    sem_init( &empty, 0, BUFSIZE );
    
    count = 0;
    for ( j = 0, i = 0; i < THREADS; i++ )
    {
        status = pthread_create( &threads[j++], NULL, produce, NULL );
        if ( status != 0 )
        {
            printf( "pthread_create error %d.\n", status );
            exit( -1 );
        }
        status = pthread_create( &threads[j++], NULL, consume, NULL );
        if ( status != 0 )
        {
            printf( "pthread_create returned error %d.\n",
                   status );
            exit( -1 );
        }
    }
    for ( j = 0; j < THREADS*2; j++ )
    pthread_join( threads[j], NULL );
    printf( "Finally, the count is %d.\n", count );
    pthread_exit( 0 );
}
