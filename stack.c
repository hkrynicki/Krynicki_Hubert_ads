#include <stdio.h>
#include <stdbool.h>

struct stack{
    const int maxSize;    
    int top;
    int stack[9];
};
struct stack undoStack = {8, -1};
struct stack redoStack = {8, -1};

bool isEmpty(){
    if(undoStack.top == -1){
        return true;
    }
    return false;
}
bool isFull(){
    if(undoStack.top == undoStack.maxSize){
        return true;
    }
    return false;
}
void pushToStack(int fieldNumber){
    redoStack.top = -1;    
    if(!isFull()){
        undoStack.top++;
        undoStack.stack[undoStack.top] = fieldNumber;            
    }
    else{
        printf("Can't insert element, stack is full\n");
    }    
}
int popFromUndoStack(){
    if(!isEmpty()){
        int fieldNumber = undoStack.stack[undoStack.top];

        redoStack.top++;
        redoStack.stack[redoStack.top] = fieldNumber;     

        undoStack.top--;
        return fieldNumber;
    }    
    return -1;
}
int popFromRedoStack(){
    if(redoStack.top > -1){
        int fieldNumber = redoStack.stack[redoStack.top];
        redoStack.top--;

        undoStack.top++;
        undoStack.stack[undoStack.top] = fieldNumber;

        return fieldNumber;
    }    
    return -1;
}

