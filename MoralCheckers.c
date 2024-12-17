/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
Gwyneth Allyson Moral, DLSU ID# 12278254
******************************************************************/

/*
Description: The program ia a checker game that lets two players, light and dark, play against each other.
Programmed by: Gwyneth Allyson M. Moral, S16A
Last modified: 12/04/2022
Version: 1.0
[Acknowledgements: Ali, M. A. (2019, June 26). the-checkers-game. GitHub. https://github.com/pyxploiter/the-checkers/blob/master/Main.c
				   Julie, J. (2022, January 22). C program for checkers/draught game...|Code with Julie..
				   arrays - keeping score in a guessing game without limits in C. (n.d.). Stack Overflow. Retrieved December 4, 2022]
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* function to clear the terminal*/
void clear() {
    system("cls");
}

/*This function presents the menu and allows user to 
choose which part of the menu they want to see or do
Precondition: players select integers 1, 2, or 3.
*/
void displayMenu(){
	printf("%24s\n", "1-Play");
	printf("%27s\n", "2-View score");
	printf("%24s\n", "3-Quit");
}

/*This function is a randomizer on which player gets the
dark pieces that goes first.
@paramm cPlayer contains the A and B to determine which player 
gets which
@param p is the randomizer of the characters
@return a randomized character to assign a user
*/
char rand_player(){
	srand(time(NULL));
	char cPlayer[] = {'A','B'};
	char p = cPlayer[rand()%2];

	return p;
}
/*This function sets the symbol to be printed on the board
using a switch case.
Precondition: board only consists of 0-3 integers.
@param nNum is for the switch case to know which symbol to return
@returns the characters X, D, L, and space in the board*/ 
char displayPieces(int nNum) {
    switch(nNum)
    {
  		case 0:
            return 'X'; // print X on board for black box
   		case 1:
            return ' '; // print empty space on board
		case 2:
            return 'D'; // print D on board
        case 3:
            return 'L'; // print L on board
    }
    return 0; 
}
	
/*This function displays the checker board.
Precondition: none
@param board[][8] is the board
@param nRow is for the rows 
@param nCol is for the column
@returns the checker board with the pieces*/ 
void displayBoard(int board[][8])
{
    int nRow, nCol;
    
    printf("  +---+---+---+---+---+---+---+---+\n");
    
    for (nRow=0; nRow<8; ++nRow)
    {
        printf("%d |", nRow+1); //prints numbers at the side of the board
        for (nCol=0; nCol<8; nCol++)
        {
            printf(" %c |", displayPieces(board[nRow][nCol]) );
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf(" ");
    for(nCol = 0; nCol <8; nCol++) { //prints the numbers at the bottom of board
        printf("   %d", nCol + 1);
    }
    printf("\n");
}
 
/*This function evaluates the coordinate input and swaps the values of the coordinates 
so that the pieces will move
Precondition: user only inputs values from the 1 to 8 coordinates
@param board[8][8] is the board
@param i is the BEFORE row input
@param j is the BEFORE column input
@param k is the NEW row input
@param l is the NEW column input
@param temp sets the swapping of values
@returns the swapped coordinates*/ 
void swapValues(int board[8][8], int i, int j, int k, int l)
{
    int temp;

    temp = board[i][j];
    
    board[i][j] = board[k][l];
    
    board[k][l] = temp;
}

/*This function checks the player input
Precondition: player input is from 1-8 and chooses the 
correct coordinates their own piece and available spaces
@param board[][8] is the board
@param player checks which player is playing
@param i the value of the row BEFORE
@param j the value of the column BEFORE
@param k the value of the row the user wants
@parm l the value of the column the user wants
@param jmp_r will be the NEW value of row
@param jmp_c will be the NEW value of column
@returns 0 if value is valid, the NEW values of the pieces for the coordinates are returned
and returns -1 if the values are not applicable
*/ 
int playTurn(int board[][8], int player, int i, int j, int k, int l)
{
    int jmp_r;
    int jmp_c;
    
    if(player == 2){ // determines which player's turn it is
        printf("\nDARK move from coordinates %d,%d to %d,%d\n", i, j, k, l);
    } else {
        printf("\nLIGHT move from coordinates %d,%d to %d,%d\n", i, j, k, l);
    }
    
//checks which pieces are out of bounds
    if(i < 0 || 8 <= i){ 
        printf("i is out of bounds\n"); //prints if i is out of bounds
        return -1;
    }
    if(j < 0 || 8 <= j){
        printf("j is out of bound\n"); //prints if j is out of bounds
        return -1;
    }
        
    if(k < 0 || 8 <= k){
        printf("k is out of bounds\n"); //prints if k is out of bounds
        return -1;
        
    }
    if(l < 0 || 8 <= l){
        printf("l is out of bounds\n"); //prints if l is out of bounds
        return -1;
    }
//checks if piece is the current player's piece 
    if(player == 2){
        if(board[i][j] != 2){
            printf("Piece is not yours\n");
            return -1;
        }
    } else { 
        if(board[i][j] != 3){
            printf("Piece is not yours\n");
            return -1;
        }
    }
//checks if the location currently has a piece
    if(board[k][l] != 1){
        printf("\nlocation is taken!\n");
        return -1;
    }
//checks if player input is the correct direction
    if(player == 2){
        if(i >= k){
            printf("DARK player must move down\n");
            return -1;
        }
    } else { 
        if(i <= k){
            printf("LIGHT player must move up\n");   
            return -1;
        }
    }
//checks validity and swaps the coordinates based on user input
    if(i - k == -1 || i - k == 1){//for 1 move
        if(j - l == 1 || j - l == -1){
            swapValues(board,i,j,k,l);
            return 0;
        }
    }  
    if(i - k == -2 || i - k == 2){//for capturing opponent
        if(j - l == -2 || j - l == 2){
            if(i < k){ 
                jmp_r = i + 1;
            } else { 
                jmp_r = i - 1;
            }
            if(j < l){ 
                jmp_c = j + 1;
            } else { 
                jmp_c = j - 1;
            }
//checks if player is capturing the opponent's piece           
            if(player==2 && board[jmp_r][jmp_c]!=3)
            {
                printf("You can only jump over your opponent's piece!\n");
                return -1;
            }
            if(player==3 && board[jmp_r][jmp_c] != 2){
                printf("You can only jump over your opponent's piece!\n");
                return -1;
            }
 
            board[jmp_r][jmp_c] = 1; //for the eaten piece to become a space
            swapValues(board,i,j,k,l);
            return 0;
        }
    }

    return -1;
    
}

/*This function is to check if the player still has pieces remaining
Precondition: none
@param row is for the row of the board
@param col is for the column of the board
@param player determines which player's piece is being checked
@param pieceRemaining checks if there is still a piece or none
@returns 1 if true and 0 if false*/
int isPlayerOutOfPieces(int board[8][8], int player) {
    int row, col;
    int pieceRemaining = 0;
    for (row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            if(board[row][col] == player) {
                pieceRemaining = 1;
            }
        }
    }
    return pieceRemaining;
}
/*this function stores and prints the scores of the players
Precondition: none
@param scoreDark is the Dark player's score
@param scoreLight is the Light player's score
@param totalGames is the total games player's have played
@returns the scores of each player and how many games played*/
void printScores() {//look for a score and open in read mode to put in parameters
    // open score.txt file
    FILE *fin = fopen("score.txt", "r"); //r is read mode
    int scoreDark = 0, scoreLight = 0, totalGames = 0;
    fscanf(fin, "%d,%d,%d", &scoreDark, &scoreLight, &totalGames); //scans the integers
    printf("DARK: %d wins\n", scoreDark);
    printf("LIGHT: %d wins\n", scoreLight);
    printf("TOTAL GAMES: %d\n", totalGames);
    fclose(fin); //closes the file
}
/*This function saves the scores accumulated by each player
@param scoreDark is dark player's score
@param scoreLight is light player's score
@param totalGames is the total games played
@param winner determines who scored
@returns the saved scores of players */
void saveScores(int winner) {
    FILE *fin = fopen("score.txt", "r"); //opens the file
    int scoreDark = 0, scoreLight = 0, totalGames = 0; //starting scores
    fscanf(fin, "%d,%d,%d", &scoreDark, &scoreLight, &totalGames);
    fclose(fin); //closes the file

    if(winner == 2) {
        scoreDark++;
    } else {
        scoreLight++;
    }
    totalGames++;

    FILE *fout = fopen("score.txt", "w"); //w is write mode
    fprintf(fout, "%d,%d,%d", scoreDark, scoreLight, totalGames);
    fclose(fout); //closesthe file

}
/*This function delays the next statement to execute
Precondition: none
@param c is for the row
@param d if for the column
@retuns a cause of delay
*/
void delay(){
	int c, d;
	for (c = 1; c <= 100000; c++)
      	 for (d = 1; d <= 100000; d++)
       		{}
}
 /*This function is the instructions to the user
Precondition: none
@retuns the statements
*/
 void Instruct(){
 	printf("HOW TO PLAY:\n");
 	printf("There are two players. Player assigned to dark pieces will be next to move, followed by light\n");
 	printf("Each player will take turns moving their own pieces\n");
 	printf("To move each piece, player inputs the row coordinate (numbers on the left of the board) and column coordinate (bottom of the board) of the piece they want to move\n");
 	printf("Then inputs the row coordinate (numbers on the left of the board) and column coordinate (bottom of the board) of the space they want their piece to move to\n");
 	printf("To win the game, the player that captures all the opponents pieces will be the winner\n");
 	printf("Goodluck and have fun!\n");
 }
int main()
{
	int i, k;
	int j, l;
    // rows and colums of the board, 0 for black box, 1 for empty box, 2 for dark pieces, 3 for light pieces
	int board[8][8]={
    {0,2,0,2,0,2,0,2},
    {2,0,2,0,2,0,2,0}, 
    {0,2,0,2,0,2,0,2}, 
    {1,0,1,0,1,0,1,0}, 
    {0,1,0,1,0,1,0,1}, 
    {3,0,3,0,3,0,3,0},
    {0,3,0,3,0,3,0,3},
	{3,0,3,0,3,0,3,0}};

    int quit = 0;
    int nSelect;

    // continue running if quit != 1
    while (!quit) {
		displayMenu();
        printf("Select choice: ");
        scanf("%d", &nSelect); //scans the choice of user from menu

        switch(nSelect) {
            case 1: {
            	char p = rand_player();
                int player = 0;
                int firstToMove = 0;
                int gameOver = 0;
                int surrender = 0;
                int playerWin = 0;
                int newGame = 1;
				
                while(!gameOver) { //continue if gameOver is != 1
                	clear();
                	Instruct();
                    int nextplayer = 0;
                    // if player has remaining, continue the game, else stop and declare other player winner
                    if(!isPlayerOutOfPieces(board, player + 2)) { //continue if != 1
                        gameOver = 1;
                        if(player == 0) {
                            playerWin = 1;
                     	}else {
                            playerWin = 0;
                        }
                        nextplayer = 1;
                    }
                    // continue playing if no player surrenders and != 1
                    while(!surrender && !nextplayer){
                        nextplayer = 0;
                        displayBoard(board);
                        if(newGame) {
                            if(firstToMove == 0) {
                                printf("\n\nFirst to move: Player %c\n\n", p);
                            }
                        }
                        newGame = 0; // set the newGame to false
                        if(player == 0) {
                            printf("\nDARK's Turn\n");
                        } else {
                            printf("\nLIGHT's Turn\n");
                        }
                        printf("\nEnter [0] in all inputs to surrender.\n");
                        printf("\nEnter current row(X) of piece to be moved: ");
                        scanf("%d",&i);
                        printf("Enter current coulumn(Y) of piece to be moved: ");
                        scanf("%d",&j);
                        printf("\nEnter new row(X) location of piece: ");
                        scanf("%d",&k);
                        printf("Enter new column(Y) location of piece: ");
                        scanf("%d",&l);

                        // if player enters 0 in all input fields, 
                        // declare the player surrenders and stop the game
                        if(i==0 && j==0 && k==0 && l==0) {
                            surrender = 1;
                            gameOver = 1;
                            if(player == 0) {
                                playerWin = 1;
                        }   else {
                                playerWin = 0;
                            }
                    } 	else {
                            if(playTurn(board, player + 2, i-1, j - 1, k-1, l - 1) == 0) {
                                if(player == 0) 
									player = 1;
                                else 
									player = 0;
                                	nextplayer = 1;
                        } 	else {
                                // illegal move if inputs not in criteria
                                printf("\nIllegal move, try again\n");
 
                            }
                    }	if(board[7][0] == 2 || board[7][2] == 2 || board[7][4] == 2 || board[7][6] == 2){//checking if opponent reched the other side of the board
                   			 surrender = 1;
                   			 gameOver = 1;
                    		 playerWin = 0;
                		}
                		else if(board[0][1] == 3 || board[0][3] == 3 || board[0][5] == 3 || board[0][7] == 3){
                			surrender = 1;
                    		gameOver = 1;
                    		playerWin = 1; 
            			}
                    }
                }
				
                    
                if(playerWin == 0) {
                    if(surrender == 1) 
					printf("Player LIGHT surrendered/Lost!\n");
                    printf("Game over! Player %s wins!\n", "DARK");
                } else {
                    if(surrender == 1) 
					printf("Player DARK surrendered/Lost!\n");
                    printf("Game over! Player %s wins!\n", "LIGHT");
                }
                saveScores(playerWin + 2);
            } break;
           
		    case 2: { //shows the score 
                clear();
                printScores();
            } break;
            
			case 3: { //terminated the game
                quit = 1;
                printf("Game will terminate");
                delay();
                clear();
            }    break;
            
			default: {
                printf("Invalid input!\n");
                delay();
                clear();
            }
        }
    }
    return 0;
}
