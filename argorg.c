//
//  argorg.c
//
//
//  Created by Emeka Opara on 9/15/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int executeCommands(char ***, int , int , int );
char ***alloc_array(int , int );
void organizeAndExecute(char **parseChars){
    char ***cmds = alloc_array(20,20);
    int lengthArray = 0;
    int background = 0;
    int redirectOut = 0;
    int redirectIn = 0;
    int i = 0, j = 0, count = 0;

    //Check for special characters
    lengthArray = 0;
    while(parseChars[lengthArray] != NULL){
        lengthArray = lengthArray + 1;
    }

    for(i=0;i<lengthArray;i++){
        if(strcmp("|", parseChars[i]) == 0){
            count = count +  1;
            j=0;
        }
        else if(strcmp("&", parseChars[i]) == 0){
            //i = i + 1;
            background = 1;
        }
        else if(strcmp(">", parseChars[i]) == 0){
            //cmds[count][j] = NULL;
            count = count + 1;
            j = 0;
            cmds[count][j] = parseChars[i];
            cmds[count][j+1] = parseChars[i+1];
            cmds[count][j+2] = NULL;
            redirectOut = 1;
            //count = count + 1;
            j =0;
            i = i + 1;
            continue;
        }
        else if(strcmp("<", parseChars[i]) == 0){
            cmds[count][j] = NULL;
            //count = count + 1;
            //j = 0;
            cmds[count][j] = parseChars[i+1];
            redirectIn = 1;
            //count = count + 1;
            j =0;
            i = i + 1;
            continue;
        }
        else{
            cmds[count][j] = parseChars[i];
            j = j + 1;

        }
        if(i+1>lengthArray){
            cmds[count][j] = parseChars[i];
        }
    }

    executeCommands(cmds, background, redirectOut, redirectIn);
}
