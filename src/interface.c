#include <stdio.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "algo.h"
#include "interface.h"

/* Create program's window  */
void create_window() {
    MLV_create_window( "Le jeu du taquin", "Le jeu du taquin", SCREEN_SIZE_LIG, SCREEN_SIZE_COL);
    MLV_actualise_window(); /* Show the grid */
}

/* Draw one square of the picture */
void draw_split_image(int i, int y) {
	MLV_draw_partial_image(IMAGE, SQUARE_SIZE_LIG*i, SQUARE_SIZE_COL*y, SQUARE_SIZE_LIG, SQUARE_SIZE_COL, TOTAL_SQUARE_SIZE_LIG*i, TOTAL_SQUARE_SIZE_COL*y);
}

/* Draw one square of the picture */
void draw_moved_image(int position_i, int position_y, int grid_i, int grid_y) {
	MLV_draw_partial_image(IMAGE, SQUARE_SIZE_LIG*grid_y, SQUARE_SIZE_COL*grid_i, SQUARE_SIZE_LIG, SQUARE_SIZE_COL, TOTAL_SQUARE_SIZE_LIG*position_y, TOTAL_SQUARE_SIZE_COL*position_i);	
}

/* Put a black square */
void erase_image(int i, int y) {
	/*printf("erase = %d %d\n", i, y);*/
	MLV_draw_filled_rectangle(TOTAL_SQUARE_SIZE_LIG*y, TOTAL_SQUARE_SIZE_COL*i, SQUARE_SIZE_LIG, SQUARE_SIZE_COL, MLV_COLOR_BLACK);
}

/* Mouse is it on one of the square ? */
int is_hover_square(int mouse_x, int mouse_y, int* result_i, int* result_y) { 
	int i, y;
	for(i=0; i<NB_COL; i++) {
		for(y=0; y<NB_LIG; y++) {
			if(
				mouse_y>=TOTAL_SQUARE_SIZE_COL*i && 
				mouse_y<= TOTAL_SQUARE_SIZE_COL*i+SQUARE_SIZE_COL && 
				mouse_x>=TOTAL_SQUARE_SIZE_LIG*y &&
				mouse_x<=TOTAL_SQUARE_SIZE_LIG*y+SQUARE_SIZE_LIG
			) {
				*result_i = i;
				*result_y = y;
				return 1;
			}
		}
	}	
	return 0;
}

/*MLV_draw_image(igm, 0, 0 );*/

/*MLV_draw_partial_image()*/

/*MLV_draw_image_on_image*/
