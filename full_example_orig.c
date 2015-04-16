#include <stdio.h>
#define _BSD_SOURCE 
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "zpr.h"
#define RHO 28
#define BETA (8/3)
#define SIGMA 10.0f
#define dt 0.01f
#define MAX_STEPS 10000000

#define FRAMERATE				60.0f	      
#define TIMEWAIT			1/FRAMERATE
#define WIDTH					800
#define	HEIGHT					800
#define GLERROR                                                    \
    {                                                              \
        GLenum code = glGetError();                                \
        while (code!=GL_NO_ERROR)                                  \
        {                                                          \
            printf("%s\n",(char *) gluErrorString(code));          \
                code = glGetError();                               \
        }                                                          \
    }

/* global lorenz simulation step : starts at 1 */
int global_sim_step = 1;
/* global variables */
double * x = NULL, * y = NULL, * z = NULL;

void comp_lorenz();
void display(void);
void pick(GLint name);
void drawAxes(void);
static void idle(void);
static double ftime(void);

int main(int argc, char * argv [])
{
   
   int i = 0;
   x = (double *) malloc( 3 * MAX_STEPS * sizeof(double));
   GLfloat h = (GLfloat) HEIGHT / (GLfloat) WIDTH;
   if(x == NULL){
   	printf("could not allocate memory\n");
       exit(-1);
   }
   printf("starting lorenz attractor simulation");
   y = &x[MAX_STEPS]; z = &y[MAX_STEPS]; 
   x[0] = 10; y[0] = 10; z[0]=10;
  
  
   /* Initialise GLUT and create a window */
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   	glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("GLT Mouse Zoom-Pan-Rotate");

	/* Configure GLUT callback functions */
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	
	glLineWidth(1.4);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, (GLint) WIDTH, (GLint) HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	
	glRotatef(35.0, 1.0, 0.0, 0.0);
	glRotatef(55.0, 0.0, 1.0, 0.0);
	glRotatef(10.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 0.0);
	
	
   	/* Configure ZPR module */
   	zprInit();
   	zprSelectionFunc(drawAxes);     /* Selection mode draw function */
   	zprPickFunc(pick);              /* Pick event client callback   */
 	GLERROR;
	
   	/* Enter GLUT event loop */
   	glutMainLoop();
   	
   /* free memory */
   free(x);
   return 0;
}


static double ftime(void) {
    struct timeval t;
    gettimeofday(&t, NULL);

    return 1.0*t.tv_sec + 1e-6*t.tv_usec;
}

double last_T;

static void idle(void)
{
	const double now_T = ftime();
	const double delta_T = now_T - last_T;
	
  	if(delta_T > TIMEWAIT )
  	{
		comp_lorenz();
		last_T = now_T;
		glutPostRedisplay();
	}
}

void comp_lorenz()
{
	if(global_sim_step < MAX_STEPS)
   	{
		x[global_sim_step] = x[global_sim_step-1] + dt * ( SIGMA * ( y[global_sim_step-1] - x[global_sim_step-1]) );
	   	y[global_sim_step] = y[global_sim_step-1] + dt * ( x[global_sim_step-1] * ( RHO - z[global_sim_step-1]) - y[global_sim_step - 1]);
   		z[global_sim_step] = z[global_sim_step-1] + dt * ( x[global_sim_step-1] * y[global_sim_step-1] -  BETA * z[global_sim_step - 1] );
  	 	global_sim_step++;
  	 }
  	 
}

double mapminmax(double xmin, double xmax, double ymin, double ymax, double x){
	return (ymax-ymin)*(x-xmin)/(xmax-xmin) + ymin;
	
}

/* Draw axes */
void drawAxes(void)
{
	int i = 0;
	double xmin = 0, xmax = 0, ymin = 0, ymax = 0, zmin = 0, zmax = 0;
	GLUquadricObj *Arrow_x = gluNewQuadric();
    GLUquadricObj *Arrow_y = gluNewQuadric();
    GLUquadricObj *Arrow_z = gluNewQuadric();
    
    /* Name-stack manipulation for the purpose of
       selection hit processing when mouse button
       is pressed.  Names are ignored in normal
       OpenGL rendering mode.                    */
	/* Render animation */
	glPushMatrix();
	
	glBegin(GL_LINE_STRIP);
	
	/* get normalization values */
	for(i = 0; i < global_sim_step; i++){
		if(x[i] < xmin){	xmin = x[i];	}
		if(x[i] > xmax){	xmax = x[i];	}	
		if(y[i] < ymin){	ymin = y[i];	}
		if(y[i] > ymax){	ymax = y[i];	}	
		if(z[i] < zmin){	zmin = z[i];	}
		if(z[i] > zmax){	zmax = z[i];	}	
	}
	
	if(global_sim_step < 100){
		glColor3f(0.4,0.6,0.1); 
		for(i = 0; i < global_sim_step; i++){
			glVertex3f( mapminmax(xmin,xmax,0,1,x[i]),
						mapminmax(ymin,ymax,0,1,y[i]),
						mapminmax(zmin,zmax,0,1,z[i]));
		}
	}else{
		glColor3f(0.0,0.4,0.1); 
		for(i = 0; i < global_sim_step-100; i++){
			glVertex3f( mapminmax(xmin,xmax,0,1,x[i]),
						mapminmax(ymin,ymax,0,1,y[i]),
						mapminmax(zmin,zmax,0,1,z[i]));
		}

		glColor3f(0.4,0.6,0.1); 
    	
		for(i = global_sim_step-100; i < global_sim_step; i++){
			glVertex3f( mapminmax(xmin,xmax,0,1,x[i]),
						mapminmax(ymin,ymax,0,1,y[i]),
						mapminmax(zmin,zmax,0,1,z[i]));
		}
	}
	glEnd();
	
	#define axis(x,y,z)		\
		glVertex3f(0,0,0);	\
		glVertex3f(x,y,z);
					
	// draw axes
	glBegin(GL_LINES);
	glColor3f(0.3,0.3,0.3); 
	axis(1,0,0);
	axis(0,1,0);
	axis(0,0,1)
	glEnd();
	
	#define arrow(x,y,z,rot,seg_x,seg_y,seg_z)							\
						glPushMatrix();									\
						glColor3f(0.4,0.4,0.4);							\
						glTranslatef(x,y,z);							\
						glRotatef(rot,seg_x,seg_y,seg_z); 				\
						gluCylinder(Arrow_x, 0.02, 0, 0.03, 10, 20);	\
						glPopMatrix();			
	arrow(1,0,0, 90, 0,1,0);
	arrow(0,1,0,-90, 1,0,0);
	arrow(0,0,1,  0, 0,0,0);	
		
	// draw labels
	glPushMatrix();
	glColor3f(0.8,0.8,0.8); 
	glTranslatef(1.05,0,-0.05);
	glRotatef(90,0,1,0);
	glScalef(0.0008,0.0008,0.0008);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'x');
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.8,0.8,0.8); 
	glTranslatef(0,1.05,-0.05);
	glRotatef(-90,0,1,0);
	glRotatef(-90,1,0,0);
	glScalef(0.0008,0.0008,0.0008);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'y');
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.8,0.8,0.8); 
	glTranslatef(-0.08,0,1.05);
	glScalef(0.0008,0.0008,0.0008);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'z');
	glPopMatrix();
	
	glPopMatrix();
}

/* Callback function for drawing */
void display(void)
{
   GLERROR;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   drawAxes();
   glutSwapBuffers();
   glFlush();
   GLERROR;
}

/* Callback function for pick-event handling from ZPR */
void pick(GLint name)
{
   fflush(stdout);
}


