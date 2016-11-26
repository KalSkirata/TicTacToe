#include<stdio.h>
#include<stdlib.h>
#include"move.h"

int id[3][3] = {{0,1,2},{3,4,5},{6,7,8}}; //id for each cell of board

int move_available(move previous_move, board boards[], int size){
	int board_id, x, y, cpt=0,i;
	
	available = NULL;

	//define board to play
	board_id = id[previous_move.x][previous_move.y];
	printf("board_id=%d pm.x=%d pm.y=%d \n", board_id, previous_move.x, previous_move.y);
	if(boards[board_id].winner=='x' || boards[board_id].winner=='o'){
		for(i=0; i<9; i++){ //parcours tous les plateaux
			if(boards[i].winner!='x' && boards[i].winner!='o'){
				board_id=i;
				printf("board_id changes to %d \n", i);
				break;
			}
		}
	}
	//search the empty cells
	for(x=0; x<BOARD_DIM; x++){
		for(y=0; y<BOARD_DIM; y++){
			if(boards[board_id].b[x][y]=='-'){
				push(&available, x, y);
				cpt++;
			}
		}
	}
	display(available);
	//clear(&move_available);
	return board_id;
}

void play(board boards[], move m){
	boards[m.board_id].b[m.x][m.y]=m.player;
}
