#include<stdio.h>
#include<board.h>

// fill board with "-" character
void init_board(board boards[], int size){
	int x=0, y=0, z=0;

	for(x=0; x<size; x++){
		for(y=0; y<BOARD_DIM; y++){
			for(z=0; z<BOARD_DIM; z++){
				boards[x].b[y][z]='-';
			}
		}
	}
}

void win_small_board(board boards[], int id){
	int i;

	for(i=0; i<BOARD_DIM; i++){
		//line test
		if ((boards[id].b[i][0]=='x' || boards[id].b[i][0]=='o') && (boards[id].b[i][0]==boards[id].b[i][1] && boards[id].b[i][0]==boards[id].b[i][2])){
			boards[id].winner = boards[id].b[i][0];
			return;

		//column test
		}else if ((boards[id].b[0][i]=='x' || boards[id].b[0][i]=='o') && (boards[id].b[0][i]==boards[id].b[1][i] && boards[id].b[0][i]==boards[id].b[2][i])){
			boards[id].winner = boards[id].b[0][i];
			return;
		}
	}

	//diagonal test
	if ((boards[id].b[0][0] != '-') && (boards[id].b[0][0] == boards[id].b[1][1]) && (boards[id].b[0][0] == boards[id].b[2][2])){
		boards[id].winner = boards[id].b[0][0];
		return;
		
	}else if ((boards[id].b[2][0] != '-') && (boards[id].b[2][0] == boards[id].b[1][1]) && (boards[id].b[2][0] == boards[id].b[0][2])){
		boards[id].winner = boards[id].b[2][0];
		return;
	}
}

/*
	return the state of the entire board
	-1 : no winner, keep going
	0 : draw
	1 : player 1 win
	2 : player 2 win
*/
int state(board boards[]){
	int i;
	for(i=0; i<BOARD_DIM*BOARD_DIM; i++){
		win_small_board(boards, i);
	}

	//left to right diagonal
	if((boards[0].winner=='x' || boards[0].winner=='o') && boards[0].winner==boards[4].winner && boards[0].winner==boards[8].winner){
		return 1;
	//right to left diagonal
	}else if((boards[2].winner=='x' || boards[2].winner=='o') && boards[2].winner==boards[4].winner && boards[2].winner==boards[6].winner){
		return 1;
	}

	for(i=0; i<BOARD_DIM; i++){
		//vertical test
		if((boards[i].winner=='x' || boards[i].winner=='o') && boards[i].winner==boards[i+3].winner && boards[i].winner==boards[i+6].winner){
			return 1;
		//horizontal test
		}else if((boards[i*BOARD_DIM].winner=='x' || boards[i*BOARD_DIM].winner=='o') && boards[i*BOARD_DIM].winner==boards[i*BOARD_DIM+1].winner && boards[i*BOARD_DIM].winner==boards[i*BOARD_DIM+2].winner){
			return 1;
		}
	}
	return -1;
}


void display_board(board boards[], int size){
	int i, cpt=0;
	while(cpt<size){
		for(i=0; i<BOARD_DIM; i++){
			printf("%c%c%c %c%c%c %c%c%c \n", boards[cpt].b[i][0], boards[cpt].b[i][1], boards[cpt].b[i][2],
											boards[cpt+1].b[i][0], boards[cpt+1].b[i][1], boards[cpt+1].b[i][2],
											boards[cpt+2].b[i][0], boards[cpt+2].b[i][1], boards[cpt+2].b[i][2]);
		}
		cpt+=BOARD_DIM;
		printf("\n");
	}
	printf("--------------------------- \n");
}

void copyBoard(board src[], board dst[], int size){
	int i, x, y;
	for(i=0; i<size; i++){
		for(x=0; x<BOARD_DIM; x++){
			for(x=0; x<BOARD_DIM; x++){
				dst[i].b[x][y]=src[i].b[x][y];
			}
		}
	} 
}
