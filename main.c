#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


const int gameSize = 3;
const char cols[3] = {'A','B','C'};
const char rows[3] = {'1','2','3'};


const char marks[2] = {'X','O'}; 
const char *defaultPlayer1 = "Player1";
const char *defaultPlayer2 = "Player2";


struct player{
    char name[20];
    char mark;
    bool isComputer;    
};

struct gamefield{
    char id[2];
    char mark;
};
struct gameboard{
    int size;    
    char rows[3];
    char col[3];
    struct gamefield fields[9];        
};

void printGameboard(struct gameboard gb,struct player p1, struct player p2){
    printf("\n%s  -  '%c'",p1.name, p1.mark);
    printf("\n%s  -  '%c'",p2.name, p2.mark);    
    printf("\n\nGame size = %u x %u\n\n", gb.size, gb.size);

    printf("      %c     %c     %c\n", gb.col[0], gb.col[1], gb.col[2]);
    printf("         |     |     \n");
    printf("  %c   %c  |  %c  |   %c  \n",gb.rows[0], gb.fields[0].mark, gb.fields[1].mark, gb.fields[2].mark);
    printf("    _____|_____|_____\n");
    printf("         |     |     \n");
    printf("  %c   %c  | %c   |   %c  \n",gb.rows[1], gb.fields[3].mark, gb.fields[4].mark, gb.fields[5].mark);
    printf("    _____|_____|_____\n");
    printf("         |     |     \n");
    printf("  %c   %c  | %c   |   %c  \n",gb.rows[2], gb.fields[6].mark, gb.fields[7].mark, gb.fields[8].mark);
    printf("         |     |     \n\n");
    
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

void flushAfterString(char *string){
    char *temp;
    if(temp=strchr(string, '\n')){//check exist newline
        *temp = 0;
    }
    else{
        scanf("%*[^\n]");scanf("%*c");//clear upto newline
    }
}
void flushAfterChar(char ch){    
     if(ch != '\n'){//check exist newline                
            scanf("%*[^\n]");scanf("%*c");//clear upto newline
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
    flushAfterString((*p1).name);
    removeNewLineFromString((*p1).name);
    if(isEmpty((*p1).name)){
        strcpy((*p1).name, defaultPlayer1);
        printf("Inserted name is not valid, you have been assigned name 'Player 1'\n");    
    }  
    

    printf("Would you like noughts('O') or crosses('X')? \nEnter 'O' or 'X':    ");      
    (*p1).mark = getchar();
    flushAfterChar((*p1).mark);
    (*p1).mark = isValidMark((*p1).mark);    
    if((*p1).mark == 127){
        (*p1).mark = marks[0];
        printf("\nInserted character is invalid, you have been assigned crosses 'X'\n");
    }    

    //Player2
    printf("\nPlayer 2 please insert your name:   ");    
    fgets((*p2).name, 20, stdin);
    flushAfterString((*p2).name);
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
    struct gameboard gb = {gameSize, {rows[0],rows[1],rows[2]}, {cols[0],cols[1],cols[2]}};
       
    determinePlayers(&p1, &p2);
    bool exit;
    int turn = 1;
    do{
        exit = false;
        char field[5];
        struct player currentPlayer;
        printGameboard(gb, p1, p2);
        if(turn == 1 || turn == 3 || turn == 5 || turn == 7 || turn == 9){
            currentPlayer = p1;
        }
        else{
            currentPlayer = p2;
        }
        printf("\n %s choose field by writing 'A1', '2C' etc or type 'exit' to finish :   ", currentPlayer.name);        
        fgets(field, 5, stdin);
        flushAfterString(field);
        removeNewLineFromString(field);
        if(strcmp(field, "exit") == 0){
            exit = true;
        }
        turn += 1;
    }while(exit != true);
    
    

    
    



    printf("\n\n---------------------Game finished--------------------- \n\n");
    return 0;
}

