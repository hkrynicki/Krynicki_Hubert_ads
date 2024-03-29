#include <stdio.h>
#include <stdbool.h>

struct stack{
    const int maxSize;    
    int top;
    int stack[9];
};
struct stack undoStack = {8, -1};
struct stack redoStack = {8, -1};

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
    if(undoStack.top > -1){
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
/**
 * Reset counter on both stacks, used when user play one game after another
*/
void cleanBothStacks(){
    undoStack.top = -1;
    redoStack.top = -1;    
}