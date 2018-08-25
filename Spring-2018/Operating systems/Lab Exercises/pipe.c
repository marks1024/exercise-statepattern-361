//
//  pipe.c
//  
//
//  Created by Dana on 23.02.2018.
//

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

#define BFSZ 128
#define CMDLEN 80

int main(int argc, char *argv[]) {
    int fds[2];                      // an array that will hold two file descriptors
    pipe(fds);                       // populates fds with two file descriptors
    pid_t pid = fork();              // create child process that is a clone of the parent
    
    if (pid == 0) {                  // if pid == 0, then this is the child process
        dup2(fds[0], STDIN_FILENO);    // fds[0] (the read end of pipe) donates its data to file descriptor 0
        close(fds[0]);                 // file descriptor no longer needed in child since stdin is a copy
        close(fds[1]);                 // file descriptor unused in child
        char *argv[] = {"sort", NULL}; // create argument vector
        execvp(argv[0], argv);         // run sort command
    } else {
        close(fds[0]);
        const char *words[] = {"pear", "peach", "apple"};
        // write input to the writable file descriptor so it can be read in from child:
        size_t numwords = sizeof(words)/sizeof(words[0]);
        for (size_t i = 0; i < numwords; i++) {
            dprintf(fds[1], "%s\n", words[i]);
        }
        
        // send EOF so child can continue (child blocks until all input has been processed):
        close(fds[1]);
    }
    int status;
    pid_t wpid = waitpid(pid, &status, 0);
    return 0;
    //return wpid == wpid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

//int main(int argc, char* argv[])
//{
//    int pid;
//    int fds[2];
//    pipe(fds);
//
//    pid = fork();
//    if(pid != 0){
//        dup2(fds[1], 1);
//        execlp("ls", "ls", NULL);
//    }else{
//        dup2(fds[0], 0);
//        execlp("sort", "sort", NULL);
//    }
//
//
//    return 0;
//}



