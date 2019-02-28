#include <stdio.h>
#include <stdbool.h>


const int maxSize = 8;
int stack[9];
int top = -1;

bool isEmpty(){
    if(top == -1){
        return true;
    }
    return false;
}
bool isFull(){
    if(top == maxSize){
        return true;
    }
    return false;
}
void pushToStack(int fieldNumber){    
    if(!isFull()){
        top++;
        stack[top] = fieldNumber;         
    }
    else{
        printf("Can't insert element, stack is full\n");
    }
    
}
int popFromStack(){
    if(!isEmpty()){
        top--;
        return stack[top+1];
    }
    printf("No moves to undo");
    return -1;
}
