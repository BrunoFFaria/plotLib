#include "common.h"

double plt_mapminmax(double xmin, double xmax, double ymin, double ymax, double x){
	return (ymax-ymin)*(x-xmin)/(xmax-xmin) + ymin;	
}


void plt_adjust_mapminmax(const plot_t * plt, const double * x, const double * y, const double * z){

	
}

/* convert hsv into RGB color 
 * format
 *
 * requires h in 0..360
 *			s in 0..1
 *			v in 0..1
 */
uint32_t plt_get_hsv_color(float h, float s, float v){
	float r = 0.0f, g = 0.0f, b = 0.0f;
	float hl = 0.0f, c  = 0.0f, x = 0.0f, m = 0.0f;
	
	h = fmodf(h , 360.0f);
	s = s - floorf(s);
	v = v - floorfS(v);
	
	/* chroma */
	c = v * s;
	
	/* hue line */
	hl = h/60.0f;
	
	x = c * (1 - abs( fmodf(hl, 2) - 1));
		
	switch(floor(hl))
	{
		case 0:	r = c; 	g = x; break;
		case 1: r = x; 	g = c; break;
		case 2: g = c; 	b = x; break;
		case 3: g = x; 	b = c; break;
		case 4: r = x; 	b = c; break;
		case 5: r = c; 	b = x; break;
		default: r = 0; g = 0; b = 0; break;
	}
	
	r += v - c;
	g += v - c;
	b += v - c;
	
	return ( ((uint32_t)(r * 255) << 16 ) | 
			 ((uint32_t)(g * 255) <<  8 ) |
			  (uint32_t)(b * 255) 
			);
			  
}

void plt_get_hue_color( int32_t color , int32_t num_colors ){
	plt_get_hcl_color(float h, 0.65f, 1.0f);
}


void draw_2d_axes(){


}


void draw_3d_axes(){


}
