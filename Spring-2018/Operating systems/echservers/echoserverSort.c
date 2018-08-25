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
#define MYQ "What is the longest river in the world?\r\n"


int numberOfClients = 0;
char *Lname[1010]; //array to store names of the clients
int scores[1010]; //array to store the scores of the clients
char *lines[1010]; //lines from file
int Lnum = 0; //group size given by admin
int qCount = 0; //number of questions in the quiz
int answer[128]; //array to store the order of answer of each client for each question
int resCount = 0;
int isFirst = 0; //flag who is first
int firstSocket = 0; //to store the value of the first socket
int isFull = 0; //flag if the group is full
int numberOfNames = 0; //number of names provided 
char R[BUFSIZE] = "RESULT";
char w[BUFSIZE] = "WIN|"; //win protocol
pthread_mutex_t  mutex;
pthread_cond_t c;

int passivesock( char *service, char *protocol, int qlen, int *rport );

/*This function is called when write and read are failed. When the client is last it allows another client to arrive*/
int exitGroup(int ccc, int clientsCount){
    printf("CCC is: %i\n", ccc);
    if(clientsCount == Lnum && ccc <=0){ //case when the last
        pthread_mutex_lock( &mutex );
        numberOfClients--; //descrement the number of clients
        clientsCount = numberOfClients;
        pthread_mutex_unlock( &mutex );
    }else{
        pthread_mutex_lock( &mutex );
        numberOfClients--;
        pthread_mutex_unlock( &mutex );
    }
    return clientsCount;
}

void *serveClient(void *arg){
    int fs = 0;
//    printf( "Hello from thread.\n" );
//    int i = 0;
//
//    fflush( stdout );

    char  buf[BUFSIZE];
    int  ssock = (int)arg;
    
    printf("Socket: %i\n", ssock);
    int  cc;
    int count = 0;
    int ans = 0;
    int nameCount  = 0;
    int fullFlag = 0;
    
    /* start working for this guy*/
    
    pthread_mutex_lock( &mutex );
    numberOfClients++; //increment the number of clients
    count = numberOfClients;
    fullFlag = isFull;
    nameCount = numberOfNames;
    pthread_mutex_unlock( &mutex );
    
    printf("The number of clients: %i\n", numberOfClients);
    fflush( stdout );
    
    char *splitted[100]; //th pointer to array of strings to handle the answer of client
    //splitted = (char**) malloc(100*sizeof(char**));
    Lname[ssock] = (char*) malloc(30*sizeof(char*)); //to strore the name of this particular client
    scores[ssock] = 0; //initialize the score count for each participant
    
    /*Each thread checks the following three conditions:
     1) if it is a first arrived client (number of clients copied to local client's count is equal to one) it becomes an administrator and sends it's name and the group's size
     2) if clients arrive until the total number of clients exceeds the group's size they join the game and their names are saved using socket number
     3) if the number of clients exceeeds the group's size server sends a message that the group is full and disconnects that client by closing socket and exiting the thread*/
    
    /*Client's socket is closed, the thread is exited and the number of clients is decremented whenever the server notices (usually by trying to read or write) that the client disconnects */

        if(count == 1){
            fs = ssock; //first socket number
            pthread_mutex_lock( &mutex );
            firstSocket = fs;
            pthread_mutex_unlock( &mutex );
            numberOfNames = 0;
            resCount = 0;
            isFirst = 0; //flag who is first
            isFull = 0;
            if ( ( cc = write( ssock, QSA, strlen(QSA))) < 0 ){ //Message to Admin
                /* This guy is dead */
                count = exitGroup(cc, count);
                close( ssock ); //close the connection with the server
                pthread_exit( NULL ); //exit thread
               }
        if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
        {
            printf( "The client has gone.\n" );
            count = exitGroup(cc, count);
            close(ssock);
            pthread_exit( NULL );
        }
        else
        {
            buf[cc] = '\0';
            printf( "The client says: %s\n", buf );
            char *save;
            char *token;
            /*using safe string tokenizer*/
            token = strtok_r(buf, "|", &save); //pointer to the first element of the splitted string
            int i = 0;
            //loop looks for special symbols, i.e. the pipe symbol
            while(token != NULL){ //store only 100 tokens
                (splitted[i]) = token; //store commands in splitted
                i++;
                token = strtok_r(NULL, "|", &save);
            }
            splitted[i] = NULL;
            strcpy(Lname[ssock], splitted[1]);//the name of the ADMIN
            Lnum = atoi(splitted[2]); //Group size
            
           printf( "The client's name: %s\n", Lname[ssock]);
            fflush( stdout );
            printf( "The group size: %i\n", Lnum);
            fflush( stdout );
            pthread_mutex_lock( &mutex );
            numberOfNames++; //increment the number of clients
            nameCount = numberOfNames;
            pthread_mutex_unlock( &mutex );
        }
        
            if (( cc = write( ssock, W, strlen(W))) < 0 ){ //WAIT messsage
                /* This guy is dead */
                count = exitGroup(cc, count);
                close(ssock);
                pthread_exit( NULL );
            }
            
        }else if(count <= Lnum && fullFlag == 0 && nameCount < Lnum){
            printf("FULL: %i\n", isFull);
            printf("Name count:%i\n", nameCount);
            fs = ssock;
            pthread_mutex_lock( &mutex );
            if(fs < firstSocket){
                firstSocket = fs;
            }
            pthread_mutex_unlock( &mutex );
            
            
            
        if (( cc = write( ssock, QSJ, strlen(QSJ))) < 0 ){ //JOIN message
            /* This guy is dead */
            count = exitGroup(cc, count);
            close(ssock);
            pthread_exit( NULL );
        }
        if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
        {
            printf( "The client has gone.\n" );
            count = exitGroup(cc, count);
            close(ssock);
            pthread_exit( NULL );
        }
        else
        {
            buf[cc] = '\0';
            if(buf[0] == 'q' || buf[0] == 'Q'){
                count = exitGroup(cc, count);
                close(ssock);
                pthread_exit( NULL );
            }
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
            token = strtok_r(splitted[1], "\n", &save);
           strcpy(Lname[ssock], splitted[1]); //names of clients are stored
           printf( "The client's name: %s\n", Lname[ssock]);
            pthread_mutex_lock( &mutex );
            numberOfNames++; //increment the number of clients
            nameCount = numberOfNames;
            pthread_mutex_unlock( &mutex );
        }
        
        if (( cc = write( ssock, W, strlen(W))) < 0 ){ //Wait message
            /* This guy is dead */
            count = exitGroup(cc, count);
            close(ssock);
            pthread_exit( NULL );
        }
    }else{
        if (( cc = write( ssock, QSF, strlen(QSF))) < 0 ){ //FULL massage
            /* This guy is dead */
            count = exitGroup(cc, count);
        }
        if(Lnum!=0){
            pthread_mutex_lock( &mutex );
            isFull = 1; //once the the number of clients reaches group size nobody can connect (do not set isFull flag to 1, if the group leader haven't given yeat a group size
            fullFlag = isFull;
            pthread_mutex_unlock( &mutex );
        }
        count = exitGroup(cc, count);
        close( ssock); //server is unavailable for extra clients
        pthread_exit( NULL );
    }

    /*If the clients is not the last in the group it goes to sleep via cond_wait where conditional variable is the number of clients.
     If the client is the last one it wakes up all other sleeeping clients and the question from the server sent to all clients st the same time*/
    
    if(nameCount < Lnum){
        pthread_mutex_lock( &mutex );
        while(numberOfNames < Lnum){
            pthread_cond_wait(&c, &mutex);
        }
        pthread_mutex_unlock( &mutex );

    }else{
        pthread_mutex_lock( &mutex );
        pthread_cond_broadcast(&c);
        pthread_mutex_unlock( &mutex );
    }
    
    int n = 0; //for line count
    
    /*start a quiz*/
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
            if (( cc = write( ssock, q, strlen(q))) < 0 ){
                /* This guy is dead */
                count = exitGroup(cc, count);
                close(ssock);
                pthread_exit( NULL );
            }
            
            /*Another local variable ans is declared and gets the copy of the answer count inside mutex lock.
             If the ans == 1, it means that this client answered first to the server's question and its name stored in Lname[sscock] is printed*/
            if ( (cc = read( ssock, buf, BUFSIZE )) <= 0 )
            {
                printf( "The client has gone.\n" );
                count = exitGroup(cc, count);
                close(ssock);
                pthread_exit( NULL );
            }
            else
            {
                
                /*if client leave in the middle of the quiz the thread should exit*/
                if((buf[0] == 'q' || buf[0] == 'Q')){
 
                    pthread_mutex_lock( &mutex );
                       answer[i]++; //order for this client for this question
                    ans = answer[i];
                    /*This part of code inside if statement prevents deadlock only if the last client who should answer types quit. It should wakeup other threads before leaving.*/
                    
                    if(ans == numberOfClients){
                        pthread_cond_broadcast(&c);
                    }
                       printf("Answer count: %i", ans);
                       fflush(stdout);
                    pthread_mutex_unlock( &mutex );
                    count = exitGroup(cc, count);
                    strcpy(Lname[ssock], "");
                    free(Lname[ssock]);
                    close(ssock);
                    pthread_exit( NULL );
                }
                buf[cc] = '\0';
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
                token = strtok_r(splitted[1], "\n", &save); //extract just answer
//
//                //strcpy(buf, splitted[1]); //answers are stored
//                printf( "The client's answer: %s\n", splitted[1]);
                
                pthread_mutex_lock( &mutex );
                answer[i]++; //order for this client for this question
                ans = answer[i];
                printf("Answer count: %i", answer[i]);
                fflush(stdout);
                pthread_mutex_unlock( &mutex );
                
                int isF; //local flag isFirst
                pthread_mutex_lock( &mutex );
                isF = isFirst;
                pthread_mutex_unlock( &mutex );
                
                /*if initially isFirst flag set to 0 but the answer is correct then this client is first and it sets isFirst flag to 1 */
                if(isF == 0 && strcmp(answ, splitted[1]) == 0){
                    pthread_mutex_lock( &mutex );
                    isFirst = 1;
                    isF = isFirst;
                    pthread_mutex_unlock( &mutex );
                }else if(isF == 1 && strcmp(answ, splitted[1]) == 0){ //if the flag was already set by someone else then just set the local flag to 0
                    isF = 0;
                }
                if(isF == 1 && strcmp(answ, splitted[1]) == 0){
                    scores[ssock] +=2;
                }else if(strcmp(answ, splitted[1]) == 0){
                    scores[ssock] +=1;
                }else if(strcmp(splitted[1], "NOANS") != 0){
                    scores[ssock] -=1;
                }
                printf( "Count is: %s\n", Lname[ssock]);
                printf( "Count is: %i\n", scores[ssock]);
                fflush( stdout );
                if(isF == 1 && strcmp(answ, splitted[1]) == 0){ //the winner
                    printf( "The winner is: %s\n", Lname[ssock]);
                    fflush( stdout );
                    sprintf(numbCl, "%s\r\n", Lname[ssock]);
                    strcpy(w, "WIN|");
                    strcat(w, numbCl);
            }
        printf("Ans %i\n", ans);
        fflush( stdout );
        
         /* All clients should wait until all other clients answer the question. Here if the order of answer of the client is less than the number of clients, it waits. If the answer order is equal to the number of clients, it releases the lock and each client is nitifyed who is the winner.*/
                
        if(ans < numberOfClients){
            pthread_mutex_lock( &mutex );
            while(answer[i] < numberOfClients){
                pthread_cond_wait(&c, &mutex);
            }
            pthread_mutex_unlock( &mutex );
            
        }else{
            pthread_mutex_lock( &mutex );
            pthread_cond_broadcast(&c);
            pthread_mutex_unlock( &mutex );
        }
                
        }
        
        /*Send the name of the winner to all clients*/
        if (( cc = write( ssock, w, strlen(w))) < 0 ){
            /* This guy is dead */
            count = exitGroup(cc, count);
            close(ssock);
            pthread_exit( NULL );
        }
        
        /*The last client who answers the question sets isFirst flag to 0 to repeat the same procedure in the next iteration with another question.*/
        if(answer[i] == numberOfClients){
            pthread_mutex_lock( &mutex );
            isFirst = 0;
            pthread_mutex_unlock( &mutex );
        }
    }
    
    char numbCl[1000];
    int res = 0;
    
    pthread_mutex_lock( &mutex );
    resCount++;
    res = resCount;
    pthread_mutex_unlock( &mutex );
    /*The next lines of code is to sort the clients names ansd scores based on their scores in the descending order. We do this inside the mutex lock to not allow each client sort the array at the same time.*/
    if(res < numberOfClients){
            pthread_mutex_lock( &mutex );
            while(resCount < numberOfClients){
                pthread_cond_wait(&c, &mutex);
            }
            pthread_mutex_unlock( &mutex );
        
    }else{
        
        pthread_mutex_lock( &mutex );
        int n = numberOfClients;
        
        /*The codes below for sorting*/
        char *clients[1010]; //array to store only numberOfClients clients according to their socket numbers, mapping their socket numbers to indexes from 0 to numberOfClients-1

        int sc[1010]; //store the scores
        for(int i = 0; i < n; i++){
            clients[i] = (char*) malloc(30*sizeof(char*));

        }
        int k = 0;
        for(int j = firstSocket; j < n+firstSocket; j++){
            if(strcmp(Lname[j], "") == 0){ //skip not used socket
                n++;
                continue;
            }
            sc[k] = scores[j];
            strcpy(clients[k], Lname[j]);
            printf("Sorted!\n");
            fflush( stdout );
            printf("%s + ", Lname[j]);
            printf("Scores: %i\n", scores[j]);
            fflush( stdout );
            k++;
        }


        //to sort
        for(int i = 0; i < n-1; i++){
            for(int j = 0; j < n-1; j++){

                if(sc[j] < sc[j+1]){
                    int temp1;
                    char *temp2;
                    temp1 = sc[j];
                    temp2 = clients[j];
                    sc[j] = sc[j+1];
                    clients[j] = clients[j+1];
                    sc[j+1] = temp1;
                    clients[j+1] = temp2;
                }
            }
        }

        strcpy(R, "RESULT");
        /*Iterate through the *clients[] and sc[] arrays to write the results concatinating to R string*/
        for(int j = 0; j < n; j++){
            printf("Sorted!\n");
            fflush( stdout );
            printf("%s + ", clients[j]);
            printf("Scores: %i\n", sc[j]);
            fflush( stdout );

            sprintf(numbCl, "|%s", clients[j]);
            strcat(R, numbCl);
            sprintf(numbCl, "|%i", sc[j]);
            strcat(R, numbCl);
            printf("Done pr\n");
            fflush( stdout );
        }
        strcat(R, "\r\n");
        Lnum = 0;
        for(int i = 0; i < numberOfClients; i++){
            free(clients[i]);
        }
        pthread_cond_broadcast(&c);
        pthread_mutex_unlock( &mutex );
    }

    

    
    if (( cc = write( ssock, R, strlen(R))) < 0 ){
        /* This guy is dead */
        count = exitGroup(cc, count);
        close(ssock);
        pthread_exit( NULL );
    }

    //free(splitted);
    free(Lname[ssock]);
    close(ssock);
    pthread_mutex_lock( &mutex );
    numberOfClients = 0; //set the number of clients to initial 0
    pthread_mutex_unlock( &mutex );
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
    pthread_cond_init( &c, NULL );
    FILE *fin;
    int    i = 0, count = 0;
    char    buf[BUFSIZE];
    
    switch (argc)
    {
//        case    1:
//            // No args? let the OS choose a port and tell the user
//            rport = 1;
//            break;
        case    2:
            // User provides a port? then use it
            if((fin = fopen( argv[1], "rw" )) == NULL){
                break;
            }
            rport = 1;
            break;
        case    3:
            if((fin = fopen( argv[1], "rw" )) == NULL){
                break;
            }
            service = argv[2];
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
    
    while ( fgets( buf, BUFSIZE-1, fin ) != NULL && qCount < 128 )
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
    qCount++;
    qCount = qCount/2;
    printf("The number of questions: %i\n", qCount);
    fflush( stdout );
    for (;;)
    {
        int  ssock;
        
        alen = sizeof(fsin);
        ssock = accept( msock, (struct sockaddr *)&fsin, &alen );
                if (ssock < 0)
                {
                    fprintf( stderr, "accept: %s\n", strerror(errno) );
                    break;
                }
                printf( "A client has arrived for echoes.\n" );
                fflush( stdout );
        
        //initialize answers[i] array
        for(int i = 0; i < 100; i++){
            answer[i] = 0;
        }
        
        /* start working for this guy
          create thread to handle each client*/
        status = pthread_create(&thread, NULL, serveClient, (void *)ssock);
        if ( status != 0 )
        {
            printf( "pthread_create error %d.\n", status );
            break;
        }
        resCount = 0;
    }
    pthread_mutex_destroy( &mutex );
    pthread_exit( 0 );
    
    for(int i = 0; i < count; i++ ){
        printf("%s\n", lines[i]);
        free(lines[i]);
    }
    fclose(fin);
    
}




