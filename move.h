#include"board.h"
#include"stack.h"

struct move{
	int x, y, board_id;
	char player;
};

typedef struct move move;

stack *available;

void play(board boards[], move m);

int unplay(move m); //TODO

int move_available(move previous_move, board boards[], int size);
