#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const int gameSize = 3;
const char rows[3] = {'A','B','C'};
const char cols[3] = {'1','2','3'};


const char marks[2] = {'X','O'}; 
const char *defaultPlayer1 = "Player1";
const char *defaultPlayer2 = "Player2";


struct player{
    char name[20];
    char mark;
    bool isComputer;
};

struct gameboard{
    int size;    
    char rows[3];
    char col[3];
};
void printGameboard(struct gameboard gb,struct player p1, struct player p2){
    printf("\n%s  -  '%c'",p1.name, p1.mark);
    printf("\n%s  -  '%c'",p2.name, p2.mark);    
    printf("\n\nGame size = %u x %u\n\n", gb.size, gb.size);

    
}
//Usability methods
/**
 * Check if string is empty - 
 *      containes nothing except spaces and control characters
 * 
 * @param string to be checked
 * @return boolean 
*/
bool isEmpty(char s[]){    
    //Useful if string contain white-spaces
    bool containsAnyLetter = false;
    for(int i = 0; i < strlen(s) - 1 ; i++){
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
 * Check if char is valid mark
 * 
 * @param char to be checked
 * @return char 'O', or 'X', or DEL character to signal invalid char
*/
char isValidMark(char c){
    if(c == 'o' || c == 'O' || c == '0'){
        return marks[1];
    }
    else if(c == 'x' || c == 'X'){
        return marks[0];
    }
    return 127;
};
/**
 * Clear input stream
*/
void flushStdin(){
    char temp;    
    while((temp = getchar()) != '\n' && temp != EOF){
    }
}
/**
 * Ask players for names and assign marks
 * 
 * @param struct player : p1, p2  
*/
void determinePlayers(struct player *p1, struct player *p2){

    //Player1
    printf("Welcome, Player 1 please insert your name:   ");    
    fgets((*p1).name, 20, stdin);
    removeNewLineFromString((*p1).name);
    if(isEmpty((*p1).name)){
        strcpy((*p1).name, defaultPlayer1);
        printf("Inserted name is not valid, you have been assigned name 'Player 1'\n");    
    }  
    

    printf("Would you like noughts('O') or crosses('X')? \nEnter 'O' or 'X':    ");      
    (*p1).mark = getchar();
    (*p1).mark = isValidMark((*p1).mark);    
    if((*p1).mark == 127){
        (*p1).mark = marks[0];
        printf("\nInserted character is invalid, you have been assigned crosses 'X'\n");
    }    

    //Player2
    printf("\nPlayer 2 please insert your name:   ");
    flushStdin();
    fgets((*p2).name, 20, stdin);
    removeNewLineFromString((*p2).name);    
    if(isEmpty((*p2).name)){
        strcpy((*p2).name, defaultPlayer2);
        printf("Inserted name is not valid, you have been assigned name 'Player 2'\n"); 
    }
    //If Player1 chose crosses than Player2 will be assigned noughts
    if((*p1).mark == marks[0]){
        (*p2).mark = marks[1];
    }
    else{
        (*p2).mark = marks[0];
    }
    printf("You have been assigned %c\n",(*p2).mark);
}
int main()
{
    printf("\n\n---------------------Game started--------------------- \n\n");
    struct player p1 = {*defaultPlayer1, marks[0], false};
    struct player p2 = {*defaultPlayer2, marks[1], false};
    struct gameboard gb = {gameSize, };    
    

    determinePlayers(&p1, &p2);
    printGameboard(gb, p1, p2);
    

    
    



    printf("\n\n---------------------Game finished--------------------- \n\n");
    return 0;
}

