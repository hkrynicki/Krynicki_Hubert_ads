#include <stdio.h>
#include <stdbool.h>

//Usability methods
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