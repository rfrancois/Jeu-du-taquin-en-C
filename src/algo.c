#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algo.h"
#include "interface.h"
#include <MLV/MLV_all.h>
#include <unistd.h>

/* Draw final picture */
void set_plateform(Plateform* P) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			((P->bloc))[i][y].lig = i;
			((P->bloc))[i][y].col = y;
			/*if(i!=NB_LIG-1 || y!=NB_COL-1) {
				draw_split_image(i, y);
			}*/
		}
	}
}

void display_mixed_plateform(Plateform* P) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			((P->bloc))[i][y].lig = i;
			((P->bloc))[i][y].col = y;
			/*if(((P->bloc))[y][i].col!=NB_LIG-1 || ((P->bloc))[y][i].lig!=NB_COL-1) {*/
				draw_moved_image(i, y, (P->bloc)[y][i].col, (P->bloc)[y][i].lig);
			/*}*/
		}
	}

	MLV_actualise_window();
}

void mix_plateform(Plateform* P) {
	srand(getpid());
	int black_i = NB_LIG-1, black_y = NB_COL-1, selected_i = black_i, selected_y = black_y, i, active = 0;

	for(i=0; i<50; i++) {
		if(rand()%2) {
			if(rand()%2) {
				if(black_i <= 0) {
					selected_i = black_i+1;
				}
				else {
					selected_i = black_i-1;
				}
			}
			else {
				if(black_i >= NB_COL-1) {
					selected_i = black_i-1;
				}
				else {
					selected_i = black_i+1;
				}
			}
		}
		else {
			if(rand()%2) {
				if(black_y <= 0) {
					selected_y = black_y+1;
				}
				else {
					selected_y = black_y-1;
				}

			}
			else {
				if(black_y>=NB_LIG-1) {
					selected_y = black_y-1;
				}
				else {
					selected_y = black_y+1;
				}
			}		
		}
		if(can_move(selected_i, selected_y, P)) {
			active++;
			/*printf("%d\n", i);*/
			move_square(selected_i, selected_y, black_i, black_y, P);
			black_i = selected_i;
			black_y = selected_y;
			printf("%d %d\n", black_y, black_i);
			/*if(active==1) {
				((P->bloc))[NB_COL-1][NB_LIG-1].lig = black_i;
				((P->bloc))[NB_COL-1][NB_LIG-1].col = black_y;
			}*/
		}
	}
	display_plateform(P);
}

/* Check if square can be moved */
int can_move(int selected_i, int selected_y, Plateform* P) {	
	if(
		(((P->bloc))[selected_y][selected_i-1].lig==NB_LIG-1 && ((P->bloc))[selected_y][selected_i-1].col==NB_COL-1) ||
		(((P->bloc))[selected_y][selected_i+1].lig==NB_LIG-1 && ((P->bloc))[selected_y][selected_i+1].col==NB_COL-1) ||
		(((P->bloc))[selected_y-1][selected_i].lig==NB_LIG-1 && ((P->bloc))[selected_y-1][selected_i].col==NB_COL-1) ||
		(((P->bloc))[selected_y+1][selected_i].lig==NB_LIG-1 && ((P->bloc))[selected_y+1][selected_i].col==NB_COL-1)
	) {
		return 1;
	}
	return 0;
}

/* Check if selected square is the black one */
int is_black_square(int selected_i, int selected_y, Plateform *P) {
	if(
		((P->bloc))[selected_y][selected_i].lig==NB_LIG-1 &&
		((P->bloc))[selected_y][selected_i].col==NB_COL-1
	) {
		return 1;
	}
	return 0;
}

/* Change positions of 2 squares */
void move_square(int selected_i, int selected_y, int black_i, int black_y, Plateform *P) {
	((P->bloc))[black_y][black_i].lig = ((P->bloc))[selected_y][selected_i].lig;
	((P->bloc))[black_y][black_i].col = ((P->bloc))[selected_y][selected_i].col;
	((P->bloc))[selected_y][selected_i].lig = NB_LIG-1;
	((P->bloc))[selected_y][selected_i].col = NB_COL-1;
	/*printf("selected = %d %d\n", selected_i, selected_y);
	printf("black = %d %d\n\n", black_i, black_y);*/
	/*draw_moved_image(black_i, black_y, ((P->bloc))[black_y][black_i].col, ((P->bloc))[black_y][black_i].lig);
	erase_image(selected_i, selected_y);
	MLV_actualise_window();*/
}


/* Print plateform (just for test) */
void display_plateform(Plateform* P) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			printf("%d %d = %d %d\n", i, y, ((P->bloc))[i][y].lig, ((P->bloc))[i][y].col);
		}
	}
	printf("-----------------------\n");
}