#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const char marks[2] = {'X','O'}; 
const char *defaultPlayer1 = "Player1";
const char *defaultPlayer2 = "Player2";

struct player{
    char name[20];
    char mark;
    bool isComputer;
};

struct gameboard{
    unsigned int size;

};
void printGameboard(struct gameboard gb){
    printf("Game size = %u x %u", gb.size, gb.size);


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
    //Check if control character is first character(common input issue)
    if(iscntrl(s[0])){            
            return true;
    }
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
void flushStdin(){
    char temp;    
    while((temp = getchar()) != '\n' && temp != EOF){
    }
}
void determinePlayers(struct player *p1, struct player *p2){

    //Player1
    printf("Welcome, Player 1 please insert your name:   ");    
    fgets((*p1).name, 20, stdin);
    if(isEmpty((*p1).name)){
        strcpy((*p1).name, defaultPlayer1);
        printf("\nInserted name is not valid, you have been assigned name 'Player 1'\n");    
    }

    char temp[2];
    printf("\nWould you like noughts('O') or crosses('X')? \nEnter 'O' or 'X':    ");    
    fgets(temp, 2, stdin);    
    if(isValidMark(temp[0]) == 127){
        (*p1).mark = marks[0];
        printf("\nInserted character is invalid, you have been assigned crosses 'X'\n");
    }
    else{
        (*p1).mark = isValidMark(temp[0]);
    }

    //Player2
    printf("Player 2 please insert your name:   ");
    flushStdin();
    fgets((*p2).name, 20, stdin);    
    if(isEmpty((*p2).name)){
        strcpy((*p2).name, defaultPlayer2);
        printf("\nInserted name is not valid, you have been assigned name 'Player 2'\n"); 
    }
    //If Player1 chose crosses than Player2 will be assigned noughts
    if((*p1).mark == marks[0]){
        (*p2).mark = marks[1];
    }
    else{
        (*p2).mark = marks[0];
    }
    printf("\nYou have been assigned %c\n",(*p2).mark);
}
int main()
{
    printf("\n\n----------------Game started---------------- \n\n");
    struct player p1 = {*defaultPlayer1, marks[0], false};
    struct player p2 = {*defaultPlayer2, marks[1], false};
    
    determinePlayers(&p1, &p2);
    printf("\n%s\n",p1.name);

    struct gameboard gb;    
    gb.size =3;
    printGameboard(gb);



    printf("\n\n----------------Game finished---------------- \n\n");
    return 0;
}

