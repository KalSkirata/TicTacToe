#include "board.h"

struct move{
	int x, y, board_id;
	char player;
};

typedef struct move move;

int play(move m); //TODO

void move_available(move previous_move, board boards[], int size);
