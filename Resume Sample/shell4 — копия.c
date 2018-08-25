/*
 **    This program is a very simple shell that only handles
 **    single word commands (no arguments).
 **    Type "quit" to quit.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include<fcntl.h>

#include<sys/stat.h>

#define BFSZ 128000
#define CMDLEN 80

//char **split_line(char *input){
//
//    char **comm;
//    comm = (char**) malloc(40*sizeof(char**));
//    const char space[2] = " ";
//    char *token;
//    token = strtok(input, space);
//    int i = 0;
//    while(token != NULL){
//        (comm[i]) = token;
//        i++;
//        token = strtok(NULL, space);
//    }
//    comm[i] = NULL;
//    return comm;
//}


int backup_redirect(int tf, int bf, int rf, off_t prev, off_t curr);
int pipng_processes(int from, int to, char **comm);

int main(int argc, char* argv[])
{
    int pid;
    int status;
    int i, backupFile, tempFile, input, append, output, pipesCount;
    char command[CMDLEN];
    char begin[CMDLEN] = "Program begins.\n";
    char prompt[CMDLEN] = "Please enter a command:   ";
    char error[CMDLEN] = "Command failed\n";
    
    char buf[BFSZ];
    
    char **splitted;
    splitted = (char**) malloc(40*sizeof(char**));
    
    
    if((backupFile = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | O_APPEND)) < -1){
        exit(-1);
    }
    
    if((tempFile = open("./tempOut.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | O_APPEND)) < -1){
        exit(-1);
    }
    
    lseek(backupFile, 0, SEEK_END);
    //prompt = "Program begins.\n";
    printf( "%s", begin);
    write(backupFile, begin, strlen(begin));
    
    off_t fileSize = lseek(tempFile, 0, SEEK_END);
    off_t prevSize = 0;
    
    for (;;)
    {
        
        input = 0;
        output = 0;
        append = 0;
        //printf( "Please enter a command:   " );
        printf( "%s", prompt);
        write(backupFile, prompt, strlen(prompt));
        
        //        int fds[2]; //create array of two file descriptors
        //        pipe(fds); //create pipe and feed it with fds
        
        fgets( command, CMDLEN, stdin );
        write(backupFile, command, strlen(command));
        
        printf("1");
        printf("2");
        command[strlen(command)-1] = '\0';
        
        // https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
        const char space[2] = " ";
        char *token;
        token = strtok(command, space); //pinter to the first element of the splitted string
        int i = 0;
        int pipesCount = 0;
        
        int pipesPos[10]; // to store pipes positions
        while(token != NULL){
            (splitted[i]) = token; //store commands in splitted
            if(strcmp(splitted[i], "<") == 0){
                input = i + 1;
            }
            if(strcmp(splitted[i], ">") == 0){
                output = i + 1;
            }
            if(strcmp(splitted[i], ">>") == 0){
                append = i + 1;
            }
            if(strcmp(splitted[i], "|") == 0){
                pipesPos[pipesCount] = i;
//                splitted[i] = NULL;
                pipesCount++;
//                i--;
            }
            i++;
            token = strtok(NULL, space);
        }
        splitted[i] = NULL;
        
        //splitted = split_line(command);
        
        printf("3");
        
        if ( strcmp(splitted[0], "quit") == 0 ) //break conition
            break;
        
        int fds[2]; //aray of two file descriptors
         //create a pipe
        
        pid = fork(); //create a first child to execute the program
        printf("4");
        
        if ( pid < 0 )
        {
            printf( "Error in fork.\n" );
            exit(-1);
        }
        if ( pid != 0 )
        {
            printf("7");
            //runs in the background, rather than the foreground.
            if(command[strlen(command)-2] != '&'){
                waitpid( pid, &status, 0 );
            }
        }
        else
        {
            printf("5");
            
            if(pipesCount != 0){
                int j;
                int inp = 0;
                char *split;
//                char **comm;
//                comm = (char**) malloc(40*sizeof(char**));
//                const char p[2] = "|";
//                char *token;
//                token = strtok(splitted, p);
                
                for(j = 0; j < pipesCount; j++){
                    pipe(fds);
                    int s, f;
                    if(j == 0){
                        s = 0;
                    }else{
                        s = pipesPos[j-1] + 1;
                    }
                    //f = pipesPos[j + 1];
                    splitted[pipesPos[j]] = NULL;
                    
//                    for(int n = j; n < pipesPos[j]; n++){
//                        comm[n] = splitted[pipesPos[j] - n];
//                    }
                    
                    //pipng_processes(inp, fds[1], &splitted[j+2]);
                    pid = fork();
                    if(pid < -1){
                        printf( "Error in fork.\n" );
                        exit(-1);
                    }
                    if ( pid != 0 )
                    {
                        printf("7");
                        waitpid( pid, &status, 0 );
                        
                    }else{
                        if(inp != 0){
                            dup2(inp, 0);
                            close(inp);
                        }
                        if(fds[1] != 1){
                            dup2(fds[1], 1);
                            close(fds[1]);
                        }
                         execvp (splitted[s], splitted);
                    }
                    close(fds[1]);
                    inp = fds[0];
                    //free(comm);
                }
                if(inp != 0){
                    dup2(inp, 0);
                }
                dup2(tempFile, 1);
                execvp(splitted[pipesPos[j-1] + 1], splitted);
                
                printf( "%s", error);
                
                //write(backupFile, error, strlen(error));
                
                printf("6");
                exit(-1);

            }else{
            
            if(input != 0){
                int fin = open(splitted[input], O_RDONLY);
                dup2(fin, 0);
                splitted[input-1] = NULL;
                splitted[input] = NULL;
                close(fin);
                
            }else if(output != 0){
                splitted[output-1] = NULL;
                splitted[output] = NULL;
                
            }else if(append != 0){
                
                splitted[append-1] = NULL;
                splitted[append] = NULL;
                
            }
            dup2(tempFile, 1);
            execvp(splitted[0], splitted);
            
            printf( "%s", error);
            
            //write(backupFile, error, strlen(error));
            
            printf("6");
            exit(-1);
            }
        }
        
        prevSize = fileSize;
        fileSize = lseek(tempFile, 0, SEEK_END);
        
        if(input != 0){
            
            if(output != 0){
                int fout = open(splitted[output], O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC);
                backup_redirect(tempFile, backupFile, fout, prevSize, fileSize);
                close(fout);
            }else if(append != 0){
                int fapp = open(splitted[append], O_WRONLY | O_APPEND);
                backup_redirect(tempFile, backupFile, fapp, prevSize, fileSize);
                close(fapp);
            }else{
                backup_redirect(tempFile, backupFile, 0, prevSize, fileSize);
            }
            
        }else if(output != 0){
            int f2 = open(splitted[output], O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC);
            backup_redirect(tempFile, backupFile, f2, prevSize, fileSize);
            close(f2);
            
        }else if(append != 0){
            int f3 = open(splitted[append], O_WRONLY | O_APPEND);
            backup_redirect(tempFile, backupFile, f3, prevSize, fileSize);
            close(f3);
        }else{
            backup_redirect(tempFile, backupFile, 0, prevSize, fileSize);
        }
        
    }
    close(backupFile);
    close(tempFile);
    
    if (remove("./tempOut.txt") != 0){
        printf("Unable to delete the file");
        exit(-1);
    }
    
    free(splitted);
    
    return 0;
}

int backup_redirect(int tf, int bf, int rf, off_t prev, off_t curr){
    char buf[BFSZ];
    
    lseek(tf, prev, SEEK_SET);
    read(tf, buf, curr-prev);
    buf[curr-prev] = '\0';
    
    if(rf != 0){
        
        write(rf, buf, curr-prev);
        write(bf, buf, curr-prev);
        
    }else{
        printf("%s", buf);
        write(bf, buf, curr-prev);
    }
    return 0;
    
}

//int pipng_processes(int from, int to, char **comm){
//    int pid;
//    int status;
//    pid = fork();
//    if(pid < -1){
//        printf( "Error in fork.\n" );
//        exit(-1);
//    }
//    if ( pid != 0 )
//    {
//        printf("7");
//       waitpid( pid, &status, 0 );
//
//    }else{
//        if(to != 0){
//            dup2(to, 0);
//            close(to);
//        }
//        if(from != 1){
//            dup2(from, 1);
//            close(from);
//        }
//    return execvp (comm[0], comm);
//    }
//    return pid;
//
//}

