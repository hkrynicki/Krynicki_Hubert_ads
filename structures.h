struct player{
    char name[20];
    char mark;       
};
struct gamefield{    
    char mark;
};
struct gameboard{
    int size;        
    struct gamefield fields[9];        
};