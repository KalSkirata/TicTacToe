#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "move.h"

#define BOARDS_NB 9

board boards[BOARDS_NB];
move previous_move;

void ia_move(){
	int r;
	srand(time(NULL));
	r = rand()%move_available(previous_move, boards, BOARDS_NB);
}

void human_move(){
	printf("move to play:");
	scanf("%d %d %d", &previous_move.board_id, &previous_move.x, &previous_move.y);
	previous_move.player='o';
	play(boards, previous_move);
}

int main(){
	init_board(boards, BOARDS_NB);
	display_board(boards, BOARDS_NB);
	previous_move.x=1;
	previous_move.y=1;
	previous_move.board_id=4;
	previous_move.player='x';
	play(boards, previous_move);
	while(state(boards)==-1){
		display_board(boards, BOARDS_NB);
		human_move();
		display_board(boards, BOARDS_NB);
		ia_move();
		display_board(boards, BOARDS_NB);
	}
	return 0;
}
