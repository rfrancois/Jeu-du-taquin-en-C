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

	Plateform p;

	set_plateform(&p);

	mix_plateform(&p);

	display_mixed_plateform(&p);

	int x, y, clicked_square_i, clicked_square_y, square_move_i = -1, square_move_y = -1;
	MLV_Event event;
	MLV_Button_state state;
	MLV_Mouse_button mouse_button;

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
				}
				/* If user clicks on a square which is allowed to move */
				else if(can_move(clicked_square_i, clicked_square_y, &p)) {
					square_move_i = clicked_square_i;
					square_move_y = clicked_square_y;
				}
			}
		}

	} while(!leave);

	return 0;
}
