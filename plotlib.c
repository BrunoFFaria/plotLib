#include <plotlib.h>
#include <math.h>
double mapminmax1(double xmin, double xmax, double ymin, double ymax, double x){
	return (ymax-ymin)*(x-xmin)/(xmax-xmin) + ymin;
	
}

void plot(data_t *data){
	
	int i=0;
	glColor3f(data->color[0],data->color[1],data->color[2]);

	for(i=0;i<data->size;i++){

		if(i<data->size-1){
			glBegin(GL_LINES);
			
				glVertex2f(mapminmax1(data->xmin,data->xmax,0,1,data->x[i]),mapminmax1(data->ymin,data->ymax,0,1,data->y[i]));
				glVertex2f(mapminmax1(data->xmin,data->xmax,0,1,data->x[i+1]),mapminmax1(data->ymin,data->ymax,0,1,data->y[i+1]));

			glEnd();
		}
		
	}
	
}

void exampleData(data_t* data, int type){
	int i=0;
	data->size=100;
	data->x=(double*)malloc(data->size*sizeof(double));
	data->y=(double*)malloc(data->size*sizeof(double));
	if(data->x==NULL || data->y==NULL){
		
		printf("Alloc failed.\n");
		exit(1);
		
	}
	else{
		
		printf("Alloc success.\n");
		
	}
	data->color[0]=1.0;
	data->color[1]=1.0;
	data->color[2]=0.0;
	
	data->xmin=1e20;
	data->xmax=-1e20;
	data->ymin=1e20;
	data->ymax=-1e20;
	if(type==1){
		
		for(i=0;i<data->size;i++){
		data->x[i]=i/10.0;
		data->y[i]=3.0*cos(data->x[i]);
		
		}
		
	}
	
	else if(type==2){
		data->color[0]=1.0;
		data->color[1]=1.0;
		data->color[2]=1.0;
		for(i=0;i<data->size;i++){
		data->x[i]=i/10.0;
		data->y[i]=(data->x[i])*(data->x[i]);
		
		}
		
	}
	
	else if(type==3){
		data->color[0]=0.0;
		data->color[1]=1.0;
		data->color[2]=0.0;
		for(i=0;i<data->size;i++){
		data->x[i]=cos(2*M_PI*(i/(1.0*data->size)));
		data->y[i]=sin(2*M_PI*(i/(1.0*data->size)));;
		
		}
		
	}
	for(i=0;i<data->size;i++){
		
		if(data->x[i] < data->xmin){	data->xmin = data->x[i];	}
		if(data->x[i] > data->xmax){	data->xmax = data->x[i];	}	
		if(data->y[i] < data->ymin){	data->ymin = data->y[i];	}
		if(data->y[i] > data->ymax){	data->ymax = data->y[i];	}
		
	}
}
