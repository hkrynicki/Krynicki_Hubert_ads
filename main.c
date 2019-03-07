#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#include "input-gathering.h"
#include "stack.h"
#include "utils.h"
#include "structures.h"

/**
 * For input gathering 
 * */
#define MAIN 0
#define DETERMINE_PLAYERS 1
#define DETERMINE_MARKS 2
#define GAME_ACTION 3
#define GAME_REPLAY 4
#define STOP_REPLAY 5

const int gameSize = 3;
int turn = 1;

struct player p1 = {"Player1", 'X'};
struct player p2 = {"Player2", 'O'};
struct player currentPlayer;
struct gameboard gb = {3};


void printPlayers(){
    printf("\n %s  -  '%c'",p1.name, p1.mark);
    printf("\n %s  -  '%c'",p2.name, p2.mark);   
}
void printGameboard(){

    char cols[3] = {'A','B','C'};
    char rows[3] = {'1','2','3'};      

    printf("\n\n      %c     %c     %c\n", cols[0], cols[1], cols[2]);
    printf("         |     |     \n");
    printf("  %c   %c  |  %c  |  %c  \n",rows[0], gb.fields[0], gb.fields[1], gb.fields[2]);
    printf("    _____|_____|_____\n");
    printf("         |     |     \n");
    printf("  %c   %c  |  %c  |  %c  \n",rows[1], gb.fields[3], gb.fields[4], gb.fields[5]);
    printf("    _____|_____|_____\n");
    printf("         |     |     \n");
    printf("  %c   %c  |  %c  |  %c  \n",rows[2], gb.fields[6], gb.fields[7], gb.fields[8]);
    printf("         |     |     \n\n");
    
}
void printStartMenu(){
    printf("\n Welcome to final and superior TicTacToe game, choose : \n");
    printf(" 0 - to exit\n");
    printf(" 1 - to start new game\n");
    printf(" 2 - to replay one of old matches\n");
    printf(" Your choice : ");    
}
void printGameMenu(){
    printf("\n %s turn\n Choose field by writing 'A1', '2C' etc\n", currentPlayer.name);
    printf(" or type 'undo' to revert one move \n");
    printf(" or type 'redo' to cancel revert \n");
    printf(" or type '0' to finish :   ");
}
/**
 * Remove all marks from gameboard, clean stacks, reset turn counter
*/
void cleanAfterMatch(){
    for(int i = 0; i < 9; i++){
        gb.fields[i] = ' ';
    }
    cleanBothStacks();
    turn = 1;
}
/**
 * Ask players for names and assign marks
 * 
 * @param struct player : p1, p2  
*/
void determinePlayers(){

    //Player1
    printf(" Welcome, Player 1 please insert your name:   ");       
    if(centralInputGatheringUnit(DETERMINE_PLAYERS, p1.name) == 0){
        strcpy(p1.name, "Player1");
        printf(" Inserted name is not valid, you have been assigned name 'Player 1'\n");    
    }  

    printf(" Would you like noughts('O') or crosses('X')? \n Enter 'O' or 'X':    ");       
    int mark = centralInputGatheringUnit(DETERMINE_MARKS);
    if(mark == 0){        
        p1.mark = 'X';
        printf("\n Inserted character is invalid, you have been assigned crosses 'X'\n");
    }
    else{
        p1.mark = mark;
    }  

    //Player2
    printf("\n Player 2 please insert your name:   ");       
    if(centralInputGatheringUnit(DETERMINE_PLAYERS, p2.name) == 0){
        strcpy(p2.name, "Player2");
        printf(" Inserted name is not valid, you have been assigned name 'Player 2'\n"); 
    }
    //If Player1 chose crosses than Player2 will be assigned noughts
    if(p1.mark == 'X'){
        p2.mark = 'O';
    }
    else{
        p2.mark = 'X';
    }
    printf(" You have been assigned %c\n",p2.mark);
}

/**
 * Calculate current player based on a turn
 * 
 * @param current turn
*/
void calcCurrentPlayer(int turn){
    if(turn == 1 || turn == 3 || turn == 5 || turn == 7 || turn == 9){
            currentPlayer = p1;
        }        
    else{
        currentPlayer = p2;
    } 
}
/**
 * Mark field in gameboard, push field number to stack
 * 
 * @param gameboard, field to mark, mark type
*/
void applyMarkToGameBoard(int fieldNum){    
    gb.fields[fieldNum] = currentPlayer.mark;    
    pushToStack(fieldNum);              
}
/**
 * Revert newest turn
 * 
 * @return true if revert was succesfull
*/
bool undoTurn(){
    if(turn > 1){        
        int fieldNum = popFromUndoStack();
        gb.fields[fieldNum] = ' ';
        turn = turn - 2;
        return true;
    }
    printf(" No moves to revert, choose other option :  ");
    return false;   

}
/**
 * Cancel revert
 * 
 * @return true if redo was succesfull
*/
bool redoTurn(){    
    int fieldNum = popFromRedoStack();
    if(fieldNum != -1){        
        gb.fields[fieldNum] = currentPlayer.mark;
        return true;
    }
    printf(" Redo not available, choose other option :  ");
    return false;   
}
/**
 * Check if field is not already marked
 * 
 * @param field number, gameboard
 * @return true if field is not marked
*/
bool fieldNotMarked(int fieldNum){
    char c = gb.fields[fieldNum];
    if(c != 'X' && c != 'O'){
        return true;
    }
    return false;
}
/**
 * Check if someone win by comparing values in rows, columns and diagonally
 * 
 * @param gameboard
 * @return true if someone won
*/
bool didAnyoneWin(){
    for(char c = 'O'; c <= 'X'; c = c + 9){
            //Check rows
        for(int i = 0; i<7; i = i + 3){
            if(gb.fields[i] == c && gb.fields[i+1] ==  c && gb.fields[i+2] == c){
                return true;
            }
        }
        //Check columns
        for(int i = 0; i < 3; i++){
            if(gb.fields[i] ==  c && gb.fields[i+3] == c && gb.fields[i+6] == c){
                return true;
            }
        }
        //Check diagonal
        for(int i = 0; i < 3; i = i + 3){
            if(gb.fields[i] == c && gb.fields[i+4] == c && gb.fields[i+8] == c){
                return true;
            }
        }
        for(int i = 6; i > 3; i = i - 3){
            if(gb.fields[i] ==  c && gb.fields[i-2]  == c && gb.fields[i-4] == c){
                return true;
            }
        }
    }    
    return false;
}

struct single_game_info* catalog;
struct single_move_details* gameplay;
int gameplaySize;

/**
 * Read gameplay id and line position in file
 * 
 * @return 
 *  -   0 if file not exist, is empty
 *  -   number of lines
*/  
int readTitlesFromHistoryFile(){
    FILE *stream;
    stream = fopen("./data/history.txt", "r");
    int maxCatalogId = 0;
    if(stream == NULL){        
        return maxCatalogId;             
    }
    else{             
        catalog = malloc(sizeof(struct single_game_info));     
        char temp[80];
        for(int lineNumber = 0; fgets(temp, 80, stream) != NULL; lineNumber++){                     
            if(strcmp(temp, "START_HEADER\n") == 0){
                fgets(temp, 80, stream);
                printf(" %u  -   %s",maxCatalogId ,temp);                
                catalog[maxCatalogId].id = maxCatalogId;
                catalog[maxCatalogId].lineNumber = lineNumber + 2;                  

                const char s[2] = "-";
                char *token;
                token = strtok(temp, s);
                token = strtok(NULL, s);
                sscanf(token, "%s '%c' %s '%c'", catalog[maxCatalogId].name1,&(catalog[maxCatalogId]).mark1, catalog[maxCatalogId].name2, &(catalog[maxCatalogId]).mark2);
                                
                maxCatalogId++;
                lineNumber++;
                catalog = realloc(catalog,((maxCatalogId+1) * sizeof(struct single_game_info)));                 
            }            
        }                    
    }         
    fclose(stream);
    return maxCatalogId;
}
/**
 * Read moves from file for particular gameplay
 * 
 * @param line to start reading from
*/
void readGameDetailsFromHistoryFile(int line){
    FILE *stream;
    stream = fopen("./data/history.txt", "r");
    char temp[80];
    int initialSize = 10;
    int index = 0;
    gameplay = malloc(initialSize * sizeof(struct single_move_details));
    gameplaySize = 0;
    for(int i = 0; fgets(temp, 80, stream) != NULL; i++){              
        if(i < line){
            continue;
        }
        else if(strcmp(temp, "START_HEADER\n") == 0){
            break;
        }
        else{            
            if(index % 10 == 0){
                gameplay = realloc(gameplay, (initialSize+index+1) * sizeof(struct single_move_details));                
            }
            gameplaySize++;
            if(strcmp(temp,"UNDO\n") == 0 || strcmp(temp,"UNDO") == 0){
                strcpy(gameplay[index].action,"UNDO");                
            }
            else if(strcmp(temp,"REDO\n") == 0 || strcmp(temp,"REDO") == 0){
                strcpy(gameplay[index].action,"REDO");
            }
            else{                
                strcpy(gameplay[index].action,"MOVE");                
                sscanf(temp, "%d", &(gameplay[index]).field);                 
            }
            index++;
        }        
    }
    fclose(stream);
}


int main()
{
    printf("\n\n---------------------Game started--------------------- \n\n");    
    
    
    do{
        bool exit = false;
        printStartMenu();
        int choice = centralInputGatheringUnit(MAIN);
        if( choice == 0){
            break;
        }        
        else if(choice == 1){
            determinePlayers();             
            addToHistoryFile("START_HEADER");
            addToHistoryFile("HEADER",p1.name, p1.mark);
            addToHistoryFile("HEADER",p2.name, p2.mark);                  
            do{          
                char field[5];
                calcCurrentPlayer(turn);       
                printPlayers(p1, p2);
                printGameboard(gb);                
                bool moveIsValid;
                
                printGameMenu();
                do{                                         
                    int fieldNum = centralInputGatheringUnit(GAME_ACTION);
                    if(fieldNum == 11){
                        moveIsValid = true;
                        exit = true;                
                    }
                    else if(fieldNum == 10){
                        moveIsValid = redoTurn();
                        if(moveIsValid){
                            addToHistoryFile("REDO");
                        }    
                    }
                    else if(fieldNum == 9){
                        moveIsValid = undoTurn(); 
                        if(moveIsValid){
                            addToHistoryFile("UNDO");
                        }               
                    }                    
                    else if(fieldNum != -1){                
                        if(fieldNotMarked(fieldNum)){
                            moveIsValid = true;
                            applyMarkToGameBoard(fieldNum);
                            addToHistoryFile("MOVE", fieldNum, currentPlayer.mark, currentPlayer.name);                    
                            if(didAnyoneWin()){
                                printGameboard();
                                printf(" %s congratulations! You won\n", currentPlayer.name);
                                exit = true;
                            }
                        }
                        else{
                            printf(" Choose other field, this is already marked :   ");
                            moveIsValid = false;
                        }                
                    }                  
                    else{
                        printf(" Please insert correct field number :   ");
                        moveIsValid = false;
                    }
                }while(!moveIsValid);
                
                turn += 1;
                if(turn == 10){
                    printf(" Game finished in a tie");
                    exit = true;
                }
            }while(exit != true);
            cleanAfterMatch();            
        }   
        else if(choice == 2){
            int size = readTitlesFromHistoryFile();            
            if(size > 0){                
                printf("\n Please choose game to replay by typing number :   ");            
                int choice = centralInputGatheringUnit(GAME_REPLAY);         

                if(choice >= 0 && choice < size){                                  
                    readGameDetailsFromHistoryFile(catalog[choice].lineNumber);
                    strcpy(p1.name,catalog[choice].name1);
                    strcpy(p2.name,catalog[choice].name2);                   
                    p1.mark = catalog[choice].mark1;
                    p2.mark = catalog[choice].mark2;
                    if(gameplaySize == 0){
                        printf(" Game was terminated before first move\n");
                    }
                    for(int i = 0; i < gameplaySize; i++){                        
                        printf("\n Enter 0 to stop, anything else to continue :  ");
                        char c = centralInputGatheringUnit(STOP_REPLAY);
                        if(c == '0'){
                            break;
                        }                                             
                        calcCurrentPlayer(turn);                                                                          
                        if(strcmp(gameplay[i].action, "UNDO") == 0){                                                        
                            bool temp1 = undoTurn();
                            calcCurrentPlayer(turn - 1);                            
                        }
                        else if(strcmp(gameplay[i].action, "REDO") == 0 ){                            
                            bool temp2 = redoTurn();
                            calcCurrentPlayer(turn - 1);                             
                        }
                        else{                            
                            int fieldNum = gameplay[i].field;
                            gb.fields[fieldNum] = currentPlayer.mark;
                            pushToStack(fieldNum);   
                        }
                        printf(" %s '%c'  -  %s", currentPlayer.name, currentPlayer.mark, gameplay[i].action);                        
                        printGameboard(gb);
                        turn++;
                    }
                    if(didAnyoneWin()){
                        printf(" %s congratulations! You won\n", currentPlayer.name);                        
                    }
                    else if(turn == 10){
                        printf(" Game finished in a tie");
                    }
                }
                else{
                    printf(" No records to display, choose other number\n");
                }                
            }
            else{
                printf(" No records to display, choose other number\n");
            }            
            cleanAfterMatch();
        }
        else{
            printf(" Wrong choice, type number again");
        }         
    }while(1); 
    printf("\n\n---------------------Game finished--------------------- \n\n");
    free(catalog); 
    free(gameplay);
    return 0;
}

