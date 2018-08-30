
/*
This struct denotes the move played by user, X means the x cordinate and Y means y cordinate.
*/
typedef struct ReversiMove
{
	int x, y;
}ReversiMove;

/*
Create a ReversiMove struct (malloc/calloc etc) and return it.
Assign parameters x and y to its fields.
*/
ReversiMove *createMove(int x, int y)
{
	ReversiMove *mv = (ReversiMove*)malloc(sizeof(ReversiMove));
	mv->x = x;
	mv->y = y;
	return mv;
}

/*
Take Only Valid Input x, y two integers . If Invalid input is entered ,Take input again . Keep Taking input until its valid
Hint : Use While Loop and isValidInput function
Cordinates are 1 indexed. Ie first row/column is denoted by 1 while giving input.
*/

ReversiMove *inputMove(ReversiGame *game)
{

	return NULL;
}


/*
To check the validity of coordinate on the board
*/

int isvalidCoordinate(ReversiGame *game, int x, int y)
{
	x--;
	y--;
	if (y < game->rows && x >= 0 && x < game->cols && y >= 0)
	{
		if (game->board[y][x] == ' ')
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

/*
Check if the move can be placed, if its going to make a valid capture to the opponent coins
*/

int isValidMove(ReversiGame *game, ReversiMove *move)
{
	int cd1, cd2, verify, i, j, p = 0, s, t, cn, v, g = 0;
	char op;
	int a[16];
	cd1 = move->x;
	cd2 = move->y;
	verify = isvalidCoordinate(game, cd1, cd2);
	if (verify == 1)
	{
		for (i = cd1 - 1; i <= cd1 + 1; i++)
		{
			for (j = cd2 - 1; j <= cd2 + 1; j++)
			{
				if (i == cd1 && j == cd2)
				{
				}
				else
				{
					a[p++] = i;
					a[p++] = j;
				}
			}
		}
		if (game->turn == 1)
			op = 'w';
		else
			op = 'b';
		for (i = 0, v = 1; i < 16; i = i + 2, v++)
		{
			s = a[i];
			t = a[i + 1];
			cn = 0;
			s--;
			t--;
			while (t<(game->rows) && s<(game->cols) && s >= 0 && t >= 0)
			{
				if (game->board[t][s] == ' ')
					break;
				else
				{
					if (game->board[t][s] != op)
					{
						cn++;
						if (v == 1)
						{
							s--;
							t--;
						}
						else if (v == 2)
						{
							s--;
						}
						else if (v == 3)
						{
							s--;
							t++;
						}
						else if (v == 4)
						{
							t--;
						}
						else if (v == 5)
						{
							t++;
						}
						else if (v == 6)
						{
							s++;
							t--;
						}
						else if (v == 7)
						{
							s++;
						}
						else if (v == 8)
						{
							s++;
							t++;
						}
					}
					else
					{
						if (cn > 0)
						{
							g = 1;
							break;
						}
						else
							break;
					}
				}
			}
			if (g == 1)
				break;
		}
		if (g == 1)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
/*
Check if the player can move , if the player is not able to move, he looses the turn
and the opponent gets the chance to play.
If both players are not able to make a move, then the game ends.
*/

int hasMove(ReversiGame *game)
{
	int can = 0, i, j;

	for (i = 0; i < game->rows; i++)
	{
		for (j = 0; j < game->cols; j++)
		{
			if (game->board[i][j] == ' ')
			{
				ReversiMove *t = createMove(j + 1, i + 1);
				can = isValidMove(game, t);
				if (can == 1)
					break;
			}
		}
		if (can == 1)
			break;
	}
	if (can == 1)
		return 1;
	else
		return 0;
}

/*
Increment the number of moves in ReversiGame struct.
*/
void incrementMoves(ReversiGame *game)
{
	game->NumberofMoves++;
}

/*
Toggle the turn in Reversi Game.
This function is to be called when you want to change the turn.
*/
void modifyTurn(ReversiGame *game)
{
	if (game->turn == 1)
		game->turn = -1;
	else
		game->turn = 1;
}

/*
End Reversi Game.
Populate game->winner field accordingly with who won. 1 for white, -1 for black.
This function is to be called when the game is ended.
*/
void endGame(ReversiGame *game)
{
	if (game->whiteCount > game->blackCount)
		game->winner = 1;
	else if (game->whiteCount < game->blackCount)
		game->winner = -1;
	else
		game->winner = 0;
	game->state = 1;
}

/*
Wrapper function you will call only modify to increment moves and modify the turn.
*/

void modify(ReversiGame *game)
{
	incrementMoves(game);
	modifyTurn(game);
}


/*
This function performs move action on the board
Note : call validity check performs using above functions before making a move
returns :
true on move sucess
false if move is invalid
*/

bool playMove(ReversiGame *game, ReversiMove *move)
{
	int ch, i, j, f, m, n, h = 0, r;

	f = isValidMove(game, move);
	if (f == 1)
	{
		int cd1, cd2, verify, i, j, p = 0, s, t, cn, v;
		char op;
		int a[16];
		cd1 = move->x;
		cd2 = move->y;
		for (i = cd1 - 1; i <= cd1 + 1; i++)
		{
			for (j = cd2 - 1; j <= cd2 + 1; j++)
			{
				if (i == cd1 && j == cd2)
				{
				}
				else
				{
					a[p++] = i;
					a[p++] = j;
				}
			}
		}
		if (game->turn == 1)
			op = 'w';
		else
			op = 'b';
		for (i = 0, v = 1; i < 16; i += 2, v++)
		{
			r = 0;
			s = a[i];
			t = a[i + 1];
			cn = 0;
			s--;
			t--;
			while (s<(game->cols) && t<(game->rows) && s >= 0 && t >= 0)
			{
				if (game->board[t][s] == ' ')
					break;
				else
				{
					if (game->board[t][s] != op)
					{
						cn++;
						if (v == 1)
						{
							s--;
							t--;
						}
						else if (v == 2)
							s--;
						else if (v == 3)
						{
							s--;
							t++;
						}
						else if (v == 4)
							t--;
						else if (v == 5)
							t++;
						else if (v == 6)
						{
							s++;
							t--;
						}
						else if (v == 7)
							s++;
						else if (v == 8)
						{
							s++;
							t++;
						}
					}
					else
					{
						if (cn > 0)
						{
							m = cd1 - 1, n = cd2 - 1;
							while (m != s || n != t)
							{
								game->board[n][m] = op;
								if (v == 1){ m--; n--; }
								else if (v == 2){ m--; }
								else if (v == 3){ m--; n++; }
								else if (v == 4){ n--; }
								else if (v == 5){ n++; }
								else if (v == 6){ m++; n--; }
								else if (v == 7){ m++; }
								else if (v == 8){ m++; n++; }

							}
						}
						break;
					}
				}
			}
		}
		game->whiteCount = 0; game->blackCount = 0;
		for (i = 0; i < game->rows; i++)
		{
			for (j = 0; j < game->cols; j++)
			{
				if (game->board[i][j] == 'w')
					game->whiteCount++;
				else if (game->board[i][j] == 'b')
					game->blackCount++;
			}
		}
		modify(game);
		ch = hasMove(game);
		if (ch == 0)
		{
			modifyTurn(game);
		}
		return true;
	}
	return false;

}


void printWinner(ReversiGame *game) {
	/*
	Sample output :
	Result Praveen has won. / Game is Drawn.
	*/
	if (game->winner == 1)
		printf("%s has won", game->player1name);
	else if (game->winner == -1)
		printf("%s has won", game->player2name);
	else
		printf("Game is drawn");
}