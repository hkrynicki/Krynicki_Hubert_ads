#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>


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
 * Validate input 
 * 
 * @param string to be validated
 * @result : 
 *      -1 for invalid input
 *     0-8 for valid
*/
int validateMarkInput(char *move){
    if(strlen(move) != 2){
        return -1;
    }    
    int row;
    int col;
    int result = 0;
    if(isalpha(move[0])){        
        move[0] = toupper(move[0]);    
    }
    else if(isalpha(move[1])){
        move[1] = toupper(move[1]); 
    }   
   
    if( move[0] >= 'A' && move[0] <= 'C' && move[1] >= '1' && move[1] <= '3'){            
        row = 1;
        col = 0;                      
    }
    else if (move[1] >= 'A' && move[1] <= 'C' && move[0] >= '1' && move[0] <= '3'){
        row = 0;
        col = 1;  
    }
    else
    {
        return -1;
    }        
    for(int i = 'A'; i <= 'C' ;i++){
        if(move[col] == i){
            result += i - 'A';
        }
    }
    for(int i = '1'; i <= '3'; i++){
        if(move[row] == i){
            result += (i - '1') * 3;
        }
    }            
    
    return result; 
}
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

/**
 * Purpose of this function is to centralise all instances of 
 *  user input gathering and validation
 * 
*/
#define MAIN 0
#define DETERMINE_PLAYERS 1
#define DETERMINE_MARKS 2
#define GAME_ACTION 3
#define GAME_REPLAY 4
#define STOP_REPLAY 5

int centralInputGatheringUnit(int option, ...){
    char choice;
    char achoice[5];
    /** 
     *  @return
     *  0 - for exit
     *  1 - for new game
     *  2 - for replay
    */
    if(option == MAIN){
        choice = getchar();
        flushAfterChar(choice);
        return (choice - '0');
    }
    /** 
     *  @param - player name 
     *  @return
     *  0 - for wrong name
     *  1 - for valid name  
    */
    if(option == DETERMINE_PLAYERS){
           va_list v;
           va_start(v, option);
           char *pName = va_arg(v, char*);           
           fgets(pName, 20, stdin);           
           flushAfterString(pName);
           if(isStringEmpty(pName)){               
               return 0;
           }           
           return 1;
    }
    /**
     * @param - player mark 
     * @return
     * 0 - for wrong mark
     * 'O' or 'X' - for valid mark 
    */
    if(option == DETERMINE_MARKS){        
        char pMark = getchar();
        flushAfterChar(pMark);
        if(pMark == 'o' || pMark == 'O' || pMark == '0'){            
            return 'O';
        }
        else if(pMark == 'x' || pMark == 'X'){            
            return 'X';
        }
        else{
            return 0;
        }
    }
    /**
     * @return
     * 11 - exit
     * 10 - redo
     * 9 - undo 
     * 0-8 - field number
     * -1 - for invalid field
    */
    if(option == GAME_ACTION){
        fgets(achoice, 5, stdin);
        flushAfterString(achoice);
        int fieldNum = validateMarkInput(achoice);
        if(strcmp(achoice, "0") == 0 || strcmp(achoice, "0") == 0){
            return 11;
        }
        else if(strcmp(achoice, "redo") == 0 || strcmp(achoice, "REDO") == 0){
            return 10;
        }
        else if(strcmp(achoice, "undo") == 0 || strcmp(achoice, "UNDO") == 0){
            return 9;
        }
        else if(fieldNum >= 0){
            return fieldNum;
        }
        else{
            return -1;
        }        
    }
    /**
     * @return
     * -1 - for invalid input
     * 0+ - for valid
    */
    if(option == GAME_REPLAY){
        int choice = -1;
        fgets(achoice, 5, stdin);
        flushAfterString(achoice);
        bool isValid = true;
        for(int i = 0; i < strlen(achoice); i++){
            if(isdigit(achoice[i]) == 0){                
                isValid = false;
                break;
            }
        }
        if(isValid){
            sscanf(achoice,"%d", &choice);                    
        }                
        return choice;
    }
    /**
     * @return
     * any char 
    */
    if(option == STOP_REPLAY){
        char temp = getchar();
        flushAfterChar(temp);
        return temp;
    }
    /**
     * Default
    */
    return -1;
}