//
//  inputread.c
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
#include <ctype.h>

char ** inputRead()
{

    int bufferSize = 1000;
    char input[bufferSize];
    int wordNum = 0;
    int charNum = 0;
    int i;
    int flag = 0;

    //fgets(input, sizeof(input), stdin);
    //Read from input stream
    if(fgets(input, sizeof(input), stdin) == NULL){
        printf("\n");
        exit(0);
    }
    int length = strlen(input);

    //Dynamically allocate string array
    char **parseChars = malloc(length * sizeof(char *));
    for (i = 0; i < length; ++i) {
        parseChars[i] = (char *)malloc(length+1);
    }
    //Custom Tokenize State Machine
    for(i = 0; i < length; i++)
    {
        if(!isspace(input[i]))
        {
            if(input[i] == '<' || input[i] == '>'
               || input[i] == '|' || input[i] == '&')
            {
                charNum = 0;
                parseChars[wordNum][charNum] = input[i];
                if(!isspace(input[i+1]))
                    wordNum++;
            }
            else //if regular token
            {
                parseChars[wordNum][charNum] = input[i];
                charNum++;
                if(input[i+1] == '<' || input[i+1] == '>'
                   || input[i+1] == '|' || input[i+1] == '&')
                {
                    wordNum++;
                }
            }
        }
        else //is space
        {
            if(!isspace(input[i-1]) && i != 0){
                wordNum++;
                charNum = 0;
            }
        }
    }
    parseChars[wordNum] = NULL;
    return parseChars;
}
