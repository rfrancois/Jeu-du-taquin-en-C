/***************************************************************
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    TP 11 d'algorithmique
    Romain FRANCOIS IR 1
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "algo.h"
#include <MLV/MLV_all.h>

/* Global variable to know when to leave the program */
int leave = 0;
 
/* Update leave variable to exit from the program */
void exit_function(void* data){
    int* leave = (int*)  data;
    *leave = 1;
}

int main(int argc, char* argv[]) {

	/* Initialize the game */

	create_window();

	Plateform p, final;

	set_plateform(&p);
	set_plateform(&final);

	mix_plateform(&p);

	display_mixed_plateform(&p);
	MLV_actualise_window();

	/*display_plateform(&p);*/

	int x, y, clicked_square_i, clicked_square_y, square_move_i = -1, square_move_y = -1, down = 0, hover = 0, tmp_x, tmp_y;
	MLV_Event event;
	MLV_Button_state state;
	MLV_Mouse_button mouse_button;

/***********************************************************************************************************************
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
                                                     PLAYING SCREEN
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
***********************************************************************************************************************/

	do {

		/* New event */
		event = MLV_get_event(
		NULL, NULL, NULL,
		NULL, NULL,
		&x, &y,&mouse_button,&state         
		);
		
		/* If user clicks on a square which is allowed to move */
		if(event==MLV_MOUSE_BUTTON && mouse_button==MLV_BUTTON_LEFT && state == MLV_PRESSED && is_hover_square(x, y, &clicked_square_i, &clicked_square_y) && can_move(clicked_square_i, clicked_square_y, &p) && !is_black_square(clicked_square_i, clicked_square_y, &p)) {			
			/* Set black square's position */
			find_black_square(&p, &square_move_i, &square_move_y);
			/* Update positions in plateform structure */
			move_square(clicked_square_i, clicked_square_y, square_move_i, square_move_y, &p);
			/*display_plateform(&p);*/
			/* Place splitted picture at the new position */
			draw_moved_image(square_move_i, square_move_y, (p.bloc)[square_move_y][square_move_i].col, (p.bloc)[square_move_y][square_move_i].lig);
			/* Erase picture now it's on another place */
			erase_image(clicked_square_i, clicked_square_y);
			MLV_actualise_window();
			if(compare_plateform(&p, &final)) {
				down = 1;
			}
		}
		/* If mouse's user passes on a square, do a hover effect */
		else if(event == MLV_MOUSE_MOTION || event == MLV_NONE) {
			/* If we were not on a square before */
			if(hover == 0 && is_hover_square(x, y, &clicked_square_i, &clicked_square_y) && !is_black_square(clicked_square_i, clicked_square_y, &p)) {
				hover = 1;
				tmp_x = clicked_square_i;
				tmp_y = clicked_square_y;
				draw_hover_effect(clicked_square_i, clicked_square_y);
			}
			/* If mouse leaved a square */
			else if (hover == 1 && !is_hover_specific_square(x, y, tmp_x, tmp_y)) {
				hover = 2;
				/* Don't draw a picture if it's black square */
				if(!is_black_square(tmp_x, tmp_y, &p)) {
					draw_moved_image(tmp_x, tmp_y, (p.bloc)[tmp_y][tmp_x].col, (p.bloc)[tmp_y][tmp_x].lig);
					MLV_actualise_window();
				}				
			}
			/* Waiting for the mouse after we leaved a square */
			else if(hover == 2) {
				hover = 0;
			}
		}

	} while(!leave && !down);

/***********************************************************************************************************************
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
                                                     WIN SCREEN
 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
***********************************************************************************************************************/

 	draw_win_screen();

	do {
		/* Do nothing until user leaves the game */
	} while(!leave);

	MLV_free_window();

	return 0;
}
