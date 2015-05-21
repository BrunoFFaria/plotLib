#include "2d_line.h"
/* 
 * specify the object 
 *
 */
void * plt_2d_line_aux(int32_t layer_num){
	/*
	 * Allocate space on the layer for the layer properties
	 *
	 */
	return mem_alloc( sizeof(prop_2d_layer_t), true);	
}


int32_t plt_2d_line_req(plot_t * plt, const double * x, const double * y, const double * z){
	/* two lines of data are required  */
	C_CHECK_CONDITION( x == NULL, API_DATA_NOT_VALID);
	C_CHECK_CONDITION( y == NULL, API_DATA_NOT_VALID);
	
	return 0;
error:
	return -1;
}


int32_t plt_2d_line_draw(void * ptr, const double * x, const double * y, const double * z, int32_t layer, int32_t num_layers){
	prop_2d_layer_t * prop = NULL;
	int32_t color = 0;
	
	/* validate memory area */
	if(ptr == NULL){ goto default_action; }
	
	prop = ptr;
	
	/* get the color to be used
	 */
	 if(prop->color == NONE && prop->user_color == NONE){
		/* 
		 * user must have specified a given color, or not...
		 */
		color = get_colormap_color( prop->color, layer, num_layers);
		
	 }else{
		 
		
	 }
	
	
	/* time to draw the data 
	 */
	
	/* only push data points that are in range */
	
	/* */
default_action:
	return 2;
}

void plt_2d_line_layer(int32_t property, int32_t value){


}


void plt_2d_line_free_aux(void * ptr){
	mem_free(ptr);
}
