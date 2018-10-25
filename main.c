//
//  main.c
//
//
//  Created by Emeka Opara on 9/18/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

char ** inputRead();
int executeCommands(char ***, int , int , int );
void organizeAndExecute(char **);

char ***alloc_array(int x, int y) {
    char ***a = calloc(x, sizeof(char **));
    int i;
    for(i = 0; i != x; i++) {
        a[i] = calloc(y, sizeof(char *));
    }
    return a;
}


static void redirect(int oldp, int newp){

    if(oldp != newp){
        if(dup2(oldp,newp) != -1)   {
            close(oldp);
        }
        else{
            exit(EXIT_FAILURE);
        }
    }
}

void run(char **cmd, int input, int out){
    redirect(input, STDIN_FILENO);
    redirect(out, STDOUT_FILENO);

    if(execvp(cmd[0], cmd) == -1) {
        perror(cmd[0]);
    }
    //exit(0);
}

int main(int argc, char *argv[]) {

    char **parseChars;
    char ***cmds;
    int i = 0;
    if (argc <= 1) {
        argv[1] = "l";
    }
    printf("my_shell\n");

    while (1) {
        if (strcmp(argv[1], "-n") != 0) {
            printf("shell:");
        }
        cmds = alloc_array(20, 20);
        parseChars = inputRead();
        organizeAndExecute(parseChars);
    }
    free(parseChars);
    free(cmds);
    printf("\n");
    return 0;
}

