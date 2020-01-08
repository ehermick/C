/**
 * Description: Homework Part 2 for Assignment #2 - CSE 240 - Spring 2019
 *              Make a program to populate a game board with pieces and to
 *              move those pieces around the board
 *
 * Completion Time: ~ 4 hour
 *
 * Emma Hermick
 *
 * Version 1.0
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 //New structure called game_piece
struct game_piece
{
	//Variable
	char label[30];
};

//game_board structure
//Contains 2D array called "board" (game_piece type)
//2 ints, rows and columns
struct game_board
{
	int rows, columns;
	struct game_piece **board;
};

//Assign the default string "---" to the game piece's label
void
game_piece_init_default(struct game_piece *piece)
{
	strcpy(piece->label, "---");
}

//Assign the game piece's label with the new_label
void
game_piece_init(struct game_piece *piece, char *new_label)
{
	strcpy(piece->label, new_label);
}

//Returns the piece's label
char *
game_piece_get_label(struct game_piece *piece)
{
	return piece->label;
}

//Constructs a string of length 3 from the piece's label
char *
game_piece_to_string(struct game_piece *piece)
{
	char *tPiece = malloc(3 * (sizeof(char)));

	for (int i = 0; i < 3; i++)
	{
		*(tPiece + i) = piece->label[i];
		return tPiece;
	}
}

//Instantiates 2D array to the size rows x columns
//Initializes each game_piece element of array using function
void
game_board_init(struct game_board *game_board, int rows, int cols)
{
	game_board -> board = (struct game_piece **) malloc(rows * sizeof(struct game_piece *));

	for (int r = 0; r < rows; r++)
	{
		game_board->board[rows] = (struct game_piece *) malloc(cols * sizeof(struct game_piece));

		for (int c = 0; c < cols; c++)
		{
			struct game_piece temp;
			game_piece_init_default(&temp);
			game_board->board[rows][cols] = temp;
		}
	}
}

//Checks if the parameters row and col are valid
int
game_board_is_space_valid(struct game_board *game_board, int row, int col)
{
	game_board ->board;

	//if at least one of the parameters row or col is less than
	//0 or larger than the last index of the array
	if (row < 0 || col < 0 || row >= game_board -> rows || col >= game_board -> columns)
	{
		//Then it returns 0 (false)
		return 0;
	}

	//Otherwise it returns 1 (true)
	else
	{
		return 1;
	}
}

//Validates that the space is valid and that the space is not occupied
int
game_board_add_piece(struct game_board *game_board, struct game_piece *piece,
	int row, int col)
{
	//If game_piece has default label, space is not occupied
	if (strcmp(game_board->board[row][col].label, "---") == 0
		&& (game_board_is_space_valid(game_board, row, col) == 1))
	{
		//If space is valid and not occupied then space should be replaced
		//by the parameter "piece" and method returns 1
		game_piece_init(&game_board->board[row][col], game_piece_get_label(+piece));
		return 1;
	}

	//Otherwise returns 0
	return 0;
}

//Validates that both src and dest spaces are valid and dest space not occupied
int
game_board_move_piece(struct game_board *game_board, int src_row,
	int src_col, int dest_row, int dest_col)
{
	//If game_piece has default label, space is not occupied
	if (strcmp(game_board->board[src_row][src_col].label, "---") == 0
		&& (game_board_is_space_valid(game_board, src_row, src_col) == 1))
	{
		//If both pass, then piece (src_row, src_col) moved to (dest_row, dest_col)
		strcpy(piece(dest_row, dest_col), (src_row, src_col));

		//The space at (src_row, src_col) should be replaced by the default game_piece
		strcpy(piece(src_row, src_col), game_piece_init_default);
		//If this method moves the piece, return 1
		return 1;
	}
	//Otherwise return 0
	else
	{
		return 0;
	}
}

//Prints information of the board
//Shows the list of pieces placed on the board
void
game_board_print(struct game_board *game_board)
{
	printf("The GameBoard" + "\n" + "--------------------" + "\n");

	for (int i = 0; i < game_board -> rows; i++)
	{
		for (int j = 0; j < game_board -> columns; j++)
		{
			game_piece_to_string(&game_board->board[i][j]);
		}
		printf("\n");

	}
}

int
main()
{
	/* declare local variables */
	int row;
	int col;
	int destRow;
	int destCol;
	int rowNum;
	int colNum;
	struct game_board board;
	struct game_piece piece;
	char input_string[30];

	/* get the size of the game board */
	printf("Please enter the number of rows.\n");
	scanf("%d", &rowNum);

	printf("Please enter the number of columns.\n");
	scanf("%d", &colNum);

	game_board_init(&board, rowNum, colNum);

	/* get the first piece's label */
	printf("Please enter a label for a new piece. Enter \"Q\" when done.\n");
	scanf("%s", input_string);

	while (strcmp(input_string, "Q") != 0 && strcmp(input_string, "q") != 0)
	{
		game_piece_init(&piece, input_string);

		/* get the location to place the piece */
		printf("Please enter a row for the piece.\n");
		scanf("%d", &row);

		printf("Please enter a column for the piece.\n");
		scanf("%d", &col);

		/* verify the space is valid then add the piece to the board */
		if (game_board_is_space_valid(&board, row, col))
		{
			if (game_board_add_piece(&board, &piece, row, col))
			{
				printf("New piece \"%s\" added.\n",
					game_piece_get_label(&piece));
			}
			else
			{
				printf("A piece is already at that space.\n");
			}
		}
		else
		{
			printf("Invalid row and/or column.\n");
		}

		/* get the label for the next piece */
		printf("Please enter a label for a new piece. Enter \"Q\" when done.");
		scanf("%s", input_string);
	}

	/* print the board and check if user wants to move a piece */
	game_board_print(&board);
	printf("Would you like to move a piece? Enter \"Y\" to move a piece.\n");
	scanf("%s", input_string);

	while (strcmp(input_string, "Y") == 0 || strcmp(input_string, "y") == 0)
	{
		/* get the location of the piece */
		printf("Please enter the piece's row.");
		scanf("%d", &row);

		printf("Please enter the piece's column.");
		scanf("%d", &col);

		/* get the destination for the piece */
		printf("Please enter the piece's new row.");
		scanf("%d", &destRow);

		printf("Please enter the piece's new column.");
		scanf("%d", &destCol);

		/* verify both spaces are valid then move the piece */
		if (game_board_is_space_valid(&board, row, col) &&
			game_board_is_space_valid(&board, destRow, destCol))
		{
			if (game_board_move_piece(&board, row, col, destRow, destCol))
			{
				printf("Piece moved to new space.\n");
			}
			else
			{
				printf("A piece is already in that space.\n");
			}
		}
		else
		{
			printf("A row or column is invalid. No piece moved.\n");
		}

		/* print the board and check if the user wants move another piece */
		game_board_print(&board);
		printf
		("Would you like to move a piece? Enter \"Y\" to move a piece.\n");
		scanf("%s", input_string);
	}

	return 0;
}