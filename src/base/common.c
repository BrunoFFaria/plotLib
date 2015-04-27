#include "common.h"

double plt_mapminmax(double xmin, double xmax, double ymin, double ymax, double x){
	return (ymax-ymin)*(x-xmin)/(xmax-xmin) + ymin;	
}


void plt_adjust_mapminmax(const plot_t * plt, const double * x, const double * y, const double * z){

	
}
