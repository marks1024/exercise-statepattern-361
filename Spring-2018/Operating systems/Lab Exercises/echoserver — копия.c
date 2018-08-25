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

#define	QLEN			5
#define	BUFSIZE			4096

int numberOfClients;
pthread_mutex_t  mutex;

int passivesock( char *service, char *protocol, int qlen, int *rport );

/*
 **    This poor server ... only serves one client at a time
 */
void *serveClient(void *arg){

     char            buf[BUFSIZE];
    int            ssock = (int)arg;
    int            cc;
    char Lname[15];
    char *msg;
//    char comp[50] = "Start a new competition. What is your name?";
//    char howBig[50] = "How big is your group?";
//    char join[50] = "Waiting for people to join.";
    
    /* start working for this guy */
    /* ECHO what the client says */
    pthread_mutex_lock( &mutex );
    numberOfClients++;
    pthread_mutex_unlock( &mutex );
    for (;;)
    {
        if(numberOfClients == 1){
            msg = "Start a new competition. What is your name?";
            if ( write( ssock, msg, strlen(msg)) < 0 ){
                /* This guy is dead */
                close( ssock );
                break;
               }
        }
//        if(numberOfClients == 1){
//            if ( write( ssock, comp, cc ) < 0 )
//            {
//                /* This guy is dead */
//                close( ssock );
//                break;
//            }
//            if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
//            {
//                printf( "The client has gone.\n" );
//                close(ssock);
//                break;
//            }
//            else
//            {
//                buf[cc] = '\0';
//                printf( "The client says: %s\n", buf );
//                strcpy(Lname, buf);
//                printf("The number of currently connected clients: %i\n", numberOfClients);
//                if ( write( ssock, buf, cc ) < 0 )
//                {
//                    /* This guy is dead */
//                    close( ssock );
//                    break;
//                }
//            }
//            if ( write( ssock, howBig, cc ) < 0 )
//            {
//                /* This guy is dead */
//                close( ssock );
//                break;
//            }
//            if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
//            {
//                printf( "The client has gone.\n" );
//                close(ssock);
//                break;
//            }
//            else
//            {
//                buf[cc] = '\0';
//                printf( "The client says: %s\n", buf );
//
//                int lnum = atoi(buf);
//                printf("The number of currently connected clients: %i\n", numberOfClients);
//                if ( write( ssock, buf, cc ) < 0 )
//                {
//                    /* This guy is dead */
//                    close( ssock );
//                    break;
//                }
//                if ( write( ssock, join, cc ) < 0 )
//                {
//                    /* This guy is dead */
//                    close( ssock );
//                    break;
//                }
//            }
//        }
        
        if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
        {
            printf( "The client has gone.\n" );
            close(ssock);
            break;
        }
        else
        {
            //char b[33];
            buf[cc] = '\0';
//            char numberOfCl[3];
//            numberOfCl[0] = itoa(numberOfClients, b, 10);
//            strcat(buf, numberOfCl);
            printf( "The client says: %s\n", buf );
            //printf("The number of currently connected clients: %i\n", numberOfClients);
            if ( write( ssock, buf, cc ) < 0 )
            {
                /* This guy is dead */
                close( ssock );
                break;
            }
            //char Lname[20];
            strcpy(Lname, buf);
            printf( "The client's name: %s\n", Lname );
        }
        
        msg = "How big is your group?";
        if ( write( ssock, msg, strlen(msg)) < 0 ){
            /* This guy is dead */
            close( ssock );
            break;
        }
        
        if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
        {
            printf( "The client has gone.\n" );
            close(ssock);
            break;
        }
        else
        {
            char b[33];
            buf[cc] = '\0';
            //            char numberOfCl[3];
            //            numberOfCl[0] = itoa(numberOfClients, b, 10);
            //            strcat(buf, numberOfCl);
            printf( "The client says: %s\n", buf );
            //printf("The number of currently connected clients: %i\n", numberOfClients);
            if ( write( ssock, buf, cc ) < 0 )
            {
                /* This guy is dead */
                close( ssock );
                break;
            }
            //char Lname[20];
            strcpy(b, buf);
            int Lnum;
            Lnum = atoi(b);
            printf( "Group size: %i\n", Lnum );
        }
        
        
    }
    pthread_exit( NULL );
}

int
main( int argc, char *argv[] )
{
    char            *service;
    struct sockaddr_in    fsin;
    int            rport = 0;
    int            alen;
    int            msock;
    int            ssock;
    pthread_t thread;
    int status;
    pthread_mutex_init( &mutex, NULL );

    switch (argc)
    {
        case    1:
            // No args? let the OS choose a port and tell the user
            rport = 1;
            break;
        case    2:
            // User provides a port? then use it
            service = argv[1];
            break;
        default:
            fprintf( stderr, "usage: server [port]\n" );
            exit(-1);
    }

    msock = passivesock( service, "tcp", QLEN, &rport );
        if (rport)
        {
            //    Tell the user the selected port
            printf( "server: port %d\n", rport );
            fflush( stdout );
        }
    
    for (;;)
    {
        int    ssock;
        
                alen = sizeof(fsin);
                ssock = accept( msock, (struct sockaddr *)&fsin, &alen );
                if (ssock < 0)
                {
                    fprintf( stderr, "accept: %s\n", strerror(errno) );
                    exit(-1);
                }
        
                printf( "A client has arrived for echoes.\n" );
                fflush( stdout );
        
                /* start working for this guy */
                /* ECHO what the client says */
        status = pthread_create(&thread, NULL, serveClient, (void *)ssock);
        if ( status != 0 )
        {
            printf( "pthread_create error %d.\n", status );
            exit( -1 );
        }
       
    }
    pthread_mutex_destroy( &mutex );
    pthread_exit( 0 );
}




