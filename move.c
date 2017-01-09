#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"move.h"

move previous_move;

int map_id[3][3] = {{0,1,2},{3,4,5},{6,7,8}}; //id for each cell of board

int move_available(board boards[], int size){
	int board_id, x, y, cpt=0,i;
	
	available = NULL;

	//define board to play
	board_id = map_id[previous_move.x][previous_move.y];
	//printf("%s : board_id=%d pm.x=%d pm.y=%d pm.id=%d pm.p=%c\n", __func__, board_id, previous_move.x, previous_move.y, previous_move.board_id, previous_move.player);
	//search if there is already a winner
	if(boards[board_id].winner=='x' || boards[board_id].winner=='o'){
		for(i=0; i<9; i++){ //parcours tous les plateaux
			if(boards[i].winner!='x' && boards[i].winner!='o'){
				board_id=i;
				//printf("board_id changes to %d \n", i);
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
	//display(available);
	//clear(&move_available);
	return board_id;
}

void play(board boards[], move m, int save){
	if(save==1)previous_move=m;
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
	play(boards, previous_move,1);
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
	play(boards, previous_move, 1);
}

int mc_playout(board boards[], int size){
	int score, r;
	int *moveAvailable;
	move moveToPlay;
	moveToPlay.player='x';
	
	//copy of actual board
	board *board_copy = malloc(size*sizeof(board));
	copyBoard(boards, board_copy, size);

	srand(time(NULL));
	while((score=state(board_copy))==-1){
		//generate list of move available
		moveToPlay.board_id=move_available(board_copy, size);
		//pick one random move in this list
		r = rand()%length(available);
		printf("%s : r=%d \n", __func__, r);
		moveAvailable=popById(r, &available);
		moveToPlay.x=*(moveAvailable);
		moveToPlay.y=*(moveAvailable+1);
		printf("%s : moveToPlay.x=%d moveToPlay.y=%d \n", __func__, moveToPlay.x, moveToPlay.y);
		//play the random move
		play(board_copy, moveToPlay,1);
	}
	free(board_copy);
	return score;
}

void mc_player(board boards[], int size, int nbPlayout){
	int score[nbPlayout], i, *data, max, r, moves[nbPlayout][nbPlayout];
	move m,p;
	
	m.board_id=move_available(boards, size);
	m.player='x';
	
	for(i=0; i<size; i++) score[i]=0;
	
	copy_move(previous_move,p); //save move made by the other player because playout overwrite it
	
	srand(time(NULL));
	for(i=0; i<nbPlayout; i++){
		display_stack(available);
		r = rand()%length(available);
		printf("%s : rand=%d length=%d\n", __func__,r,length(available));
		data=popById(r, &available);
		m.x=*(data);
		m.y=*(data+1);
		//store move played to use it later while the comparaison of score
		moves[i][0]=m.x;
		moves[i][1]=m.y;
		//printf("%s : m.id=%d m.player=%c m.x=%d m.y=%d \n", __func__, m.board_id, m.player, m.x, m.y);
		play(boards,m,0);
		score[i]=mc_playout(boards, size);
		//printf("%s : score[%d]=%d \n", __func__, i, score[i]);
		unplay(boards,m);
		copy_move(p, previous_move); //restore previous_move value
		move_available(boards, size); //rebuild list of available moves because popById destroy a part of it
	}
	
	copy_move(p, previous_move); //restore value of previous_move
	
	max=0;
	for(i=0; i<nbPlayout; i++){
		//printf("%s : score[%d]=%d \n", __func__, i, score[i]);
		if(score[i]>max) max = i;
	}
	
	//data = popById(max, &available);
	m.x=moves[max][0];
	m.y=moves[max][1];
	printf("\n%s : previous_move=",__func__);
	display_move(previous_move);
	printf("\n%s : move=",__func__);
	display_move(m);
	display_stack(available);	
	play(boards, m, 1);
}

void display_move(move m){
	printf("move : id=%d x=%d y=%d player=%c \n", m.board_id, m.x, m.y, m.player);
}

void copy_move(move src, move dst){
	dst.x=src.x;
	dst.y=src.y;
	dst.board_id=src.board_id;
	dst.player=src.player;
}
