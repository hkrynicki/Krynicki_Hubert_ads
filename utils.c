#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

struct single_game_info{
    int id;
    int lineNumber;
};
struct single_game_info* catalog;

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
        fprintf(file, "START_HEADER\n");
        fprintf(file, "%s - ",getCurrentTime());
    }
    else if(strcmp(action,"HEADER") == 0){
        char *pName = va_arg(v, char*);
        char mark = va_arg(v, char);
        fprintf(file, "%s '%c'  ", pName, mark);
    }
    else if(strcmp(action,"START_GAME") == 0){
        fprintf(file, "\nSTART_GAME\n");
    }
    else if(strcmp(action,"MOVE") != 0){
        fprintf(file, "%s\n",action);
    }
    else{        
        int fieldNum = va_arg(v, int);
        char mark = va_arg(v, char);
        char *playerName = va_arg(v, char*);
        fprintf(file, "%u %c %s \n", fieldNum, mark, playerName);   
    }
    fclose(file);     
}


/**
 * Read gameplay id and line position in file
 * 
 * @return false if file does not exist, true if operation was succesfull
*/
bool readTitlesFromHistoryFile(){
    FILE *stream;
    stream = fopen("./data/history.txt", "r");
    if(stream == NULL){
        printf("No records to display, play first game");
        return false;             
    }
    else{        
        int catalogId = 0;
        catalog = malloc(sizeof(struct single_game_info));     
        char temp[80];
        for(int lineNumber = 0; fgets(temp, 80, stream) != NULL; lineNumber++){            
            if(strcmp(temp, "START_HEADER\n") == 0){
                fgets(temp, 80, stream);
                printf("%u  -   %s",catalogId ,temp);

                catalog[catalogId].id = catalogId;
                catalog[catalogId].lineNumber = lineNumber + 3;
                printf(" %u %u\n", catalog[catalogId].id, catalog[catalogId].lineNumber);
                catalogId++;
                lineNumber++;                
                catalog = realloc(catalog,((catalogId+1) * sizeof(struct single_game_info)));
                 
            }            
        }                    
    }    
    free(catalog);  
    fclose(stream);
    return true;
}




/**
 * Check if string is empty - 
 *      containes nothing except spaces and control characters
 * 
 * @param string to be checked
 * @return boolean 
*/
bool isStringEmpty(char s[]){    
    //Useful if string contain white-spaces
    bool containsAnyLetter = false;
    for(int i = 0; i < strlen(s) ; i++){
        if(iscntrl(s[i])){            
            return true;
        }
        else if(isalnum(s[i])){
            containsAnyLetter = true;
        }                
    }
    //If string is composed of white-spaces only return true
    if(containsAnyLetter != true){
        return true;
    }         
    return false;
};
/**
 * Remove newLine from string, especially useful after fgets
 * 
 * @param string to be modified
*/
void removeNewLineFromString(char *s){
    int len = strlen(s);
    if(s[len-1] == '\n'){
        s[len-1] = 0;
    }
}

/**
 * Clear input stream
*/
void flushAfterString(char *string){
    char *temp;
    if(temp=strchr(string, '\n')){//check exist newline
        *temp = 0;
    }
    else{
        scanf("%*[^\n]");scanf("%*c");//clear upto newline
    }
    removeNewLineFromString(string);
}
void flushAfterChar(char ch){    
     if(ch != '\n'){//check exist newline                
            scanf("%*[^\n]");scanf("%*c");//clear upto newline
        }
}