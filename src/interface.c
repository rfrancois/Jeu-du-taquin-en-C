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

void draw_hover_effect(int i, int y) {
	MLV_draw_filled_rectangle(TOTAL_SQUARE_SIZE_LIG*y, TOTAL_SQUARE_SIZE_COL*i, SQUARE_SIZE_LIG, SQUARE_SIZE_COL, MLV_convert_rgba_to_color(0, 0, 0, 50));	
	MLV_actualise_window();
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

int is_hover_specific_square(int mouse_x, int mouse_y, int i, int y) { 
	if(
		mouse_y>=TOTAL_SQUARE_SIZE_COL*i && 
		mouse_y<= TOTAL_SQUARE_SIZE_COL*i+SQUARE_SIZE_COL && 
		mouse_x>=TOTAL_SQUARE_SIZE_LIG*y &&
		mouse_x<=TOTAL_SQUARE_SIZE_LIG*y+SQUARE_SIZE_LIG
	) {
		return 1;
	}
	return 0;
}

void draw_win_screen() {
	/* Calculate center */
	int width, height;
	MLV_get_image_size(IMAGE, &width, &height);
	width = SCREEN_SIZE_LIG/2-width/2;
	height = SCREEN_SIZE_COL/2-height/2;
	/* Draw picture */
	MLV_clear_window( MLV_COLOR_BLACK );
	MLV_draw_image(IMAGE, width, height);
	/* Draw text */
	char* libel = "You won !";
	MLV_draw_text(20, 20, libel, MLV_COLOR_BLACK);
	MLV_actualise_window();
}

/*MLV_draw_image(igm, 0, 0 );*/

/*MLV_draw_partial_image()*/

/*MLV_draw_image_on_image*/
