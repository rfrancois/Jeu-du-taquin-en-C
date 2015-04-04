#ifndef __ALGO__
#define __ALGO__

#define NB_COL 4
#define NB_LIG 4

typedef struct square {
	int lig;
	int col;
} Square;

typedef struct plateform
{
	Square bloc[NB_COL][NB_LIG];
} Plateform;

void set_plateform(Plateform* P);
int can_move(int selected_i, int selected_y, Plateform* P);
 
#endif