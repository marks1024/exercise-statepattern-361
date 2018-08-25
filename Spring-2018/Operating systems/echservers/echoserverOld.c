#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <pthread.h>

#define    QLEN            5
#define    BUFSIZE            4096

#define W "WAIT\r\n"
#define SQ "SENDQUIZ\r\n"
#define OK "OK\r\n"
#define BAD "BAD\r\n"
#define FULL "FULL\r\n"
#define NOGR "NOGROUP\r\n"

pthread_mutex_t  mutex;
pthread_cond_t c;

typedef struct{
    int score;
    char name[30];
    char groupName[30];
    int isLeader;
}client;

typedef struct{
    char topic[30];
    int size;
    int currSize;
    char groupName[30];
    client *members[1024];
}group;

client *clients[1010];
group *groups[32];
char OPGR[BUFSIZE] = "OPENGROUPS";
int passivesock( char *service, char *protocol, int qlen, int *rport );
void listGroups(int lssock);

void *startGroup(void *arg){
    int cc;
    char  buf[BUFSIZE];
    
    int  leaderSock = (int)arg;
    
    if (( cc = write( leaderSock, SQ, strlen(SQ))) < 0 ){ //Sendquiz messsage
        /* This guy is dead */
        //count = exitGroup(cc, count);
        close(leaderSock);
        pthread_exit( NULL );
    }
        printf( "1" );
        fflush(stdout);
    
    if ( (cc = read( leaderSock, buf, BUFSIZE )) <= 0 )
    {
        printf( "The client has gone.\n" );
        //count = exitGroup(cc, count);
        close(leaderSock);
        pthread_exit( NULL );
    }else{
        buf[cc] = '\0';
        printf( "My message: %s\n", buf );
        fflush(stdout);
        char *save;
        char *token;
        char *splitted[100];
        int quizSize = 0;
        int qCount = 0;
        printf( "2" );
        fflush(stdout);
        char *lines[1010]; //lines from file
        token = strtok_r(buf, "|", &save); //pinter to the first element of the splitted string
        int i = 0, count = 0;

        //loop looks for special symbols
        while(token != NULL){ //store only 100 tokens
            (splitted[i]) = token; //store commands in splitted
            i++;
            token = strtok_r(NULL, "|", &save);
        }
        splitted[i] = NULL;
        printf( "3" );
        fflush(stdout);

        printf( "HI" );
        fflush(stdout);
        
    quizSize = atoi(splitted[1]);
        FILE * fp;
        fp = fopen ("./file.txt", "rw");
        int remSize;
        printf("Remsize: %i\n", remSize);
        fflush(stdout);
        if (splitted[2]==NULL)
            remSize=quizSize;
            else {
            remSize = quizSize - strlen(splitted[2]);
            printf("%s\n", splitted[2]);
            fwrite(splitted[2] , 1 , strlen(splitted[2]) , fp );
        }
        printf("Remsize is: %i\n", remSize);
        
        //fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
        printf( "4" );
        fflush(stdout);
        
        while(remSize > 0){
            if ( (cc = read( leaderSock, buf, BUFSIZE )) <= 0 )
            {
                printf( "The client has gone.\n" );
                //count = exitGroup(cc, count);
                close(leaderSock);
                pthread_exit( NULL );
            }else{
                buf[cc] = '\0';
                fwrite(buf , 1 , cc , fp );
                //printf( "here" );
                printf("%s\n", buf);
                //fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
                printf( "4" );
                fflush(stdout);
                remSize -= cc;
            }
        }
        
        
    while ( fgets( buf, quizSize, fp ) != NULL && qCount < 128 )
    {
        lines[i] = (char *) malloc( strlen(buf) + 1 );
        buf[strlen(buf)-1] = '\0';
        strcpy( lines[i], buf );
        if(strcmp(lines[i], "") == 0){
            qCount++;
        }
        i++;
        count++;
    }
        printf( "5" );
        fflush(stdout);
    qCount++;
    qCount = qCount/2;
    printf("The number of questions: %i\n", qCount);
    fflush( stdout );
        fclose(fp);
    }
    
    pthread_exit( NULL ); //exit thread
}
/*
 **    The server ...
 */
int
main( int argc, char *argv[] )
{
    char            buf[BUFSIZE];
    char            *service;
    struct sockaddr_in    fsin;
    int            msock;
    int            ssock;
    fd_set            rfds;
    fd_set            afds;
    int            alen;
    int            fd;
    int            nfds;
    int            rport = 0;
    int            cc;
    pthread_t thread;
    int status;
    pthread_mutex_init( &mutex, NULL );
    pthread_cond_init( &c, NULL );
    
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
    
    
    // Set the max file descriptor being monitored
    nfds = msock+1;
    
    FD_ZERO(&afds);
    FD_SET( msock, &afds );
    for (;;)
    {
        // Reset the file descriptors you are interested in
        memcpy((char *)&rfds, (char *)&afds, sizeof(rfds));
        
        // Only waiting for sockets who are ready to read
        //  - this also includes the close event
        if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
                   (struct timeval *)0) < 0)
        {
            fprintf( stderr, "server select: %s\n", strerror(errno) );
            exit(-1);
        }
        
        // Since we've reached here it means one or more of our sockets has something
        // that is ready to read
        
        // The main socket is ready - it means a new client has arrived
        if (FD_ISSET( msock, &rfds))
        {
            int    ssock;
            
            // we can call accept with no fear of blocking
            alen = sizeof(fsin);
            ssock = accept( msock, (struct sockaddr *)&fsin, &alen );
            //clients[ssock] = (client*)malloc(sizeof(client));
            if (ssock < 0)
            {
                fprintf( stderr, "accept: %s\n", strerror(errno) );
                exit(-1);
            }
            
            /* start listening to this guy */
            FD_SET( ssock, &afds );
            
            // increase the maximum
            if ( ssock+1 > nfds )
                nfds = ssock+1;
        }
        
        /*    Handle the participants requests  */
        for ( fd = 0; fd < nfds; fd++ )
        {
            // check every socket to see if it's in the ready set
            if (fd != msock && FD_ISSET(fd, &rfds))
            {
                clients[fd] = (client*)malloc(sizeof(client));
                char *splitted[100];
                // read without blocking because data is there
                if ( (cc = read( fd, buf, BUFSIZE )) <= 0 )
                {
                    printf( "The client has gone.\n" );
                    (void) close(fd);
                    FD_CLR( fd, &afds );
                    // lower the max socket number if needed
                    if ( nfds == fd+1 )
                        nfds--;
                    
                }
                else
                {
                    buf[cc] = '\0';
                    //printf( "The client says: %s\n", buf );
                    
                    //char *save;
                    char *token;
                    /*using safe string tokenizer*/
                    token = strtok(buf, "|"); //pointer to the first element of the splitted string
                    int i = 0;
                    //loop looks for special symbols, i.e. the pipe symbol
                    while(token != NULL){ //store only 100 tokens
                        (splitted[i]) = token; //store commands in splitted
                        i++;
                        token = strtok(NULL, "|");
                    }
                    splitted[i] = NULL;
                    
                    if(strcmp(splitted[0], "GROUP") == 0){
                        groups[fd] = (group*)malloc(sizeof(group));
                        strcpy(groups[fd]->topic, splitted[1]);
                        strcpy(groups[fd]->groupName, splitted[2]);
                        //int s = atoi(splitted[3]);
                        //group[fd]->currSize = 1;
                        groups[fd]->size = atoi(splitted[3]);
                        //strcpy(clients[fd]->name, splitted[4]);
                    
                        printf("Topic is: %s. Groupname is: %s. Groupsize is: %i.\n", groups[fd]->topic, groups[fd]->groupName, groups[fd]->size);
                        fflush(stdout);
                        status = pthread_create(&thread, NULL, startGroup, (void *)fd);
                        if ( status != 0 )
                        {
                            printf( "pthread_create error %d.\n", status );
                            break;
                        }
                    }else if(strcmp(splitted[0], "JOIN") == 0){
                        strcpy(clients[fd]->groupName, splitted[1]);
                        strcpy(clients[fd]->name, splitted[2]);
                        clients[fd]->score = 0;
//                        groups[fd]->members[groups[fd]->currSize] = clients[fd];
//                        printf("Groupname is: %s. Client's name: %s. Member's name: %s.\n", clients[fd]->groupName, clients[fd]->name, groups[fd]->members[groups[fd]->currSize]->name);
                        printf("Groupname is: %s. Client's name: %s. Group's curr size: %i.\n", clients[fd]->groupName, clients[fd]->name, groups[fd]->currSize);
                    }else if(strcmp(splitted[0], "GETOPENGROUPS") == 0){
                        printf("WH\n");
                        fflush( stdout );
                        listGroups(fd);
//                        printf("%s\n", OPGR);
//                        fflush(stdout);
                    }else if(strcmp(splitted[0], "CANCEL") == 0){
                    //sprintf( buf, "OK\n" );
                    
                    }
                }
            }
            
        }
    }
    pthread_mutex_destroy( &mutex );
    pthread_exit( 0 );

}

void listGroups(int lssock){
    printf("HI!");
    fflush( stdout );
    //int n = groups[ssock]->size;
    strcpy(OPGR, "OPENGRPOUPS");
    char data[1000];
    for(int i = 0; i < 32; i++){
        if(groups[i]->size == 0){ //skip not used socket
            continue;
        }
        printf("1");
        fflush( stdout );
        sprintf(data, "|%s", groups[i]->topic);
        strcat(OPGR, data);
        sprintf(data, "|%s", groups[i]->groupName);
        strcat(OPGR, data);
        sprintf(data, "|%i", groups[i]->size);
        strcat(OPGR, data);
//        sprintf(numbCl, "|%i", groups[i]->currSize);
//        strcat(R, numbCl);
        printf("Done pr\n");
        fflush( stdout );
    }
    strcat(OPGR, "\r\n");
    printf("%s\n", OPGR);
    fflush(stdout);
    //return 0;
}
