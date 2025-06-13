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
        if (y == 1) c = 1;
        else if (y == 2) c = 5;
        else if (y == 3) c = 9;
    }

    else if (x == 2){
        r = 2;
        if (y == 1) c = 1;
        else if (y == 2) c = 5;
        else if (y == 3) c = 9;
    }

    else if (x == 3){
        r = 4;
        if (y == 1) c = 1;
        else if (y == 2) c = 5;
        else if (y == 3) c = 9;
    }

    return 0;
}


//check whether the input is conflicted
int check(int r, int c){
    return (board[r][c] == 'X' || board[r][c] == 'O'); //if input position is occupied, return 1
}


void computer_move(){
    int lebal = 1;
    for (x = 1; x < 4 && lebal; x++){
        for (y = 1; y < 4; y++){
            mapping(x, y);
            if (check(r, c)) continue;
            else {
                board[r][c] = 'O';
                lebal = 0;
                break;
            } //if the position is not occupied, fill with computer's move
        }
    }
}


//check who wins and return judgement. checking by row by row, column by column, and by diagonal
int winning_check(){
    //check rows one by one
    for (int i = 1; i < 4; i++){
        int human_account = 0;
        int computer_account = 0;

        for (int j = 1; j < 4; j++){
            mapping(i, j);
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
    for (int j = 1; j < 4; j++){
        int human_account = 0;
        int computer_account = 0;

        for (int i = 1; i < 4; i++){
            mapping(i, j);
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
    for (int i = 1; i < 4; i++){
        int human_account = 0;
        int computer_account = 0;

        mapping(i, i);
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
    for (int i = 1; i < 4; i++){
        int j = 3;
        int human_account = 0;
        int computer_account = 0;

        mapping(i, j);
        j--;
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

    //no one wins
    return -1;
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

        //mapping result printing for debug
        //printf("r = %d\nc = %d\n\n", r, c);


        //check user move is in range
        if (x > 3 || y > 3 || x < 1 || y < 1){
            printf("Your move is out of range!\n");
            continue;
        }

        //check user move is in empty space
        else if (check(r, c)){
            printf("Your move is conflicted!\n");
            continue;
        }

        else board[r][c] = 'X'; //if the position is not occupied and input is valid, fill with user's move


        //winning checking part
        turns++;

        if (turns > 2){
            int result = winning_check();
            if (result == 0){
                printf("********\nYou won!\n********\n\n");
                draw_board();
                break;
            }

            else if (result == 1){
                printf("********\nYou lost!\n********\n\n");
                draw_board();
                break;
            }
           
        }

        if (turns == 5) {
            int result = winning_check();
            if (result == -1) {
                printf("********\nNo one wins!\nGame over!\n********\n\n");
                draw_board();
                break;
            }
        }

        computer_move();

        if (turns > 2){
            int result = winning_check();
            if (result == 0){
                printf("********\nYou won!\n********\n\n");
                draw_board();
                break;
            }

            else if (result == 1){
                printf("********\nYou lost!\n********\n\n");
                draw_board();
                break;
            }
        }

        if (turns == 5) {
            int result = winning_check();
            if (result == -1) {
                printf("********\nNo one wins!\nGame over!\n********\n\n");
                draw_board();
                break;
            }
        }


        draw_board();

    }

    return 0;
}