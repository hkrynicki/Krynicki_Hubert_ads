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

struct single_move_details{
    char action[5];
    int field;   
};

struct single_game_info{
    int id;
    int lineNumber;
    char mark1;
    char name1[25];
    char mark2;
    char name2[25];
};