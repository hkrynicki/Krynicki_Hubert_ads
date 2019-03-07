#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#include "structures.h"
/**
 * Get current system time
 * 
 * @return string with time info
*/
char* getCurrentTime(){
    time_t currentTime;
    char* timeString;
    
    currentTime = time(NULL);

    if (currentTime == ((time_t)-1))
    {
        printf("Failure to obtain the current time.\n");
        return "Time not available";
    }    
    timeString = ctime(&currentTime);

    if (timeString == NULL)
    {
        printf("Failure to convert the current time.\n");
        return "Time not available";
    }

    int len = strlen(timeString);
    if(timeString[len-1] == '\n'){
        timeString[len-1] = 0;
    }
    return timeString;
}
/**
 * Writes info, action or move details to txt file
 * 
 * @param 
 *  Required - type of action(string)
 *  Optional - fieldNum(int), mark(char), playerName(string)
*/
void addToHistoryFile(char *action, ...){        
    FILE *file;
    file = fopen("./data/history.txt", "a");    

    va_list v;
    va_start(v, action);
    if(strcmp(action,"START_HEADER") == 0){
        fprintf(file, "\nSTART_HEADER\n");
        fprintf(file, "%s - ",getCurrentTime());
    }
    else if(strcmp(action,"HEADER") == 0){
        char *pName = va_arg(v, char*);
        char mark = va_arg(v, char);
        fprintf(file, "%s '%c'  ", pName, mark);
    }    
    else if(strcmp(action,"MOVE") != 0){
        fprintf(file, "\n%s",action);
    }
    else{        
        int fieldNum = va_arg(v, int);
        char mark = va_arg(v, char);
        char *playerName = va_arg(v, char*);
        fprintf(file, "\n%u %c %s", fieldNum, mark, playerName);   
    }
    fclose(file);     
}
