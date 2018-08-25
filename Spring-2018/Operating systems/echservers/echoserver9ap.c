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
int findByGroupname(char *grname);

void *startGroup(void *arg){
    int cc;
    char  buf[BUFSIZE];
    int count = 0, n = 0, i;
    char *lines[1010]; //lines from file
    FILE* fp;
    
    int  leaderSock = (int)arg;
    
    if (( cc = write( leaderSock, SQ, strlen(SQ))) < 0 ){ //Sendquiz messsage
        /* This guy is dead */
        //count = exitGroup(cc, count);
        close(leaderSock);
        pthread_exit( NULL );
    }
        printf( "1" );
        fflush(stdout);
    
    
    if ( (cc = read( leaderSock, buf, BUFSIZE )) > 0 )
    {
//        printf( "The client has gone.\n" );
//        //count = exitGroup(cc, count);
//        close(leaderSock);
//        pthread_exit( NULL );
//    }else{
        buf[cc] = '\0';
        printf( "My message: %s\n", buf );
        fflush(stdout);
    }
        int qCount = 0;
    printf( "My message: %i\n", qCount );
    
//    if ( (cc = read( leaderSock, buf, BUFSIZE )) <= 0 )
//    {
//        printf( "The client has gone.\n" );
//        //count = exitGroup(cc, count);
//        close(leaderSock);
//        pthread_exit( NULL );
//    }else{
//        buf[cc] = '\0';
//        printf( "My message: %s\n", buf );
//        fflush(stdout);
//        char *save;
//        char *token;
//        char *splitted[100];
//        int quizSize = 0;
//        int qCount = 0;
//        printf( "2" );
//        fflush(stdout);
//        char *lines[1010]; //lines from file
//        token = strtok_r(buf, "|", &save); //pinter to the first element of the splitted string
//        int i = 0, count = 0;
//
//        //loop looks for special symbols
//        while(token != NULL){ //store only 100 tokens
//            (splitted[i]) = token; //store commands in splitted
//            i++;
//            token = strtok_r(NULL, "|", &save);
//        }
//        splitted[i] = NULL;
//        printf( "3" );
//        fflush(stdout);
//
//        printf( "HI" );
//        fflush(stdout);
//
//        quizSize = atoi(splitted[1]);
//        //FILE * fp;
//        if((fp = fopen("myquiz.txt", "ab+" )) == NULL){
//            printf("Cannot open the file!\n");
//        }
//
//        fwrite(buf , 1 , cc , fp );
//        //fp = fopen ("./file.txt", "rw");
//        int remSize;
////        printf("Remsize: %i\n", remSize);
////        fflush(stdout);
//        if (splitted[2]==NULL)
//            remSize=quizSize;
//        else {
//            remSize = quizSize - strlen(splitted[2]);
//            printf("%s\n", splitted[2]);
//            fwrite(splitted[2] , 1 , strlen(splitted[2]) , fp );
//        }
//        printf("Remsize is: %i\n", remSize);
//
//        //fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
//        printf( "4" );
//        fflush(stdout);
//
//        while(remSize > 0){
//            if ( (cc = read( leaderSock, buf, BUFSIZE )) <= 0 )
//            {
//                printf( "The client has gone.\n" );
//                //count = exitGroup(cc, count);
//                close(leaderSock);
//                pthread_exit( NULL );
//            }else{
//                buf[cc] = '\0';
//                fwrite(buf , 1 , cc , fp );
//                //printf( "here" );
//                printf("%s\n", buf);
//                //fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
//                printf( "4" );
//                fflush(stdout);
//                remSize -= cc;
//            }
//        }
//
//    char buff[BUFSIZE];
    //memset(buff, '0', sizeof(buff));
//    if((cc = read(leaderSock, buff, BUFSIZE)) <= 0)
//    {
//        printf( "The client has gone.\n" );
//        //count = exitGroup(cc, count);
//        close(leaderSock);
//        pthread_exit( NULL );
//
//    }else{
//        buff[cc] = '\0';
//        printf( "2\n" );
//        fflush(stdout);
//        printf("I received %s\n",buff);
//        fflush(stdout);
//        printf("Bytes received %d\n",cc);
//        fflush(stdout);
//        fwrite(buff, 1,cc,fp);
//    }
    
    
    
    while ( fgets( buf, BUFSIZE-1, fp ) != NULL && qCount < 128 )
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
    
    for(int i = 0; i < qCount; i++){
        
        char q[BUFSIZE] = "QUES|";
        char qa[BUFSIZE] =""; //to store question and answer string
        char numbCl[1000];
        char answ[10]; //store the correct answer
        int size = 0; //size of QA string
        printf("I am here!\n");
        fflush(stdout);
        
        while(strcmp(lines[n], "") != 0){
            sprintf(numbCl, "%s\n", lines[n]); //copy each line of question and answer until the "\n" character
            strcat(qa, numbCl);
            size+=strlen(lines[n]); //increase the size of QA string
            n++;
        }
        
        n++;
        sprintf(answ, "%s", lines[n]); //read the correct answer
        printf("The correct answer: %s\n", answ);
        fflush(stdout);
        n+=2; //skip one more empty line
        //size = strlen(q);
        sprintf(numbCl, "%i|\n", size); //copy the size
        strcat(q, numbCl); //add to protocol the size
        strcat(q, qa); //add to protocol the string itself
        printf("%s", q);
//        if (( cc = write( ssock, q, strlen(q))) < 0 ){
//            /* This guy is dead */
//            count = exitGroup(cc, count);
//            close(ssock);
//            pthread_exit( NULL );
//        }
   }
    
    /*select for client*/
//    fd_set            rfds;
//    fd_set            afds;
//     nfds = leaderSsock+1;
//
//     FD_ZERO(&afds);
//     FD_SET( leaderSock, &afds );
//     for (;;)
//     {
//     // Reset the file descriptors you are interested in
//     memcpy((char *)&rfds, (char *)&afds, sizeof(rfds));
//
//     // Only waiting for sockets who are ready to read
//     //  - this also includes the close event
//     if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
//     (struct timeval *)0) < 0)
//     {
//     fprintf( stderr, "server select: %s\n", strerror(errno) );
//     exit(-1);
//     }
//
//     // Since we've reached here it means one or more of our sockets has something
//     // that is ready to read
//
//     // The main socket is ready - it means a new client has arrived
//     if (FD_ISSET( msock, &rfds))
//     {
//     int    ssock;
//
//     // we can call accept with no fear of blocking
//     alen = sizeof(fsin);
//     ssock = accept( msock, (struct sockaddr *)&fsin, &alen );
//     //clients[ssock] = (client*)malloc(sizeof(client));
//     if (ssock < 0)
//     {
//     fprintf( stderr, "accept: %s\n", strerror(errno) );
//     exit(-1);
//     }
//
//     /* start listening to this guy */
//    FD_SET( ssock, &afds );
//
//    // increase the maximum
//    if ( ssock+1 > nfds )
//        nfds = ssock+1;
//}
//
///*    Handle the participants requests  */
//for ( fd = 0; fd < nfds; fd++ )
//{
//    // check every socket to see if it's in the ready set
//    if (fd != msock && FD_ISSET(fd, &rfds))
//    {
//    }
//}
//     }
    
    /*end of select */
    //}
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
                //listGroups(fd);
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
                        
                        if(findByGroupname(splitted[1]) != -1){
                            if (( cc = write( fd, BAD, strlen(BAD))) < 0 ){ //Sendquiz messsage
                                /* This guy is dead */
                                close(fd);
                            }
                        }else{
                        groups[fd] = (group*)malloc(sizeof(group));
                        strcpy(groups[fd]->topic, splitted[1]);
                        strcpy(groups[fd]->groupName, splitted[2]);
                        //int s = atoi(splitted[3]);
                        groups[fd]->currSize = 1;
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
                        }
                    }else if(strcmp(splitted[0], "JOIN") == 0){
                        
                        strcpy(clients[fd]->name, splitted[2]);
                        clients[fd]->score = 0;
                        int leadsock = findByGroupname(splitted[1]);
                        if(leadsock == -1){
                            if (( cc = write( fd, NOGR, strlen(NOGR))) < 0 ){ //Sendquiz messsage
                                /* This guy is dead */
                                close(fd);
                            }
                        }else{
                            if(groups[leadsock]->currSize == groups[leadsock]->size){
                                if (( cc = write( fd, FULL, strlen(FULL))) < 0 ){ //Sendquiz messsage
                                    /* This guy is dead */
                                    close(fd);
                                }
                            }else{
                                strcpy(clients[fd]->groupName, splitted[1]);
                                int c = groups[leadsock]->currSize++;
                                groups[leadsock]->members[c] = clients[fd];
                                printf("Groupname is: %s. Client's name: %s. Group curr size: %i.\n", clients[fd]->groupName, clients[fd]->name, groups[leadsock]->currSize);
                                printf("New member: %s\n", groups[leadsock]->members[c]->name);
                                if (( cc = write( fd, OK, strlen(OK))) < 0 ){ //Sendquiz messsage
                                    /* This guy is dead */
                                    close(fd);
                                }
                            }
                            
                        }
                        
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

 int findByGroupname(char *grname){
    printf("Join??");
    fflush( stdout );
     for(int i = 0; i < 32; i++){
         if(groups[i] == NULL){ //skip not used socket
             continue;
         }
         if(strcmp(groups[i]->groupName, grname) == 0){
             printf("Found!\n");
             fflush( stdout );
             return i;
     }
}
     return -1;
}

void listGroups(int lssock){
    int cc;
    printf("HI!");
    fflush( stdout );
    strcpy(OPGR, "OPENGRPOUPS");
    char data[1000];
    for(int i = 0; i < 32; i++){
        if(groups[i] == NULL){ //skip not used socket
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
    if (( cc = write( lssock, OPGR, strlen(OPGR))) < 0 ){ //Sendquiz messsage
        /* This guy is dead */
        close(lssock);
    }
}
