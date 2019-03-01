#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

//Usability methods


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
    if(strcmp(action,"HEADER") == 0){
        char *pName = va_arg(v, char*);
        char mark = va_arg(v, char);
        fprintf(file, "%s - %c\n", pName, mark);
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
void removeNewLineFromString(char s[]){
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