#include"board.h"
#include"stack.h"

struct move{
	int x, y, board_id;
	char player;
};

typedef struct move move;

stack *available;

void play(board boards[], move m);

void unplay(board boards[], move m);

int move_available(board boards[], int size);

void dumb_ia(board boards[], int BOARD_NB);

void human_move(board boards[], int BOARDS_NB);

void mc_player(board boards[], int size, int nbPlayout);

void display_move(move m);
