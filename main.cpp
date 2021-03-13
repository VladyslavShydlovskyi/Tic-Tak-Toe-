#include <iostream>
#include <string>
using namespace std;

//initialization of constants
const char X = 'X';
const char O = 'O';
const char STAR = '*';
const char DRAW = 'D';
const char NO_ONE = 'N';
char human;
char computer;
int bestMovesComp[2];
int movesHuman[2];

//function prototypes
void instructions(const char(&board)[3][3]);
char yesNo(string question);
int askNumber(string question, int high, int low=0);
char humanPiece();
char opponent(char piece);
void displayBoard(const char(&board)[3][3]);
char winner(char board[3][3]);
bool isLegal(const char(&board)[3][3], int row, int column);
void humanMove(const char(&board)[3][3]);
void announceWinner(char board [3][3]);
void fillArr(char(&board)[3][3], char star);
int evaluate(char board[3][3]);
bool isMovesLeft(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMax);
void computerMove(char board[3][3]);


int main() {

    char board[3][3];
    fillArr(board, STAR);
    instructions(board);
    human = humanPiece();
    computer = opponent(human);


    char turn = X; //according to rules, X moves first



    while(winner(board) == NO_ONE){

        if(turn == human){
            humanMove(board);
            board[movesHuman[0]][movesHuman[1]] = human;
            cout << "your Turn!"<<endl;
            displayBoard(board);
        }else{
            computerMove(board);
            board[bestMovesComp[0]][bestMovesComp[1]] = computer;
            cout << "SHOW ME WHAT YOU CAN!"<< endl;
            displayBoard(board);
        }

        turn = opponent(turn);
    }
    announceWinner(board);

    return 0;
}

void instructions(const char(&board)[3][3]){
    cout << "Hello, board looks like this:" << endl;
    displayBoard(board);
    cout << "You will be asked to enter two numbers: row and column" << endl;
}

void displayBoard(const char(&board)[3][3]){

    for(int i = 0; i < 3; i++){
        cout << "\t"<< "-------------"  << endl;
        for(int j = 0; j < 3; j++) {
            if(j == 0){
                cout << "\t"<< "| " << board[i][j] << " |";
            }else if(j == 1){
                cout << " " << board[i][j];
            }else{
                cout <<" | "<< board[i][j] << " |";
            }

        }
        cout << endl;
    }
    cout << "\t"<< "-------------" << endl;
}

char yesNo(string question){

    char response;
    do{
        cout << question;
        cin >> response;

    }while(response != 'y' && response != 'n');

    return response;
}

int askNumber(string question, int high, int low){

    int number;
    do{
        cout << question << " (" << low << " - " << high << "): "<<endl;
        cin >> number;
    }while(number > high || number < low);
    return number;
}

char humanPiece(){

    char go_first = yesNo("Do you want to move first?");
    if(go_first == 'y'){
        cout << "OKKKK" << endl;
        return X;
    }else{
        cout << "My turn!!!!!" << endl;
    }
    return O;
}

char opponent(char piece){

    if(piece == X){
        return O;
    }
    return X;
}

void fillArr(char (&board)[3][3], char star){

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = star;
        }
    }
}

bool isLegal(const char(&board)[3][3], int row, int column){
    return board[row][column] != '*';
}

int evaluate(char board[3][3]){
    // Checking for Rows.
    for (int row = 0; row<3; row++){
        if (board[row][0]==board[row][1] &&
            board[row][1]==board[row][2])
        {
            if (board[row][0] == computer)
                return +10;
            else if (board[row][0] == human)
                return -10;
        }
    }

    // Checking for Columns.
    for (int col = 0; col<3; col++){
        if (board[0][col]==board[1][col] &&
            board[1][col]==board[2][col])
        {
            if (board[0][col] == computer)
                return +10;

            else if (board[0][col] == human)
                return -10;
        }
    }

    // Checking for Diagonals.
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2]){
        if (board[0][0] == computer)
            return +10;
        else if (board[0][0] == human)
            return -10;
    }

    if (board[0][2]==board[1][1] && board[1][1]==board[2][0]){
        if (board[0][2] == computer)
            return +10;
        else if (board[0][2] == human)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

bool isMovesLeft(char board[3][3]){

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == STAR){
                return true;
            }
        }
    }
    return false;
}

int minimax(char board[3][3], int depth, bool isMax){
    int score = evaluate(board);

    if (score == 10)
        return score - depth;

    if (score == -10)
        return score + depth;

    if (!isMovesLeft(board))
        return 0;

    if (isMax){
        int best = -1000;
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                if (board[i][j] == STAR)
                {
                    board[i][j] = computer;
                    best = max(best, minimax(board, depth+1, !isMax) );
                    board[i][j] = STAR;
                }
            }
        }
        return best;
    }else{
        int best = 1000;
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                if (board[i][j] == STAR)
                {
                    board[i][j] = human;
                    best = min(best, minimax(board, depth+1, !isMax));
                    board[i][j] = STAR;
                }
            }
        }
        return best;
    }
}

void computerMove(char board[3][3]) {
    int bestVal = -1000;
    bestMovesComp[0] = -1;
    bestMovesComp[1] = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == STAR) {
                board[i][j] = computer;
                int moveVal = minimax(board, 0, false);
                board[i][j] = STAR;
                if (moveVal > bestVal) {
                    bestMovesComp[0] = i;
                    bestMovesComp[1] = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

void humanMove(const char(&board)[3][3]){

    int row = askNumber("Enter row number:", 2);
    int column = askNumber("Enter column number: ", 2);

    while(isLegal(board, row, column)){
        cout << "can not go here"<<endl;
        row = askNumber("Enter row number:", 2);
        column = askNumber("Enter column number: ", 2);

    }

    movesHuman[0] = row;
    movesHuman[1] = column;

}

char winner(char board[3][3]){
    int num = evaluate(board);
    if(num == 10){
        return computer;
    }else if(num == -10){
        return human;
    }else{
        return NO_ONE;
    }
}

void announceWinner(char board[3][3]){
    if(winner(board) == computer){
        cout<<"I have won!!!!!!!!!";
    }else if(winner(board) == human){
        cout<<"CONGRATS!";
    }else{
        cout<< "DRAW";
    }
}