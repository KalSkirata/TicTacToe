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
}
