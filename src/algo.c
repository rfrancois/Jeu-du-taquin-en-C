#include "algo.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

/* Draw final picture */
void set_plateform(Plateform* P) {
	int i, y;
	for(i=0; i<NB_LIG; i++) {
		for(y=0; y<NB_COL; y++) {
			((P->bloc))[i][y].lig = i;
			((P->bloc))[i][y].col = y;
			if(i!=NB_LIG-1 || y!=NB_COL-1) {
				draw_split_image(i, y);
			}
		}
	}
	draw_split_image(3, 4);
	MLV_actualise_window();
}

/* CHeck if square can be moved */
int can_move(int selected_i, int selected_y, Plateform* P) {

	/*((P->bloc))[i][y].lig = i;*/
	return 0;
}