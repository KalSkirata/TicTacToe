#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"move.h"

move previous_move;

int map_id[3][3] = {{0,1,2},{3,4,5},{6,7,8}}; //mapping for each board with its id

/**
	Check for available moves
	The stack named available is filled with the found moves
	return : the id of the board in which we need to play
**/
int move_available(board boards[], int size){
	int board_id, x, y, i;
	
	available = NULL;

	//define board to play
	board_id = map_id[previous_move.x][previous_move.y];
	
	//search if there is already a winner
	if(boards[board_id].winner=='x' || boards[board_id].winner=='o'){
		//if there is a winner, we can play in every other board
		for(i=0; i<9; i++){
			if(boards[i].winner!='x' && boards[i].winner!='o'){
				board_id=i;
				break;
			}
		}
	}
	
	//search the empty cells
	for(x=0; x<BOARD_DIM; x++){
		for(y=0; y<BOARD_DIM; y++){
			if(boards[board_id].b[x][y]=='-'){
				push(&available, x, y);
			}
		}
	}
	return board_id;
}

/**
	Play a move "m" into the board "boards"
**/
void play(board boards[], move m, int save){
	if(save==1)previous_move=m;
	boards[m.board_id].b[m.x][m.y]=m.player;
}

/**
	Unplay a move "m" into the board "boards"
**/
void unplay(board boards[], move m){
	boards[m.board_id].b[m.x][m.y]='-';
}

/**
	dumb ia which play the last move of the stack available
**/
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

/**
	Check the user's entry and play a valid move
**/
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
	int score, *moveAvailable;
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
		moveAvailable=popById(rand()%length(available) , &available);
		moveToPlay.x=*(moveAvailable);
		moveToPlay.y=*(moveAvailable+1);
		
		//play the random move
		play(board_copy, moveToPlay,1);
	}
	free(board_copy);
	return score;
}

void mc_player(board boards[], int size, int nbPlayout){
	int score[nbPlayout], i, *data, max, moves[nbPlayout][nbPlayout];
	move m,p;
	
	m.board_id=move_available(boards, size);
	m.player='x';
	
	for(i=0; i<nbPlayout; i++) score[i]=0;
	
	copy_move(previous_move,p); //save move made by the other player because playout overwrite it
	
	srand(time(NULL));
	for(i=0; i<nbPlayout; i++){
		//select a random available move
		data=popById(rand()%length(available), &available);
		m.x=*(data);
		m.y=*(data+1);
		
		//store move played to use it later while the comparaison of score
		moves[i][0]=m.x;
		moves[i][1]=m.y;
		
		play(boards,m,0);
		score[i]=mc_playout(boards, size);
		unplay(boards,m);
		
		copy_move(p, previous_move); //restore previous_move value
		move_available(boards, size); //rebuild list of available moves because popById destroy a part of it
	}
	
	copy_move(p, previous_move); //restore value of previous_move
	
	max=0;
	for(i=0; i<nbPlayout; i++)
		if(score[i]>max) max = i;
	
	//play the move with the best score
	m.x=moves[max][0];
	m.y=moves[max][1];
	printf("Monte Carlo play : ");
	display_move(m);
	play(boards, m, 1);
}

void display_move(move m){
	printf("id=%d x=%d y=%d \n", m.board_id, m.x, m.y);
}

/**
	Copy a move source into a move destination
**/
void copy_move(move src, move dst){
	dst.x=src.x;
	dst.y=src.y;
	dst.board_id=src.board_id;
	dst.player=src.player;
}
