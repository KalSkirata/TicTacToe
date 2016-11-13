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

void win_small_board(board boards[], int id_board){
	int i;

	for(i=0; i<BOARD_DIM; i++){
		//line test
		if ((boards[id_board].b[i][0]=='x' || boards[id_board].b[i][0]=='o') && (boards[id_board].b[i][0]==boards[id_board].b[i][1] && boards[id_board].b[i][0]==boards[id_board].b[i][2])){
			boards[id_board].player = boards[id_board].b[i][0];

		//column test
		}else if ((boards[id_board].b[0][i]=='x' || boards[id_board].b[0][i]=='o') && (boards[id_board].b[0][i]==boards[id_board].b[1][i] && boards[id_board].b[0][i]==boards[id_board].b[2][i])){
			boards[id_board].player = boards[id_board].b[0][i];
		}
	}

	//diagonal test
	if ((boards[id_board].b[0][0] != '-') && (boards[id_board].b[0][0] == boards[id_board].b[1][1]) && (boards[id_board].b[0][0] == boards[id_board].b[2][2])){
		boards[id_board].player = boards[id_board].b[0][0];
		
	}else if ((boards[id_board].b[2][0] != '-') && (boards[id_board].b[2][0] == boards[id_board].b[1][1]) && (boards[id_board].b[0][0] == boards[id_board].b[0][2])){
		boards[id_board].player = boards[id_board].b[2][0];
	}
}

void win_big_board(board boards[], int id_board){
	int i;
	for(i=0; i<3; i++){
		if ((boards[id_board].player =='x' || boards[id_board].player =='o') && (boards[id_board].b[i][0]==boards[id_board].b[i][1] && boards[id_board].b[i][0]==boards[id_board].b[i][2])){
		}
	}
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
