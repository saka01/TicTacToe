#include <stdio.h>
#include <ctype.h>

// initalizes a Tic-Tac-Toe board from 1 to 9
// m  and n are the size of the baord (row, columns)
// board is an array that holds all the information
void InitalizeBoard(int m, int n, char board[][n]){
    int c = 1; // c = counter
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            board[i][j] = c + '0';
            c++;
        }
    }
}

// prints out the data in our Tic-Tac-Toe board
// m  and n are the size of the baord (row, columns)
// board is an array that holds all the information
void PrintBoard(int m, int n, char board[][n]){
    for(int i = 0; i < m; i++){
        printf("   |   |\n");
        for(int j = 0; j < n; j++){
            if(j+1 == n){
                printf(" %c \n", board[i][j]);
            }
            else{
                printf(" %c |", board[i][j]);
            }
        }
        if(i+1 == m){
            printf("   |   |\n");
        }
        else{
            printf("___|___|___\n");
        }
    }
}

// allows the user to set each cell of the board to what ever they choose
// m  and n are the size of the baord (row, columns)
// board is an array that holds all the information
void CreateBoard(int m, int n, char board[][n]){
    int opt;
    char input;
    int row, col;

    do {
        printf("Enter the number of the cell where you want to insert X or O or enter -1 to exit\n");
        scanf("%d", &opt);


        // checking if the option chosen is in our range of numbers or if it's the terminator
        if((opt > n * m) || opt < 1){
            break;
        }

        else{
            row = opt / m, col = opt % n;

            if(col == 0){
                col += 3;
                row -= 1;
            }

            printf("Type X or O\n");
            scanf(" %c", &input);
            board[row][col - 1] = toupper(input);
        }
        PrintBoard(m, n, board);

    } while(opt != -1);
}

// determines if the board is valid or not (that is there are the correct amount of X's and O's)
// m  and n are the size of the baord (row, columns)
// board is an array that holds all the information
int IsvalidBoard(int m, int n, char board[][m]){
    int counter = 0; // keeping track of the difference of x's to o's

    // finding the difference
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] == 'X'){
                ++counter;
            }
            else if (board[i][j] == 'O'){
                --counter;
            }
        }
    }

    // if it is a valid table
    if(counter == 0 || counter == 1 || counter == -1){
        return 1; // a valid table
    }

    else {
        // if it is an invalid table
        return 0; // an invalid table
    }
}

// finds the winnng cells for player X and O
// m  and n are the size of the baord (row, columns)
// board is an array that holds all the information
void LastWinningCells(int m, int n, char board[][m]){
    int occurence; // how many times a player's X or O orrures in a row, column, or diagonlly
    int Found1Solution; // if we find  a place where x or O can go, we increment this
    int FoundX, FoundO;
    char idk[2] = {'X','O'}; // player listing


    // checking if the board is valid
    if(!IsvalidBoard(m, n, board)){
        printf("Invalid board, cannot determing winning cells\n");
        return;
    }

    // determing the winning cells
    for(int option = 0; option < 2; ++option){
        Found1Solution = 0;
        // checking horizontal cases
        for(int i = 0; i < m; i++){
            occurence = 0;
            for(int j = 0; j < m; j++){
                if(board[i][j] == idk[option]){
                    ++occurence; // detemining how many times an X or an O occured horizontally to deduce if there is a potential winning case
                }
            }
            // if the cell requies 1 more X or O to win
            if(occurence == 2){
                for(int j = 0; j < m; j++){
                    if(board[i][j] != idk[option] && (board[i][j] != idk[(option + 1) % 2])){
                        if(!Found1Solution){
                            printf("Cell #%d ",  i*m + j + 1);
                        }
                        else if (Found1Solution >= 1) {
                            printf("and #%d ", i*m + j + 1);
                        }
                        ++Found1Solution;
                    }
                }
            }
        }

        // checking vertical cases cases
        for(int i = 0; i < m; i++){
            occurence = 0;
            for(int j = 0; j < m; j++){
                if(board[j][i] == idk[option]){
                    ++occurence;
                }
            }
            if(occurence == 2){
                for(int j = 0; j < m; j++){
                    if(board[j][i] != idk[option] && (board[j][i] != idk[(option + 1) % 2])){
                        if(!Found1Solution){
                            printf("Cell #%d ",  j*m + i + 1);
                        }
                        else if (Found1Solution >= 1) {
                            printf("and #%d ", j*m + i + 1);
                        }
                        ++Found1Solution;
                    }
                }
            }
        }

        // checking TopLeft-BottomRight diagonal
        occurence = 0;
        for(int i = 0; i < m; i++){
            if(board[i][i] == idk[option]){
                ++occurence; // detemining how many times an X or an O occured horizontally to deduce if there is a potential winning case
            }
        }

        // if the cell requies 1 more X or O to win
        if(occurence == 2){
            for(int i = 0; i < m; i++){
                if(board[i][i] != idk[option] && (board[i][i] != idk[(option + 1) % 2])){
                    if(!Found1Solution){
                        printf("Cell #%d ",  (i * m) + i + 1);
                    }
                    else if (Found1Solution >= 1) {
                        printf("and #%d ", (i * m) + i + 1);
                    }
                    ++Found1Solution;
                }
            }
        }

        // checking TopRight-BottomLeft diagonal
        occurence = 0;
        for(int i = 0; i < m; i++){
            if(board[i][m - i - 1] == idk[option]){
                ++occurence; // detemining how many times an X or an O occured horizontally to deduce if there is a potential winning case
            }
        }

        // if the cell requies 1 more X or O to win
        if(occurence == 2){
            for(int i = 0; i < m; i++){
                if(board[i][m - i - 1] != idk[option] && (board[i][m - i - 1] != idk[(option + 1) % 2])){
                    if(!Found1Solution){
                        printf("Cell #%d ", (2 * i) + 3);  // (2 * i) + 3 is the formula to relate index of our 3x3 array to a linear array index + 1
                    }
                    else if (Found1Solution >= 1) {
                        printf("and #%d ", (2 * i) + 3);
                    }
                    ++Found1Solution;
                }
            }
        }
        if(Found1Solution >= 1){
            printf("are winning cells for player %c\n", idk[option]);
        }

        // Used to determine if there are no winning cells for X or O
        if(option == 0){
            FoundX = Found1Solution;
        }
        else{
            FoundO = Found1Solution;
        }
    }
    if(!FoundX && !FoundO){
        printf("No winning solutions for player X or O\n");
    }

}

// prints out the menu
void menu(void){
    puts("press 'p' to print the tic-tac-toe board");
    puts("press 'c' to create a tic-tac-toe board with some X and O cells");
    puts("press 't' to test if a tic-tac-toe board is valid or invalid board");
    puts("press 'w' to predict winning cell for player X or O");
    puts("press 'e' to Exit");
}

int main(){
    //size of the board
    int m = 3, n = m;
    int playing = 1; // controls the while loop, 1 or true means the game is in progress
    char choice; // choice chosen from menu
    char board[m][n]; // Tic-Tac-Toe board

    //initalizing the board
    InitalizeBoard(m, n, board);

    menu();
    scanf(" %c", &choice);
    while(playing){
        switch(choice){
            case 'p':
            case 'P':
                // prints the tic-tac-toe board to the screen
                PrintBoard(m, n, board);
                break;

            case 'c':
            case 'C':
                // creating the board then printing out the created board
                CreateBoard(m, n, board);
                break;

            case 't':
            case 'T':
                //testing to see if the board is invalid
                if(IsvalidBoard(m, n, board)){
                    puts("This is a valid board.");
                }
                else{
                    puts("This is an invalid board.");
                }
                break;

            case 'w':
            case 'W':
                LastWinningCells(m, n, board);
                break;

            case 'e':
            case 'E':
                playing = 0;
                break;

            default:
                puts("Unknon input");
                break;
        }
        if(playing){
            menu();
            scanf(" %c", &choice);
        }
    }
    return 0;
}
