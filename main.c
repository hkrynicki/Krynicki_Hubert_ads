#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "stack.h"
#include "utils.h"
#include "structures.h"
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
    printf("  %c   %c  |  %c  |  %c  \n",rows[0], gb.fields[0].mark, gb.fields[1].mark, gb.fields[2].mark);
    printf("    _____|_____|_____\n");
    printf("         |     |     \n");
    printf("  %c   %c  |  %c  |  %c  \n",rows[1], gb.fields[3].mark, gb.fields[4].mark, gb.fields[5].mark);
    printf("    _____|_____|_____\n");
    printf("         |     |     \n");
    printf("  %c   %c  |  %c  |  %c  \n",rows[2], gb.fields[6].mark, gb.fields[7].mark, gb.fields[8].mark);
    printf("         |     |     \n\n");
    
}
void printStartMenu(){
    printf(" Welcome to final and superior TicTacToe game, choose : \n");
    printf(" 1 - to start new game\n");
    printf(" 2 - to replay one of old matches\n");
    printf(" You choose : ");
}
void printGameMenu(){
    printf("\n %s turn\n Choose field by writing 'A1', '2C' etc\n", currentPlayer.name);
    printf(" or type 'undo' to revert one move \n");
    printf(" or type 'redo' to cancel revert \n");
    printf(" or type 'exit' to finish :   ");
}

/**
 * Ask players for names and assign marks
 * 
 * @param struct player : p1, p2  
*/
void determinePlayers(){

    //Player1
    printf(" Welcome, Player 1 please insert your name:   ");    
    fgets(p1.name, 20, stdin);
    flushAfterString(p1.name);    
    if(isStringEmpty(p1.name)){
        strcpy(p1.name, "Player1");
        printf(" Inserted name is not valid, you have been assigned name 'Player 1'\n");    
    }  

    printf(" Would you like noughts('O') or crosses('X')? \n Enter 'O' or 'X':    ");      
    p1.mark = getchar();
    flushAfterChar(p1.mark);
    
    if(p1.mark == 'o' || p1.mark == 'O' || p1.mark == '0'){
        p1.mark = 'O';
    }
    else if(p1.mark == 'x' || p1.mark == 'X'){
        p1.mark = 'X';
    }    
    else{
        p1.mark = 'X';
        printf("\n Inserted character is invalid, you have been assigned crosses 'X'\n");
    }    

    //Player2
    printf("\n Player 2 please insert your name:   ");    
    fgets(p2.name, 20, stdin);
    flushAfterString(p2.name);     
    if(isStringEmpty(p2.name)){
        strcpy(p2.name, "Player2");
        printf("Inserted name is not valid, you have been assigned name 'Player 2'\n"); 
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
 * Validate field to be marked
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
    gb.fields[fieldNum].mark = currentPlayer.mark;   

    addToHistoryFile("MOVE", fieldNum, currentPlayer.mark, currentPlayer.name);
    pushToStack(fieldNum);              
}
/**
 * Revert newest turn
 * 
 * @return true if revert was succesfull
*/
bool undoTurn(){
    if(turn > 1){
        addToHistoryFile("UNDO");
        int fieldNum = popFromUndoStack();
        gb.fields[fieldNum].mark = ' ';
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
        addToHistoryFile("REDO");
        gb.fields[fieldNum].mark = currentPlayer.mark;
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
    char c = gb.fields[fieldNum].mark;
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
            if(gb.fields[i].mark == c && gb.fields[i+1].mark ==  c && gb.fields[i+2].mark == c){
                return true;
            }
        }
        //Check columns
        for(int i = 0; i < 3; i++){
            if(gb.fields[i].mark ==  c && gb.fields[i+3].mark == c && gb.fields[i+6].mark == c){
                return true;
            }
        }
        //Check diagonal
        for(int i = 0; i < 3; i = i + 3){
            if(gb.fields[i].mark == c && gb.fields[i+4].mark == c && gb.fields[i+8].mark == c){
                return true;
            }
        }
        for(int i = 6; i > 3; i = i - 3){
            if(gb.fields[i].mark ==  c && gb.fields[i-2].mark  == c && gb.fields[i-4].mark == c){
                return true;
            }
        }
    }    
    return false;
}
int main()
{
    printf("\n\n---------------------Game started--------------------- \n\n");    
       
    determinePlayers();
    bool exit = false;  
    addToHistoryFile("START_HEADER");
    addToHistoryFile("HEADER",p1.name, p1.mark);
    addToHistoryFile("HEADER",p2.name, p2.mark);     
    addToHistoryFile("START_GAME");          
    do{          
        char field[5];
        calcCurrentPlayer(turn);       
        printPlayers(p1, p2);
        printGameboard(gb);
        //If move will be invalid app will ask for new input
        bool moveIsValid;
        
        printGameMenu();
        do{                    
            fgets(field, 5, stdin);
            flushAfterString(field);

            int fieldNum = validateMarkInput(field);
            if(fieldNum != -1){                
                if(fieldNotMarked(fieldNum)){
                    moveIsValid = true;
                    applyMarkToGameBoard(fieldNum);                    
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
            else if(strcmp(field, "exit") == 0 || strcmp(field, "EXIT") == 0){
                moveIsValid = true;
                exit = true;                
            }
            else if(strcmp(field, "undo") == 0 || strcmp(field, "UNDO") == 0){
                moveIsValid = undoTurn();                
            }
            else if(strcmp(field, "redo") == 0 || strcmp(field, "REDO") == 0){
                moveIsValid = redoTurn();
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
    addToHistoryFile("END_GAME");
    



    printf("\n\n---------------------Game finished--------------------- \n\n");
    return 0;
}

