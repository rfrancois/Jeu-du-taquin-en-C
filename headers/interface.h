#ifndef __INTERFACE__
#define __INTERFACE__

/* Screen dimension */
#define GLOBAL_SIZE 512
#define PADDING_SIZE 10
/* Columns */
#define SCREEN_SIZE_COL (GLOBAL_SIZE+PADDING_SIZE*(NB_COL-1))
#define SQUARE_SIZE_COL (GLOBAL_SIZE/NB_COL)
#define TOTAL_SQUARE_SIZE_COL (SQUARE_SIZE_COL+PADDING_SIZE)
/* Lines */
#define SCREEN_SIZE_LIG (GLOBAL_SIZE+PADDING_SIZE*(NB_LIG-1))
#define SQUARE_SIZE_LIG (GLOBAL_SIZE/NB_LIG)
#define TOTAL_SQUARE_SIZE_LIG (SQUARE_SIZE_LIG+PADDING_SIZE)
/* Image */
#define IMAGE (MLV_load_image("igm.gif"))

void create_window();
void draw_split_image(int i, int y);
void draw_moved_image(int position_i, int position_y, int grid_i, int grid_y);
void erase_image(int i, int y);
int is_hover_square(int mouse_x, int mouse_y, int* result_i, int* result_y);


#endif
