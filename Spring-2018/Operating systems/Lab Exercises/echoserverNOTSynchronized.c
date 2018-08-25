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

#define QSA "QS|ADMIN\r\n"
#define W "WAIT\r\n"
#define QSJ "QS|JOIN\r\n"
#define QSF "QS|FULL\r\n"

int numberOfClients = 0;
char Lname[15];
int Lnum;
pthread_mutex_t  mutex;
pthread_cond_t c;

int passivesock( char *service, char *protocol, int qlen, int *rport );

void *serveClient(void *arg){

     char            buf[BUFSIZE];
    int            ssock = (int)arg;
    int            cc;
    
    /* start working for this guy */
  
    pthread_mutex_lock( &mutex );
    numberOfClients++;
    pthread_mutex_unlock( &mutex );

    printf("The number of clients: %i\n", numberOfClients);
    char **splitted;
    splitted = (char**) malloc(100*sizeof(char**));
        if(numberOfClients == 1){
    
            if ( write( ssock, QSA, strlen(QSA)) < 0 ){
                /* This guy is dead */
                pthread_mutex_lock( &mutex );
                numberOfClients--;
                pthread_mutex_unlock( &mutex );
                close( ssock );
                exit(-1);
               }

        if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
        {
            printf( "The client has gone.\n" );
            pthread_mutex_lock( &mutex );
            numberOfClients--;
            pthread_mutex_unlock( &mutex );
            close(ssock);
            exit(-1);
        }
        else
        {
            
            buf[cc] = '\0';
            
            printf( "The client says: %s\n", buf );
            
            char *save;
            char *token;
            token = strtok_r(buf, "|", &save); //pinter to the first element of the splitted string
            int i = 0;
            
            //loop looks for special symbols
            while(token != NULL){ //store only 100 tokens
                (splitted[i]) = token; //store commands in splitted
                i++;
                token = strtok_r(NULL, "|", &save);
            }
            splitted[i] = NULL;

            
            strcpy(Lname, splitted[1]);
            Lnum = atoi(splitted[2]);
            
            printf( "The client's name: %s\n", Lname );
            
        }
        
            if ( write( ssock, W, strlen(W)) < 0 ){
                /* This guy is dead */
                pthread_mutex_lock( &mutex );
                numberOfClients--;
                pthread_mutex_unlock( &mutex );
                close( ssock );
                exit(-1);
            }
            
        }
    else if(numberOfClients < Lnum){

        if ( write( ssock, QSJ, strlen(QSJ)) < 0 ){
            /* This guy is dead */
            pthread_mutex_lock( &mutex );
            numberOfClients--;
            pthread_mutex_unlock( &mutex );
            close( ssock );
            exit(-1);
        }
        
        if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
        {
            printf( "The client has gone.\n" );
            close(ssock);
            exit(-1);
        }
        else
        {
            char Cname[33];
            buf[cc] = '\0';
            
            char *save;
            char *token;
            token = strtok_r(buf, "|", &save); //pinter to the first element of the splitted string
            int i = 0;
            
            //loop looks for special symbols
            while(token != NULL){ //store only 100 tokens
                (splitted[i]) = token; //store commands in splitted
                i++;
                token = strtok_r(NULL, "|", &save);
            }
            splitted[i] = NULL;
 
            strcpy(Lname, splitted[1]);
            printf( "The client's name: %s\n", Lname );
            
            
        }
        
        if ( write( ssock, W, strlen(W)) < 0 ){
            /* This guy is dead */
            pthread_mutex_lock( &mutex );
            numberOfClients--;
            pthread_mutex_unlock( &mutex );
            close( ssock );
            exit(-1);
        }
    }else{
        if ( write( ssock, QSF, strlen(QSF)) < 0 ){
            /* This guy is dead */
            pthread_mutex_lock( &mutex );
            numberOfClients--;
            pthread_mutex_unlock( &mutex );
            close( ssock );
            exit(-1);
        }
    }
    free(splitted);
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




