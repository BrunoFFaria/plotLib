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


}


static int32_t plt_2d_line_req(plot_t * plt, const double * x, const double * y, const double * z){
	/* two lines of data are required  */
	C_CHECK_CONDITION( x == NULL, API_DATA_NOT_VALID);
	C_CHECK_CONDITION( y == NULL, API_DATA_NOT_VALID);
	
	return 0;
error:
	return -1;
}


static int32_t plt_2d_line_draw(void *, const double * x, const double * y, const double * z, int32_t layer, int32_t num_layers){


}

static void plt_2d_line_layer(int32_t property, int32_t value){


}


static void plt_2d_line_free_aux(void * ptr){



}
