
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFSIZE		4096
int connectsock( char *host, char *service, char *protocol );

/*
 **    Client
 */

void *writeToServer(void *args){
    char buf[BUFSIZE];
    int csock = (int) args;
    //     Start the loop
    while ( fgets( buf, BUFSIZE, stdin ) != NULL )
    {
        // If user types 'q' or 'Q', end the connection
        if ( buf[0] == 'q' || buf[0] == 'Q' )
        {
            exit(-1);
        }
    
    if ( write( csock, buf, strlen(buf) ) < 0 )
    {
        fprintf( stderr, "client write: %s\n", strerror(errno) );
        exit( -1 );
    }
    }
    pthread_exit(NULL);
}

void *readFromSercer(void *args){
    int csock = (int) args;
    char buf[BUFSIZE];
    int cc;
    
    while(1)
    {
    if ( (cc = read( csock, buf, BUFSIZE )) <= 0 )
    {
        printf( "The server has gone.\n" );
        close(csock);
        exit(-1);
    }
    else
    {
        buf[cc] = '\0';
        printf( "%s\n", buf );
    }
    
    }
    pthread_exit(NULL);
}

int
main( int argc, char *argv[] )
{
    char        buf[BUFSIZE];
    char        *service;
    char        *host = "localhost";
    int        cc;
    int        csock;
    pthread_t thread[2];
    int status1, status2;
    
    switch( argc )
    {
        case    2:
            service = argv[1];
            break;
        case    3:
            host = argv[1];
            service = argv[2];
            break;
        default:
            fprintf( stderr, "usage: chat [host] port\n" );
            exit(-1);
    }
    
    /*    Create the socket to the controller  */
    if ( ( csock = connectsock( host, service, "tcp" )) == 0 )
    {
        fprintf( stderr, "Cannot connect to server.\n" );
        exit( -1 );
    }
    
    printf( "The server is ready, please start sending to the server.\n" );
    printf( "Type q or Q to quit.\n" );
    fflush( stdout );

        // Send to the server
        status1 = pthread_create(&thread[0], NULL, writeToServer, (void *)csock);
        if ( status1 != 0 )
        {
            printf( "pthread_create error %d.\n", status1 );
            exit( -1 );
        }
        
        // Read the echo and print it out to the screen
    
        status2 = pthread_create(&thread[1], NULL, readFromSercer, (void *)csock);
        if ( status2 != 0 )
        {
            printf( "pthread_create error %d.\n", status2 );
            exit( -1 );
        }
    for (int j = 0; j < 2; j++ )
        pthread_join( thread[j], NULL );
    close( csock );
    pthread_exit( 0 );
}


