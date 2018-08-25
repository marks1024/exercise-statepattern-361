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
fd_set  afds;
int nfds;

typedef struct{
    int mysock;
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
    char *lines[1010];
    int numberOfQuestions;
    int answ[128];
}group;

client *clients[1010];
group *groups[32];
char OPGR[BUFSIZE] = "OPENGROUPS";
int passivesock( char *service, char *protocol, int qlen, int *rport );
void listGroups(int lssock);
int findByGroupname(char *grname);
void leaveGroup(int csock);

void *getQuiz(void *arg){
    int cc;
    char  buf[BUFSIZE];
    int count = 0, n = 0, i;
    
    int  leaderSock = (int) arg;
    
    printf("Leader of quiz 0: %i\n\n\n", leaderSock);
    fflush(stdout);
    char filename[30];
    sprintf(filename, "myquiz%d.txt", leaderSock);
    printf("%s\n", filename);
    FILE *temp;
    if((temp = fopen(filename, "ab+" )) == NULL){
        printf("Cannot open the file specified!\n");
    }
    
    printf("Leader of quiz 1: %i\n\n", leaderSock);
    fflush(stdout);
    
    if (( cc = write( leaderSock, SQ, strlen(SQ))) < 0 ){ //Sendquiz messsage
        /* This guy is dead */
        close(leaderSock);
        pthread_exit( NULL );
    }
        printf( "1\n" );
        fflush(stdout);
    
    int header = 0;
    int remSize = 9;
    //fwrite(&namee , 5 , 1 , temp );
    while ( (cc = read( leaderSock, buf, BUFSIZE )) > 0 && remSize > 0)
    {
        header++;
        if(cc < 0){
        printf( "The client has gone.\n" );
        close(leaderSock);
        pthread_exit( NULL );
    }else{
        buf[cc] = '\0';
        printf("cc: %i\n", cc);
        printf( "My message: %s\n", buf );
        if(header == 1){
                    char *save;
                    char *token;
                    char *splitted[100];
                    int quizSize = 0;

                    token = strtok_r(buf, "|", &save); //pinter to the first element of the splitted string
                    int i = 0, count = 0;
                    //loop looks for special symbols
                    while(token != NULL){ //store only 100 tokens
                        (splitted[i]) = token; //store commands in splitted
                        i++;
                        token = strtok_r(NULL, "|", &save);
                    }

                    quizSize = atoi(splitted[1]);
            
                    if (splitted[2]==NULL)
                            remSize=quizSize;
                        else {
                            remSize = quizSize - strlen(splitted[2]);
                            printf("%s\n", splitted[2]);
                            fprintf(temp, "%s", splitted[2]);
                        }
                        printf("Remsize is: %i\n", remSize);
                        if(remSize == 0){
                          break;
                        }
                        printf( "4" );
                        fflush(stdout);
        }else{
            fprintf(temp, "%s", buf);
            remSize-=cc;
            printf("Remsize now is: %i\n", remSize);
            printf( "4" );
            fflush(stdout);
            if(remSize == 0){
                break;
            }
        
        }
        
    }
    }
    fclose(temp);
    FILE *quiz;
        int qCount = 0;
        printf( "QuizCount: %i\n", qCount );
        fflush(stdout);
    
    if((quiz = fopen(filename, "rw" )) == NULL){
        printf("Cannot open the file specified!\n");
    }
    
        /*select for client*/
    while ( fgets( buf, BUFSIZE-1, quiz ) != NULL && qCount < 128 )
    {
        groups[leaderSock]->lines[i] = (char *) malloc( strlen(buf) + 1 );
        buf[strlen(buf)-1] = '\0';
        strcpy( groups[leaderSock]->lines[i], buf );
        if(strcmp(groups[leaderSock]->lines[i], "") == 0){
            qCount++;
        }
        i++;
        count++;
    }
        printf( "5" );
        fflush(stdout);
    qCount++;
    qCount = qCount/2;
    groups[leaderSock]->numberOfQuestions = qCount;
    printf("The number of questions: %i\n", qCount);
    printf("The count: %i\n", count);
    fflush( stdout );
    fclose(quiz);
    if (remove(filename) == 0)
    printf("Deleted successfully");
    else
    printf("Unable to delete the file");
    pthread_mutex_lock( &mutex );
    FD_SET(leaderSock, &afds );
    pthread_mutex_unlock( &mutex );

    pthread_exit( NULL ); //exit thread
}

void *startQuiz(void *arg){
    
    int cc;
    char  buf[BUFSIZE];
    
    int count = 0, n = 0, i;
    int maxfds;
    
    int  leaderSock = (int)arg;
    int fd;
    int isFirst = 0;
    char R[BUFSIZE] = "RESULT";
//    char w[BUFSIZE] = "WIN|"; //win protocol
    char w[BUFSIZE] = "WIN|\r\n";
    char *save;
    char *token;
    char *splitted[100];
    
    fd_set  trfds;
    fd_set  tafds;
    maxfds = leaderSock+1;
    
    FD_ZERO(&tafds);
    FD_SET( leaderSock, &tafds );
    
    struct timeval tv;
    
    /* Wait up to 60 seconds. */
    tv.tv_sec = 60;
    tv.tv_usec = 0;
    int answerCount = 0;
    
    for(int i = 0; i < groups[leaderSock]->numberOfQuestions; i++){
        answerCount = 0;
        char q[BUFSIZE] = "QUES|";
        char qa[BUFSIZE] =""; //to store question and answer string
        char numbCl[1000];
        char answ[10]; //store the correct answer
        int size = 0; //size of QA string
        int j = i;
        printf("I am here!\n");
        fflush(stdout);
        
        while(strcmp(groups[leaderSock]->lines[n], "") != 0){
            sprintf(numbCl, "%s\n", groups[leaderSock]->lines[n]); //copy each line of question and answer until the "\n" character
            strcat(qa, numbCl);
            size+=strlen(numbCl); //increase the size of QA string
            n++;
        }
        
        n++;
        sprintf(answ, "%s", groups[leaderSock]->lines[n]); //read the correct answer
        printf("The correct answer: %s\n", answ);
        fflush(stdout);
        n+=2; //skip one more empty line
        //size = strlen(q);
        sprintf(numbCl, "%i|", size); //copy the size
        strcat(q, numbCl); //add to protocol the size
        strcat(q, qa); //add to protocol the string itself
        printf("%s", q);
        
        //if (FD_ISSET( leaderSock, &tafds))
        //{
            for(int i = 0; i < groups[leaderSock]->currSize; i++){
                printf("Accessing\n");
                fflush(stdout);
                printf("Leader's group current size: %i\n", groups[leaderSock]->currSize);
                fflush(stdout);
                printf("Player's socket: %i\n", groups[leaderSock]->members[i]->mysock);
                fflush(stdout);
                groups[leaderSock]->answ[i] = 0;
                FD_SET( groups[leaderSock]->members[i]->mysock, &tafds );
                
                if ( groups[leaderSock]->members[i]->mysock + 1> maxfds ){
                    maxfds = groups[leaderSock]->members[i]->mysock+1;
                    printf("Number of file descrip:%i\n", maxfds);
                }

                if (( cc = write( groups[leaderSock]->members[i]->mysock, q, strlen(q))) < 0 ){
                    /* This guy is dead */
                    leaveGroup(groups[leaderSock]->members[i]->mysock);
                    close(groups[leaderSock]->members[i]->mysock);
                    pthread_exit( NULL );

                }
                
                
            }
        
        
        int setCount = 1;
        
        while(answerCount != groups[leaderSock]->currSize && setCount>0){
            tv.tv_sec = 60;
            tv.tv_usec = 0;
            memcpy((char *)&trfds, (char *)&tafds, sizeof(trfds));
            printf("Time rem1: %li\n", tv.tv_sec);
            fflush(stdout);
            
            if (select(maxfds, &trfds, (fd_set *)0, (fd_set *)0, &tv) < 0){
                fprintf( stderr, "server select: %s\n", strerror(errno) );
                            exit(-1);
             }
            printf("Time rem2: %li\n", tv.tv_sec);
            fflush(stdout);
            setCount = 0;
            for(int i = 0; i < groups[leaderSock]->currSize; i++){
                int fd = groups[leaderSock]->members[i]->mysock;
                if(FD_ISSET(fd, &trfds)){
                    setCount++;
                }else{
                    //leaveGroup(fd);
                }
            }
            printf("Set count: %d\n\n", setCount);
            fflush(stdout);
            
            if(setCount == 0){
                
                break;
            }
            
//              for(int i = 0; i < groups[leaderSock]->currSize; i++){
//                  int fd = groups[leaderSock]->members[i]->mysock;
//                  if(FD_ISSET(fd, &trfds) == 0 ){
//                  printf("You are kicked out!");
//                  fflush(stdout);
//
//                  pthread_mutex_lock( &mutex );
//                  leaveGroup(fd);
//                  pthread_mutex_unlock( &mutex );
//
//                  FD_CLR(fd, &tafds );
//                  pthread_mutex_lock( &mutex );
//                  FD_SET(fd, &afds);
//                  pthread_mutex_unlock( &mutex );
//                  }
//             }
            
            for ( fd = 0; fd < maxfds; fd++ ){
                 // check every socket to see if it's in the ready set
                if (fd != leaderSock && FD_ISSET(fd, &trfds)){
                    
                    if ( (cc = read( fd, buf, BUFSIZE )) <= 0 )
                    {
                        
                        printf( "The client has gone.\n" );
                        (void) close(fd);
                        FD_CLR( fd, &tafds );
                        // lower the max socket number if needed
                        if ( maxfds == fd+1 )
                            maxfds--;
                        
                    }else{
                        buf[cc] = '\0';
                        if(strcmp(buf, "LEAVE\r\n") == 0){
                            printf("I want to leave...");
                            fflush(stdout);
                            
                            pthread_mutex_lock( &mutex );
                            leaveGroup(fd);
                            pthread_mutex_unlock( &mutex );

                            FD_CLR(fd, &tafds );
                            pthread_mutex_lock( &mutex );
                            FD_SET(fd, &afds);
                            pthread_mutex_unlock( &mutex );
                        }
                        
                        char *save;
                        char *token;
                        /*using safe string tokenizer*/
                        token = strtok_r(buf, "|", &save); //pointer to the first element of the splitted string
                        int m = 0;
                        
                        while(token != NULL){ //store only 100 tokens
                            (splitted[m]) = token; //store commands in splitted
                            m++;
                            token = strtok_r(NULL, "|", &save);
                        }
                        
                        splitted[m] = NULL;
                        token = strtok_r(splitted[1], "\r\n", &save); //extract just answer
                        answerCount++;
                        printf( "Answer count: %i\n", answerCount);
                        fflush( stdout );
                        /*if initially isFirst flag set to 0 but the answer is correct then this client is first and it sets isFirst flag to 1 */
                        printf( "1%i is first?: %i\n", fd, isFirst);
                        fflush( stdout );
                        if(groups[leaderSock]->answ[j] == 0 && strcmp(answ, splitted[1]) == 0){
                                  groups[leaderSock]->answ[j] = 1;
                        }else if(groups[leaderSock]->answ[j] == 1 && strcmp(answ, splitted[1]) == 0){ //if the flag was already set by
                            groups[leaderSock]->answ[j] = 0;
                        }
                        if(groups[leaderSock]->answ[j] == 1 && strcmp(answ, splitted[1]) == 0){
                            clients[fd]->score+=2;
                        }else if(strcmp(answ, splitted[1]) == 0){
                            clients[fd]->score +=1;
                        }else if(strcmp(splitted[1], "NOANS") != 0){
                            clients[fd]->score -=1;
                        }
                        printf( "2%i is first?: %i\n", fd, groups[leaderSock]->answ[j]);
                        fflush( stdout );
                        if(groups[leaderSock]->answ[j] == 1 && strcmp(answ, splitted[1]) == 0){ //the winner
                            printf( "The winner is: %s\n", clients[fd]->name);
                            fflush( stdout );
                            sprintf(w, "WIN|%s\r\n", clients[fd]->name);
                            
                        }
                }
                }
//                    if(fd != leaderSock && FD_ISSET(fd, &trfds) == 0 && clients[fd] != NULL){
//                        printf("You are kicked out: %d!\n", fd);
//                        fflush(stdout);
//
//                        pthread_mutex_lock( &mutex );
//                        leaveGroup(fd);
//                        pthread_mutex_unlock( &mutex );
//
//                        FD_CLR(fd, &tafds );
//                        pthread_mutex_lock( &mutex );
//                        FD_SET(fd, &afds);
//                        pthread_mutex_unlock( &mutex );
//                    }
                //}
                
            }
        }
        for(int i = 0; i < groups[leaderSock]->currSize; i++){

            printf("Leader's group current size: %i\n", groups[leaderSock]->currSize);
            fflush(stdout);
            printf("%s's score: %i\n", groups[leaderSock]->members[i]->name, groups[leaderSock]->members[i]->score);
            fflush(stdout);
            printf("My socket: %i\n", groups[leaderSock]->members[i]->mysock);
            fflush(stdout);
//            if(answerCount == 0){
//                sprintf(w, "WIN|\r\n");
//            }
            //printf("%s + length: %d", w, strlen(w));
            
            if (( cc = write( groups[leaderSock]->members[i]->mysock, w, strlen(w))) < 0 ){
                /* This guy is dead */
                printf( "The client has gone.\n" );
                leaveGroup(groups[leaderSock]->members[i]->mysock);
                close(groups[leaderSock]->members[i]->mysock);
            }

        }
        
        if (( cc = write(leaderSock, w, strlen(w))) < 0 ){
            /* This guy is dead */
            //count = exitGroup(cc, count);
            printf( "The leader has gone.\n" );
            leaveGroup(leaderSock);
            close(leaderSock);
            pthread_exit( NULL );
        }
        //answerCount = 0;
    }

     strcpy(R, "RESULT");
        
      char res[BUFSIZE];
    for(int i = 0; i < groups[leaderSock]->currSize; i++){
        printf("Sorted!\n");
        fflush( stdout );
        printf("%s + ", groups[leaderSock]->members[i]->name);
        printf("Scores: %i\n", groups[leaderSock]->members[i]->score);
        fflush( stdout );
        
        sprintf(res, "|%s", groups[leaderSock]->members[i]->name);
        strcat(R, res);
        sprintf(res, "|%i", groups[leaderSock]->members[i]->score);
        strcat(R, res);
        printf("Done pr\n");
        fflush( stdout );
                               
    }
     strcat(R, "\r\n");
     printf("%s\n", R);
     //printf("%s + length: %d", R, strlen(R));
     fflush(stdout);
                           
     for(int i = 0; i < groups[leaderSock]->currSize; i++){
         
         if (( cc = write( groups[leaderSock]->members[i]->mysock, R, strlen(R))) < 0 ){
              /* This guy is dead */
             //count = exitGroup(cc, count);
             printf( "The client has gone.\n" );
             leaveGroup(groups[leaderSock]->members[i]->mysock);
             close(groups[leaderSock]->members[i]->mysock);
             pthread_exit( NULL );
             
                 }
     }
    
    if (( cc = write(leaderSock, R, strlen(R))) < 0 ){
        /* This guy is dead */
        //count = exitGroup(cc, count);
        printf( "The leader has gone.\n" );
        leaveGroup(groups[leaderSock]->members[i]->mysock);
        close(leaderSock);
        pthread_exit( NULL );
        //pthread_exit( NULL );
    }

    char end[30];
    sprintf(end, "ENDGROUP|%s\r\n", groups[leaderSock]->groupName);
    
    for(int i = 0; i < groups[leaderSock]->currSize; i++){
   
        if (( cc = write( groups[leaderSock]->members[i]->mysock, end, strlen(end))) < 0 ){
            /* This guy is dead */
            //count = exitGroup(cc, count);
            printf( "The client has gone.\n" );
            leaveGroup(groups[leaderSock]->members[i]->mysock);
            close(leaderSock);
            pthread_exit( NULL );
            //pthread_exit( NULL );
        }
        
        printf( "%d is going to be  cleared and returned back\n",  groups[leaderSock]->members[i]->mysock);
        fflush(stdout);
        
        FD_CLR(groups[leaderSock]->members[i]->mysock, &tafds );
        pthread_mutex_lock( &mutex );
        FD_SET(groups[leaderSock]->members[i]->mysock, &afds);
        printf( "%d was cleared and returned back\n",  groups[leaderSock]->members[i]->mysock);
        fflush(stdout);
//         listGroups(groups[leaderSock]->members[i]->mysock);
        
        pthread_mutex_unlock( &mutex );
        groups[leaderSock]->members[i]->score = 0;
        strcpy(groups[leaderSock]->members[i]->groupName, "");
        //groups[leaderSock]->members[i] = NULL;
        
        
        
    }
    
    if (( cc = write( leaderSock, end, strlen(end))) < 0 ){
        /* This guy is dead */
        printf( "The leader has gone.\n" );
        leaveGroup(leaderSock);
        close(leaderSock);
        pthread_exit( NULL );
    }
    
    
     FD_CLR(leaderSock, &tafds );
     pthread_mutex_lock( &mutex );
     FD_SET(leaderSock, &afds );
     pthread_mutex_unlock( &mutex );
     free(groups[leaderSock]);
     groups[leaderSock] = NULL;
     pthread_exit( NULL ); //exit thread

}

/*
 **    The server ...
 */

int main( int argc, char *argv[] )
{
    char            buf[BUFSIZE];
    char            *service;
    struct sockaddr_in    fsin;
    int            msock;
    int            ssock;
    
    int            alen;
    int            fd;
    int            rport = 0;
    int            cc;
    struct timeval tv;
    fd_set  rfds;
    int  nfds;
    char bad[50];
    pthread_t thread;
    int status1, status2;
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
    
    
    // Set the max file descriptor being monitored
    nfds = msock+1;
    
    FD_ZERO(&afds);
    FD_SET( msock, &afds );
    /* Wait up to 60 seconds. */
    
    for (;;)
    {
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        // Reset the file descriptors you are interested in
        pthread_mutex_lock( &mutex );
        memcpy((char *)&rfds, (char *)&afds, sizeof(rfds));
        pthread_mutex_unlock( &mutex );
        // Only waiting for sockets who are ready to read
        //  - this also includes the close event
        if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, &tv) < 0)
//        if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
//                   (struct timeval *)0) < 0)
        {
            fprintf( stderr, "server select: %s\n", strerror(errno) );
            exit(-1);
        }
//        printf("I woke up!\n");
//        fflush(stdout);
//        printf("Is socket 4 woken up? %d\n", FD_ISSET( 4, &afds));
//        fflush(stdout);
//        printf("Is socket 5 woken up? %d\n", FD_ISSET( 5, &afds));
//        fflush(stdout);
//        printf("Is socket 6 woken up? %d\n", FD_ISSET( 6, &afds));
//        fflush(stdout);
        
        // Since we've reached here it means one or more of our sockets has something
        // that is ready to read
        
        // The main socket is ready - it means a new client has arrived
        if (FD_ISSET( msock, &rfds))
        {
            int    ssock;
            
            // we can call accept with no fear of blocking
            alen = sizeof(fsin);
            ssock = accept( msock, (struct sockaddr *)&fsin, &alen );
            listGroups(ssock);
            //clients[ssock] = (client*)malloc(sizeof(client));
            if (ssock < 0)
            {
                fprintf( stderr, "accept: %s\n", strerror(errno) );
                exit(-1);
            }
            
            /* start listening to this guy */
            pthread_mutex_lock( &mutex );
            FD_SET( ssock, &afds );
            pthread_mutex_unlock( &mutex );
            
            // increase the maximum
            if ( ssock+1 > nfds )
                nfds = ssock+1;
        }
//        printf("Before loop: nfds: %d\n", nfds);
//        fflush(stdout);
        /*    Handle the participants requests  */
        for ( fd = 0; fd < nfds; fd++ )
        {
//            printf("In loop nfds: %d\n", nfds);
//            fflush(stdout);
            
            // check every socket to see if it's in the ready set
            if (fd != msock && FD_ISSET(fd, &rfds))
            {
                if(clients[fd] == NULL){
                    clients[fd] = (client*)malloc(sizeof(client));
                    clients[fd]->mysock = fd;
                }

                char *splitted[100];
                // read without blocking because data is there
                if ( (cc = read( fd, buf, BUFSIZE )) <= 0 )
                {
                    printf( "The client has gone.\n" );
                    (void) close(fd);
                    
                    FD_CLR( fd, &afds );
                    leaveGroup(fd);
                    close(fd);
                    pthread_exit( NULL );
                    
                    // lower the max socket number if needed
                    if ( nfds == fd+1 )
                        nfds--;
                    
                }
                else
                {
                    buf[cc] = '\0';
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
                    //splitted[i] = NULL;
                    
                    if(strcmp(splitted[0], "GROUP") == 0){

                        if(findByGroupname(splitted[2]) != -1){
                           
                            strcpy(bad, "BAD|The groupname is not unique\r\n");
                            //sprintf(message, "BAD|The groupname is not unique\r\n");
                            if (( cc = write( fd, bad, strlen(bad))) < 0 ){ //Sendquiz messsage
                                /* This guy is dead */
                                close(fd);
                                FD_CLR( fd, &afds );
                                // lower the max socket number if needed
                                if ( nfds == fd+1 )
                                nfds--;
                            }
                        }else{
                        groups[fd] = (group*)malloc(sizeof(group));
                        strcpy(groups[fd]->topic, splitted[1]);
                        strcpy(groups[fd]->groupName, splitted[2]);
                        groups[fd]->currSize = 0;
                        groups[fd]->size = atoi(splitted[3]);

                            printf("Topic is: %s. Groupname is: %s. Groupsize is: %i.Leadersock is: %i\n", groups[fd]->topic, groups[fd]->groupName, groups[fd]->size, clients[fd]->mysock);
                        fflush(stdout);
                            
                            pthread_mutex_lock( &mutex );
                            FD_CLR(fd, &afds );
                            pthread_mutex_unlock( &mutex );
                            
                       status1 = pthread_create(&thread, NULL, getQuiz, (void *)fd);
                            if ( status1 != 0 )
                            {
                                printf( "pthread_create error %d.\n", status1 );
                                break;
                            }
                            printf("FD ssock of leader: %i\n", fd);
                            fflush(stdout);
                        }
                    }else if(strcmp(splitted[0], "JOIN") == 0){
                        
                        token = strtok(splitted[2], "\r\n");
                        strcpy(clients[fd]->name, splitted[2]);
                        clients[fd]->score = 0;
                        int leadsock = findByGroupname(splitted[1]);
                        if(leadsock == -1){
                            strcpy(bad, "BAD|Group does not exist\r\n");
                            if (( cc = write( fd, bad, strlen(bad))) < 0 ){ //Sendquiz messsage
                                /* This guy is dead */
                                close(fd);
                                FD_CLR( fd, &afds );
                                // lower the max socket number if needed
                                if ( nfds == fd+1 )
                                    nfds--;
                            }
                        }else{
                            if(groups[leadsock]->currSize == groups[leadsock]->size){
                                strcpy(bad, "BAD|The group is full\r\n");
                                if (( cc = write( fd, bad, strlen(bad))) < 0 ){ //Sendquiz messsage
                                    /* This guy is dead */
                                    close(fd);
                                }
                            }else{
                                
                                strcpy(clients[fd]->groupName, splitted[1]);
                                groups[leadsock]->currSize++;
                                int c = groups[leadsock]->currSize-1;
                                printf("c is %d\n", c);
                                fflush(stdout);
                                groups[leadsock]->members[c] = clients[fd];
                                printf("Groupname is: %s. Client's name: %s. Group curr size: %i.\n", clients[fd]->groupName, clients[fd]->name, groups[leadsock]->currSize);
                                printf("New member: %s and its socket is %d\n", groups[leadsock]->members[c]->name, groups[leadsock]->members[c]->mysock);
                                fflush(stdout);
                                if (( cc = write( fd, OK, strlen(OK))) < 0 ){ //Sendquiz messsage
                                    /* This guy is dead */
                                    close(fd);
                                    FD_CLR( fd, &afds );
                                   
                                    // lower the max socket number if needed
                                    if ( nfds == fd+1 )
                                        nfds--;
                                }
                                
                                if(groups[leadsock]-> currSize == groups[leadsock]->size){
                                    
                                    for(int i = 0; i < groups[leadsock]->currSize; i++){
                                        FD_CLR( groups[leadsock]->members[i]->mysock, &afds );
                                    }
                                    FD_CLR( leadsock, &afds );
                                    status2 = pthread_create(&thread, NULL, startQuiz, (void *)leadsock);
                                    if ( status2 != 0 )
                                    {
                                        printf( "pthread_create error %d.\n", status2 );
                                        break;
                                    }
                                }
                            }
                        }
                        
                    }else if(strcmp(splitted[0], "GETOPENGROUPS\r\n") == 0){
                        printf("WH\n");
                        fflush( stdout );
                        listGroups(fd);

                    }else if(strcmp(buf, "LEAVE\r\n") == 0){
                        printf("I want to leave...");
                        fflush(stdout);
                        pthread_mutex_lock( &mutex );
                        leaveGroup(fd);
                        pthread_mutex_unlock( &mutex );
                        
                    }else if(strcmp(splitted[0], "CANCEL\r\n") == 0){
                        printf("CANCel");
                        fflush(stdout);
                        if(clients[fd]->isLeader == 1 && groups[fd]->size!=groups[fd]->currSize){
                            free(groups[fd]);
                            groups[fd] = NULL;
                            if (( cc = write( fd, OK, strlen(OK))) < 0 ){ //Sendquiz messsage
                                /* This guy is dead */
                                close(fd);
                                FD_CLR( fd, &afds );
                                // lower the max socket number if needed
                                if ( nfds == fd+1 )
                                    nfds--;
                            }
                        }else if(clients[fd]->isLeader == 0){
                            strcpy(bad, "BAD|You are not group leader\r\n");
                            if (( cc = write( fd, bad, strlen(bad))) < 0 ){ //Sendquiz messsage
                                /* This guy is dead */
                                close(fd);
                                FD_CLR( fd, &afds );
                                // lower the max socket number if needed
                                if ( nfds == fd+1 )
                                nfds--;
                            }
                        }else{
                            strcpy(bad, "BAD|Quiz has started\r\n");
                            if (( cc = write( fd, bad, strlen(bad))) < 0 ){ //Sendquiz messsage
                                /* This guy is dead */
                                close(fd);
                                FD_CLR( fd, &afds );
                                // lower the max socket number if needed
                                if ( nfds == fd+1 )
                                nfds--;
                            }
                        }
                    
                    }
                }
            }
            
        }
    }
    pthread_mutex_destroy( &mutex );
    pthread_exit( 0 );

}

 int findByGroupname(char *grname){
     
    printf("Looking for a group...\n");
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
    
    printf("HI!\n");
    fflush( stdout );
    strcpy(OPGR, "OPENGROUPS");
    char data[1000];
    for(int i = 0; i < 32; i++){
        if(groups[i] == NULL){ //skip not used socket
            //sprintf(data, "%s\r\n", OPGR);
            //strcat(OPGR, data);
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
        sprintf(data, "|%i", groups[i]->currSize);
        strcat(OPGR, data);
        printf("Done pr\n");
        fflush( stdout );
    }
    //strcat(OPGR, "\r\n");
    printf("%s\r\n", OPGR);
    sprintf(OPGR, "%s\r\n", OPGR);
    
    fflush(stdout);
    if (( cc = write( lssock, OPGR, strlen(OPGR))) < 0 ){ //Sendquiz messsage
        /* This guy is dead */
        close(lssock);
        FD_CLR( lssock, &afds );
        // lower the max socket number if needed
        if ( nfds == lssock+1 )
        nfds--;
        close(lssock);
    }
}

void leaveGroup(int csock){
    int cc;
    char bad[50];
    int lssock = findByGroupname(clients[csock]->groupName);
    if(clients[csock]->isLeader == 1){
        strcpy(bad, "BAD|Leader cannot leave\r\n");
        if (( cc = write( csock, bad, strlen(bad))) < 0 ){ //Sendquiz messsage
            /* This guy is dead */
            close(csock);
            FD_CLR( csock, &afds );
              /* lower the max socket number if needed */
            if ( nfds == csock+1 )
            nfds--;
        }
    }else{
        printf("I am going to leave...");
        fflush(stdout);
        clients[csock]->score = 0;
        strcpy(clients[csock]->groupName, "");
        groups[lssock]->currSize = groups[lssock]->currSize-1;
            printf("Groupname is: %s. Client's name: %s. Group curr size: %i.\n", clients[csock]->groupName, clients[csock]->name, groups[lssock]->currSize);
            //printf("Old member: %s\n", groups[leadsock]->members[c]->name);
            if (( cc = write( csock, OK, strlen(OK))) < 0 ){ //Sendquiz messsage
                /* This guy is dead */
                close(csock);
                FD_CLR( csock, &afds );
                 /* lower the max socket number if needed */
                if ( nfds == csock+1 )
                nfds--;
            }
            
    
       }
               }
