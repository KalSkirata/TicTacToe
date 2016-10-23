#include <stdio.h>
#include <board.h>

#define BOARDS_NB 9

board boards[BOARDS_NB];

int main(){
	init_board(boards, BOARDS_NB);
	display_board(boards, BOARDS_NB);
	return 0;
}
