#include <stdio.h>
#include <GL/glut.h>
typedef struct data{

	double *x;
	double *y;
	double xmax;
	double xmin;
	double ymax;
	double ymin;
	int size; //size of x, y arrays
	float color[3];
		
}data_t;

typedef struct plot{
	
	data_t* graphs;
	
}plot_t;

double mapminmax1(double xmin, double xmax, double ymin, double ymax, double x);
void plot(data_t *data);
void exampleData(data_t* data, int type);


