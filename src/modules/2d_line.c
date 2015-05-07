#include "2d_line.h"
/* 
 * specify the object 
 *
 */
static void * plt_2d_line_aux(int32_t layer_num){
	/*
	 * Allocate space on the layer for the layer properties
	 *
	 */
	return mem_alloc( sizeof(prop_2d_layer_t), true);	
}


static int32_t plt_2d_line_req(plot_t * plt, const double * x, const double * y, const double * z){
	/* two lines of data are required  */
	C_CHECK_CONDITION( x == NULL, API_DATA_NOT_VALID);
	C_CHECK_CONDITION( y == NULL, API_DATA_NOT_VALID);
	
	return 0;
error:
	return -1;
}


static int32_t plt_2d_line_draw(void * ptr, const double * x, const double * y, const double * z, int32_t layer, int32_t num_layers){
	prop_2d_layer_t * prop = NULL;
	
	/* validate memory area */
	if(ptr == NULL){ goto default_action; }
	
	prop = ptr;
	/* get color
	 */
	
	
	/* time to draw the data 
	 */
	
	
	/* */
default_action:
	return 2;
}

static void plt_2d_line_layer(int32_t property, int32_t value){


}


static void plt_2d_line_free_aux(void * ptr){
	mem_free(ptr);
}
