#include <stdio.h>
#include <board.h>

board boards[9];

int main(){
	init_board(boards);
	display_board(boards);
	return 0;
}
