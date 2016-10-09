#include <stdio.h>

struct board{
	char b[3][3];
};

typedef struct board board;

board boards[9];

// fill board with "-" character
void init_board(){
	int x=0, y=0, z=0;

	for(x=0; x<9; x++){
		for(y=0; y<3; y++){
			for(z=0; z<3; z++){
				boards[x].b[y][z]='-';
			}
		}
	}
}

void display_board(){
	int i, cpt=0;
	while(cpt<9){
		for(i=0; i<3; i++){
			printf("%c%c%c %c%c%c %c%c%c \n", boards[cpt].b[i][0], boards[cpt].b[i][1], boards[cpt].b[i][2],
												boards[cpt+1].b[i][0], boards[cpt+1].b[i][1], boards[cpt+1].b[i][2],
										 		boards[cpt+2].b[i][0], boards[cpt+2].b[i][1], boards[cpt+2].b[i][2]);
		}
		cpt+=3;
		printf("\n");
	}
}

int main(){
	init_board();
	display_board();
	return 0;
}
