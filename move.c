#include<stdlib.h>
#include"move.h"
#include"board.h"
#include"stack.h"

int id[3][3] = {{0,1,2},{3,4,5},{6,7,8}}; //id for each cell of board

void move_available(move previous_move, board boards[], int size){
	int board_id, x, y, cpt=0;
	
	stack *move_available = NULL;

	//define board to play
	board_id = id[previous_move.x][previous_move.y];
	//search the empty cells
	for(x=0; x<BOARD_DIM; x++){
		for(y=0; y<BOARD_DIM; y++){
			if(boards[board_id].b[x][y]=='-'){
				push(&move_available, x, y);
				cpt++;
			}
		}
	}
	display(move_available);
	clear(&move_available);
}
