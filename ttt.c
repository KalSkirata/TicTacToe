#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

#define BOARDS_NB 9

board boards[BOARDS_NB];
move previous_move;

int main(){
	init_board(boards, BOARDS_NB);
	display_board(boards, BOARDS_NB);
	previous_move.x=1;
	previous_move.y=1;
	previous_move.board_id=4;
	previous_move.player='x';
	move_available(previous_move, boards, BOARDS_NB);
	return 0;
}
