#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algo.h"
#include "interface.h"
#include <unistd.h>

/* Set plateform with final positions */
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
			/* If we're not on black square, draw current square */
			if(((P->bloc))[y][i].col!=NB_LIG-1 || ((P->bloc))[y][i].lig!=NB_COL-1) {
				draw_moved_image(i, y, (P->bloc)[y][i].col, (P->bloc)[y][i].lig);
			}
		}
	}
}

/* Take a sorted plateform structure and mix it */
void mix_plateform(Plateform* P) {

	int black_i = NB_LIG-1; /* black square - line index */
    int black_y = NB_COL-1; /* black square - column index */ 
	int selected_i = black_i; /* square to move - line index */
	int selected_y = black_y; /* square to move - column index */
	int i; /* Loop counter */

	srand(getpid());

	/* Mix movements loop */
	for(i=0; i<120; i++) {
		/* Move to left/right or top/bottom */
		if(rand()%2) {
			/* Move to the left or to the right */
			if(rand()%2) {
				/* Check if we are on a border */
				if(black_i <= 0) {
					selected_i = black_i+1;
				}
				else {
					selected_i = black_i-1;
				}
			}
			else {
				/* Check if we are on a border */
				if(black_i >= NB_COL-1) {
					selected_i = black_i-1;
				}
				else {
					selected_i = black_i+1;
				}
			}
		}
		else {
			/* Move to the top or to the bottom */
			if(rand()%2) {
				/* Check if we are on a border */
				if(black_y <= 0) {
					selected_y = black_y+1;
				}
				else {
					selected_y = black_y-1;
				}

			}
			else {
				/* Check if we are on a border */
				if(black_y>=NB_LIG-1) {
					selected_y = black_y-1;
				}
				else {
					selected_y = black_y+1;
				}
			}		
		}
		/* Check if moving of selected square is legal */
		if(can_move(selected_i, selected_y, P)) {
			move_square(selected_i, selected_y, black_i, black_y, P);
			/* Set selected square as black square */
			black_i = selected_i;
			black_y = selected_y;
		}
	}
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
		(((P->bloc))[selected_y][selected_i+1].lig==NB_LIG-1 && ((P->bloc))[selected_y][selected_i+1].col==NB_COL-1 && selected_i+1 < NB_LIG) ||
		(((P->bloc))[selected_y-1][selected_i].lig==NB_LIG-1 && ((P->bloc))[selected_y-1][selected_i].col==NB_COL-1) ||
		(((P->bloc))[selected_y+1][selected_i].lig==NB_LIG-1 && ((P->bloc))[selected_y+1][selected_i].col==NB_COL-1) ||
		(((P->bloc))[selected_y][selected_i-1].lig==NB_LIG-1 && ((P->bloc))[selected_y][selected_i-1].col==NB_COL-1 && selected_i-1 >= 0)
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

/* Find out black square position */
void find_black_square(Plateform *P, int* selected_i, int* selected_y) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			/* If black square is found, set position in given pointers */
			if((P->bloc)[i][y].lig == NB_LIG-1 && (P->bloc)[i][y].col == NB_COL-1) {
				*selected_i = y;
				*selected_y = i;
				return ;
			}
		}
	}	
}

/* Change positions of 2 squares */
void move_square(int selected_i, int selected_y, int black_i, int black_y, Plateform *P) {
	/* Permutation */
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
