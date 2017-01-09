#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "move.h"

#define BOARDS_NB 9
#define NB_PLAYOUT 50

board boards[BOARDS_NB];

move m;

int main(){
	init_board(boards, BOARDS_NB);
	display_board(boards, BOARDS_NB);
	
	//IA play its first move in the center of the board
	m.x=1;
	m.y=1;
	m.board_id=4;
	m.player='x';
	printf("IA play : id=%d x=%d y=%d \n", m.board_id, m.x, m.y);
	play(boards, m, 1);
	
	display_board(boards, BOARDS_NB);
	while(state(boards)==-1){
		human_move(boards, BOARDS_NB);
		display_board(boards, BOARDS_NB);
		if(state(boards)>-1) break;
		mc_player(boards, BOARDS_NB, NB_PLAYOUT);
		display_board(boards, BOARDS_NB);
	}
	return 0;
}
