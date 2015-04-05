#ifndef __ALGO__
#define __ALGO__

#define NB_COL 4
#define NB_LIG 5

typedef struct square {
	int lig;
	int col;
} Square;

typedef struct plateform
{
	Square bloc[NB_COL][NB_LIG];
} Plateform;

void set_plateform(Plateform* P);
void mix_plateform(Plateform* P);
int can_move(int selected_i, int selected_y, Plateform* P);
int is_black_square(int selected_i, int selected_y, Plateform *p);
void move_square(int selected_i, int selected_y, int black_i, int black_y, Plateform *P);
void display_plateform(Plateform* P);
 
#endif