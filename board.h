#ifndef BOARD
#define BOARD

#define BOARD_DIM 3

struct board{
	char b[BOARD_DIM][BOARD_DIM];
};

typedef struct board board;

// fill board with "-" character
void init_board(board boards[], int size);

void display_board(board boards[], int size);

#endif
