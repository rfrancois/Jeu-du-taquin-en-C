#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algo.h"
#include "interface.h"
#include <unistd.h>

/* Draw final picture */
void set_plateform(Plateform* P) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			((P->bloc))[i][y].lig = i;
			((P->bloc))[i][y].col = y;
		}
	}
}

/* Display mixed plateform */
void display_mixed_plateform(Plateform* P) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			if(((P->bloc))[y][i].col!=NB_LIG-1 || ((P->bloc))[y][i].lig!=NB_COL-1) {
				draw_moved_image(i, y, (P->bloc)[y][i].col, (P->bloc)[y][i].lig);
			}
		}
	}
}

/* Take a sorted plateform structure and mix it */
void mix_plateform(Plateform* P) {
	srand(getpid());
	int black_i = NB_LIG-1, black_y = NB_COL-1, selected_i = black_i, selected_y = black_y, i, active = 0;

	for(i=0; i<20; i++) {
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
			move_square(selected_i, selected_y, black_i, black_y, P);
			black_i = selected_i;
			black_y = selected_y;
		}
	}
	/*display_plateform(P);*/
}

/* Return 1 if 2 plateforms are equals */
int compare_plateform(Plateform* p1, Plateform* p2) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			if(
				(p1->bloc)[i][y].lig != (p2->bloc)[i][y].lig ||
				(p1->bloc)[i][y].col != (p2->bloc)[i][y].col
			) {
				return 0;
			}
		}
	}
	return 1;
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