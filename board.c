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
		
	}else if ((boards[id].b[2][0] != '-') && (boards[id].b[2][0] == boards[id].b[1][1]) && (boards[id].b[0][0] == boards[id].b[0][2])){
		boards[id].winner = boards[id].b[2][0];
	}
}

/*
	return the state of the board
	-1 : no winner, keep going
	0 : draw
	1 : player 1 win
	2 : player 2 win
*/
int state(board boards[]){
	int i,j,increment;
	for(i=0; i<BOARD_DIM*BOARD_DIM; i++){
		win_small_board(boards, i);
	}

	/*i=0;
	for(j=0; j<2; i++){
		if(j==0){increment=BOARD_DIM;}else{increment=1;}
		while((i<BOARD_DIM*BOARD_DIM && j==0) || ((i<3 && j==1))){
			if ((boards[i].winner =='x' || boards[i].winner =='o') && (boards[i].winner==boards[i+1].winner && boards[i].winner==boards[i+2].winner)){
				if(boards[i].winner=='x'){return 0;}else{return 1;} //TODO improve
			}
			i+=increment;
		}
	}*/
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
