struct board{
	char b[3][3];
};

typedef struct board board;

// fill board with "-" character
void init_board(board boards[]);

void display_board(board boards[]);
