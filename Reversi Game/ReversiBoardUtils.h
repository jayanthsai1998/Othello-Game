#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ReversiGame
{
	char **board;	// char 'w' for whites, 'b' for blacks ' ' for empty 
	// do allocate memory for '\0' as it is character array.
	char *player1name;
	char *player2name;
	int whiteCount = 0;
	int blackCount = 0;
	int NumberofMoves = 0;
	int rows, cols;
	int turn = 1;   //1 for white, -1 for black
	int state = 0;  //0 for unfinished, 1 for game over
	int winner = 0; //1 for white, -1 for black
}ReversiGame;


void endGame(ReversiGame *game);
int hasMove(ReversiGame *game);
void modifyTurn(ReversiGame *game);

/*

Create a new ReversiGame By allocating memory from Heap , Let it be game;
Create a 2D Array from Heap(Dynamically) with specified number of rows and cols
and copy its reference to game->board;

Note : Return NULL for Invalid Inputs
Note : Copy Rows into newlyCreatedBoard->rows , and vice versa for cols ,
Also copy player1name,player2name.
*/

ReversiGame * createNewGame(int rows, int cols, char *player1, char *player2)
{
	if (rows != cols)
		return NULL;
	ReversiGame *changeThis = (ReversiGame*)malloc(sizeof(ReversiGame));
	int p;
	char **myrev = (char**)malloc(rows*sizeof(char*));
	for (p = 0; p < rows; p++)
	{
		myrev[p] = (char*)malloc((cols + 1)*sizeof(char));
	}
	changeThis->board = myrev;
	changeThis->player1name = player1;
	changeThis->player2name = player2;
	changeThis->whiteCount = 0;
	changeThis->blackCount = 0;
	changeThis->NumberofMoves = 0;
	changeThis->rows = rows;
	changeThis->cols = cols;
	changeThis->turn = 1;
	changeThis->state = 0;
	changeThis->winner = 0;
	return changeThis;
}


/*
Copy the tobeCopied Array into game->board .
Learn how to Copy a 2D array when address of first row is given.
Note this function is called in the following way

Also Initialize the turn variable, whiteCount with no of white coins and same for black.

Do Nothing for Invalid Inputs
*/

void initializeReversiGame(ReversiGame *game, char *tobeCopiedBoard, int rows, int cols, int turn)
{
	int i, j, p = 0, k;
	game->whiteCount = 0;
	game->blackCount = 0;
	if (rows <= 0 || cols <= 0 || rows != cols || game == NULL || tobeCopiedBoard == NULL)
	{
	}
	else
	{
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j <= cols; j++)
			{
				game->board[i][j] = tobeCopiedBoard[p++];
				if (game->board[i][j] == 'w')
					game->whiteCount = game->whiteCount + 1;
				else if (game->board[i][j] == 'b')
					game->blackCount = game->blackCount + 1;
			}
		}
		game->rows = rows;
		game->cols = cols;
		game->turn = turn;
		k = hasMove(game);
		if (k == 0)
		{
			modifyTurn(game);
		}
		if (game->whiteCount + game->blackCount == rows*cols)
		{
			endGame(game);
		}
	}
}

/*
Check if the Current board is in End Position . Return 0 if the game is Ended, 1 if not .
Win Condition : Either all the squares are filled or a stalemate position (No one can Move)

*/

int checkReversiGameOver(ReversiGame *game)
{
	if (((game->rows)*(game->cols)) == game->whiteCount + game->blackCount)
	{
		endGame(game);
		return 0;
	}
	int wh, bl;
	wh = hasMove(game);
	if (wh == 0)
	{
		modifyTurn(game);
		bl = hasMove(game);
		if (bl == 0)
		{
			endGame(game);
			return 0;
		}
		else
			return 1;
	}
	return 1;
}

void printMoves(ReversiGame *game)
{
	/*
	Sample output :
	Whites Count : 5
	Black Count : 4
	Move Count : 9
	*/
	printf("Whites Count : %d", game->whiteCount);
	printf("Black Count : %d", game->blackCount);
	printf("Move Count : %d", game->whiteCount + game->blackCount);
}

/*
Print the Board in a Good Way.Make sure Each Number is properly formatted and Seperated, and Row lines too .
Print Empty Space when you encounter 0.Also make sure your board looks good for 5x5 or 7x7 boards too .
Use your Thinking / UI Skills .
See the link we shared for sample screenshots for inspiration.
*/

void drawBoardOnScreen(ReversiGame *game)
{
	return;
}

/*
Clear The Screen , So that we can redraw the Board (which has modified values )
*/

void clearScreen(ReversiGame *game)
{
	system("cls");
}

/*
Clear the Screen and ReDraw the Board ,Call above two functions
*/

void clearAndRedrawScreen(ReversiGame *game)
{

}
