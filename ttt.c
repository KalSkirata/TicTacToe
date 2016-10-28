#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

#define BOARDS_NB 9

board boards[BOARDS_NB];

int main(){
	init_board(boards, BOARDS_NB);
	display_board(boards, BOARDS_NB);
	move_available(NULL, boards, BOARDS_NB);
	return 0;
}
