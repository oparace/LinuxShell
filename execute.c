//
//  execute.c
//
//
//  Created by Emeka Opara on 9/14/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
void run(char **, int, int);
int executeCommands(char ***cmds, int background, int redirectOut, int redirectIn){

    pid_t pid;
    int p[2];
    int input = 0;
    const int READ = 0;
    const int WRITE = 1;
    int i = 0, j, status, temp;

    while (cmds[i][0] != NULL)
    {

        int p[2];
        pid_t pid;

        if(strcmp(cmds[i][0], ">") == 0 || strcmp(cmds[i][0], "<") == 0){
            i++;
            continue;
        }

        if(pipe(p) == -1){
            exit(EXIT_FAILURE);
        }
        else if((pid = fork()) == -1){
            exit(EXIT_FAILURE);
        }
        else if(pid == 0) //Child
        {
            // > Logic for unlimited output redirects
            if(cmds[i+1][0] != NULL && strcmp(cmds[i+1][0], ">") == 0){
                temp = i + 1;
                while(strcmp(cmds[temp][0], ">") == 0){
                    p[1] = creat(cmds[temp][1] , 0644);
                    temp++;
                    if(cmds[temp][0] == NULL){
                        break;
                    }
                }
                run(cmds[i], input, p[1]);
            }

            else if(cmds[i+1][0] != NULL && strcmp(cmds[i+1][0], "<") == 0){
                p[0] = open(cmds[i+1][1], O_RDONLY);
                run(cmds[i], input, p[0]);
            }

            else{
                if(cmds[i+1][0] != NULL)
                    run(cmds[i], input, p[1]);
                else{
                    run(cmds[i], input, STDOUT_FILENO);
                }
                exit(EXIT_FAILURE);
            }
        }
        else{ //Parent

            if(background == 0){
                waitpid(pid, &status, WUNTRACED);
                wait(NULL);
            }
            else if(background == 1)
            {
                //waitpid(fork,&status,WUNTRACED);
            }

            close(p[1]);
            input = p[0];
            i++;
        }
    }

    if(background == 1){
        printf("[%d] %d\n", getppid(), getpid());
    }
    background = 0;
    return 0;
}
