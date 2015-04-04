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


	int x, y, clicked_square_i, clicked_square_y;
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
			if(is_hover_square(x, y, &clicked_square_i, &clicked_square_y)) {
				printf("%d %d\n", clicked_square_i, clicked_square_y);
			}
		}

	} while(!leave);

	return 0;
}
