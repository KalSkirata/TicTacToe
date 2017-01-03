#include<stdio.h>
#include<stdlib.h>
#include"move.h"

move previous_move;

int map_id[3][3] = {{0,1,2},{3,4,5},{6,7,8}}; //id for each cell of board

int move_available(board boards[], int size){
	int board_id, x, y, cpt=0,i;
	
	available = NULL;

	//define board to play
	board_id = map_id[previous_move.x][previous_move.y];
	printf("board_id=%d pm.x=%d pm.y=%d \n", board_id, previous_move.x, previous_move.y);
	//search if there is already a winner
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
	previous_move=m;
	boards[m.board_id].b[m.x][m.y]=m.player;
}

void unplay(board boards[], move m){
	boards[m.board_id].b[m.x][m.y]='-';
}

//dumb ia which take the last move of the stack
void dumb_ia(board boards[], int BOARDS_NB){
	int* move;
	previous_move.board_id=move_available(boards, BOARDS_NB);
	move = pop(&available);
	previous_move.player='x';
	previous_move.x=*(move);
	previous_move.y=*(move+1);
	printf("IA play : x=%d y=%d \n", previous_move.x, previous_move.y);
	play(boards, previous_move);
}

void human_move(board boards[], int BOARDS_NB){
	int i,x,y;
	while(1){
		printf("move to play:");
		scanf("%d %d %d", &i, &x, &y);
		if(map_id[previous_move.x][previous_move.y]!=i){
			if(boards[map_id[previous_move.x][previous_move.y]].winner=='x' || boards[map_id[previous_move.x][previous_move.y]].winner=='o'){
				if(boards[i].winner=='x' || boards[i].winner=='o'){
					printf("Board %d already won \n",i);
				}else{
					printf("no winner in board %d \n",i);
					if(boards[i].b[x][y]!='-'){
						printf("This cell is already set \n");
					}else{
						break;
					}
				}
			}else{
				printf("You can only play in board %d \n", map_id[previous_move.x][previous_move.y]);
			}
		}else{
			if(boards[map_id[previous_move.x][previous_move.y]].winner=='x' || boards[map_id[previous_move.x][previous_move.y]].winner=='o'){
				printf("You can't play in a board already won \n");
			}else{
				if(boards[i].b[x][y]!='-'){
					printf("This cell is already set \n");
				}else{
					break;
				}
			}
		}
	}
	previous_move.player='o';
	previous_move.x=x;
	previous_move.y=y;
	previous_move.board_id=i;
	printf("Human play : id=%d x=%d y=%d \n", previous_move.board_id, previous_move.x, previous_move.y);
	play(boards, previous_move);
}
