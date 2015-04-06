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

	create_window();

	Plateform p, final;

	set_plateform(&p);
	set_plateform(&final);

	mix_plateform(&p);

	display_mixed_plateform(&p);
	MLV_actualise_window();

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

		if(event==MLV_MOUSE_BUTTON && mouse_button==MLV_BUTTON_LEFT && state == MLV_PRESSED) {
			/* If user clicks on a square */
			if(is_hover_square(x, y, &clicked_square_i, &clicked_square_y)) {
				/* If user clicks on black square to move another square */
				if(square_move_i != -1 && is_black_square(clicked_square_i, clicked_square_y, &p)) {
					/* Update positions in plateform structure */
					move_square(square_move_i, square_move_y, clicked_square_i, clicked_square_y, &p);
					/* PLace splitted picture at the new position */
					draw_moved_image(clicked_square_i, clicked_square_y, (p.bloc)[clicked_square_y][clicked_square_i].col, (p.bloc)[clicked_square_y][clicked_square_i].lig);
					/* Erase picture now she's on another place */
					erase_image(square_move_i, square_move_y);
					MLV_actualise_window();
					/*display_plateform(&p);*/
					square_move_i = -1;
					square_move_y = -1;
					if(compare_plateform(&p, &final)) {
						down = 1;
					}
				}
				/* If user clicks on a square which is allowed to move */
				else if(can_move(clicked_square_i, clicked_square_y, &p)) {
					square_move_i = clicked_square_i;
					square_move_y = clicked_square_y;
				}
			}
		}
		else if(event == MLV_MOUSE_MOTION || event == MLV_NONE) {
			if(hover == 0 && is_hover_square(x, y, &clicked_square_i, &clicked_square_y) && !is_black_square(clicked_square_i, clicked_square_y, &p)) {
				hover = 1;
				tmp_x = clicked_square_i;
				tmp_y = clicked_square_y;
				draw_hover_effect(clicked_square_i, clicked_square_y);
			}
			else if (hover == 1 && !is_hover_specific_square(x, y, tmp_x, tmp_y)) {
				hover = 2;
				draw_moved_image(tmp_x, tmp_y, (p.bloc)[tmp_y][tmp_x].col, (p.bloc)[tmp_y][tmp_x].lig);
				MLV_actualise_window();				
			}
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
		
	} while(!leave);

	return 0;
}
