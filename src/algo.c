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
			((P->bloc))[i][y].col = i;
			if(i!=NB_COL-1 || y!=NB_LIG-1) {
				draw_split_image(i, y);
			}
		}
	}
	MLV_actualise_window();
}