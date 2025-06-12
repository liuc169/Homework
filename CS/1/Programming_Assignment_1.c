# include <stdio.h>

int x = 0; //x coordinate of input
int y = 0; //y coordinate of input
int r = 0; //row of board
int c = 0; //column of board
int turns = 0;

//game board 
char board [5][11] = {
        {' ',' ',' ','|',' ',' ',' ','|',' ',' ',' '},
        {'-','-','-','|','-','-','-','|','-','-','-'},
        {' ',' ',' ','|',' ',' ',' ','|',' ',' ',' '},
        {'-','-','-','|','-','-','-','|','-','-','-'},
        {' ',' ',' ','|',' ',' ',' ','|',' ',' ',' '},
};

//print out the whole board information
void draw_board(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 11; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    };
}

//input is a 3*3 matrix on the user side, but data are stored in a 5*11 matrix. We need map two matrix.
//function is used for mapping input coordinate with board position
int mapping(int x, int y){
    if (x == 1){
        r = 0;
        if (y == 0) c = 1;
        else if (y == 1) c = 5;
        else if (y == 2) c = 9;
    }

    else if (x == 2){
        r = 2;
        if (y == 0) c = 1;
        else if (y == 1) c = 5;
        else if (y == 2) c = 9;
    }

    else if (x == 3){
        r = 4;
        if (y == 0) c = 1;
        else if (y == 1) c = 5;
        else if (y == 2) c = 9;
    }

    return 0;
}


//check whether the input is conflicted
int check(int r, int c){
    return board[r][c] == 'X' || 'O'; //if input position is occupied, return 1
}


void computer_move(){
    for (x = 0; x < 3; x++){
        for (y = 0; y < 3; y++){
            mapping(x, y);
            if (check(r, c)) continue;
            else board[r][c] = 'O'; //if the position is not occupied, fill with computer's move
        }
    }
}


//check who wins and return judgement. checking by row by row, column by column, and by diagonal
int winning_check(){
    //check rows one by one
    for (x = 0; x < 3; x++){
        int human_account = 0;
        int computer_account = 0;

        for (y = 0; y < 3; y++){
            mapping(x, y);
            if (check(r, c)){
                if (board[r][c] == 'X'){
                    human_account++;
                }
                else computer_account++;
            }
            else continue;
        }

        if (human_account == 3) return 0;
        else if (computer_account == 3) return 1;
    }

    //check columns one by one
    for (y = 0; y < 3; y++){
        int human_account = 0;
        int computer_account = 0;

        for (x = 0; x < 3; x++){
            mapping(x, y);
            if (check(r, c)){
                if (board[r][c] == 'X'){
                    human_account++;
                }
                else computer_account++;
            }
            else continue;
        }

        if (human_account == 3) return 0;
        else if (computer_account == 3) return 1;
    }
    
    //check by diagonal from left to right
    for (x = 0; x < 3; x++){
        y = 0;
        int human_account = 0;
        int computer_account = 0;

        mapping(x, y);
        y++;
        if (check(r, c)){
            if (board[r][c] == 'X'){
                human_account++;
            }
            else computer_account++;
        }
        else continue;

        if (human_account == 3) return 0;
        else if (computer_account == 3) return 1;
    }     

    //check by diagonal from right to left
    for (x = 0; x < 3; x++){
        y = 2;
        int human_account = 0;
        int computer_account = 0;

        mapping(x, y);
        y--;
        if (check(r, c)){
            if (board[r][c] == 'X'){
                human_account++;
            }
            else computer_account++;
        }
        else continue;

        if (human_account == 3) return 0;
        else if (computer_account == 3) return 1;
    }   
}


int main(){
    char name[100];

    //title and welcome print
    printf("\n\n********************\nTic Tac Toe\nCreator: Chengyao Liu\nStudent number: T00782767\nTry to play against the computer :)\n********************\n\n");
    printf("What is your name?\n\n");
    scanf("%s", name);
    printf("\n\nHello %s ... Let's have fun !!!\nYou = X | Computer = O\n\n", name);

    while(1){

        printf("Enter X,Y coordinates for your move: ");
        scanf("%d,%d", &x, &y);

        mapping(x, y);
        //check user move is in range
        if (check(r, c) || x > 2 || y > 2 || x < 0 || y < 0){
            printf("Your move is invalid!\n");
            continue;
        }

        else board[r][c] = 'X'; //if the position is not occupied and input is valid, fill with user's move

        computer_move();

            //winning checking part
            turns++;
            if (turns > 2){
                if (!winning_check()){
                    printf("********\nYou won!\n********\n\n");
                    draw_board();
                    break;
                }

                if (winning_check()){
                    printf("********\nYou lost!\n********\n\n");
                    draw_board();
                    break;
                }
            }

            draw_board();

    }

    return 0;
}