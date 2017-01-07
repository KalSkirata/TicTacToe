#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "move.h"

#define BOARDS_NB 9

board boards[BOARDS_NB];

move m;

int main(){
	init_board(boards, BOARDS_NB);
	display_board(boards, BOARDS_NB);
	m.x=1;
	m.y=1;
	m.board_id=4;
	m.player='x';
	printf("IA play : id=%d x=%d y=%d \n", m.board_id, m.x, m.y);
	play(boards, m);
	display_board(boards, BOARDS_NB);
	while(state(boards)==-1){
		human_move(boards, BOARDS_NB);
		display_board(boards, BOARDS_NB);
		if(state(boards)>-1) break;
		//dumb_ia(boards, BOARDS_NB);
		mc_player(boards, BOARDS_NB, 5);
		display_board(boards, BOARDS_NB);
	}
	return 0;
}
