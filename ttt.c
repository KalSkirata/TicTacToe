#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "move.h"

#define BOARDS_NB 9

board boards[BOARDS_NB];
move previous_move;

int map[3][3] = {{0,1,2},{3,4,5},{6,7,8}}; //id for each cell of board

void ia_move(){
	int* move;
	previous_move.board_id=move_available(previous_move, boards, BOARDS_NB);
	move = pop(&available);
	previous_move.player='x';
	previous_move.x=*(move);
	previous_move.y=*(move+1);
	printf("IA play : x=%d y=%d \n", previous_move.x, previous_move.y);
	play(boards, previous_move);
}

void human_move(){
	int i,x,y;
	while(1){
		printf("move to play:");
		scanf("%d %d %d", &i, &x, &y);
		if(map[previous_move.x][previous_move.y]!=i){
			if(boards[map[previous_move.x][previous_move.y]].winner=='x' || boards[map[previous_move.x][previous_move.y]].winner=='o'){
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
				printf("You can only play in board %d \n", map[previous_move.x][previous_move.y]);
			}
		}else{
			if(boards[map[previous_move.x][previous_move.y]].winner=='x' || boards[map[previous_move.x][previous_move.y]].winner=='o'){
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

int main(){
	init_board(boards, BOARDS_NB);
	display_board(boards, BOARDS_NB);
	previous_move.x=1;
	previous_move.y=1;
	previous_move.board_id=4;
	previous_move.player='x';
	printf("IA play : id=%d x=%d y=%d \n", previous_move.board_id, previous_move.x, previous_move.y);
	play(boards, previous_move);
	display_board(boards, BOARDS_NB);
	while(state(boards)==-1){
		human_move();
		display_board(boards, BOARDS_NB);
		if(state(boards)>-1) break;
		ia_move();
		display_board(boards, BOARDS_NB);
	}
	return 0;
}
