#include "ogl.h"

/* the executing thread should use its value to pull the object from the objects list and draw that object */
/* updating the object list should be done using mutexes... */

plt_t ** drawing_objects;

/* function responsible to keep the object updated on screen */
int draw_object(void)
{
	


	
	while(1){
		/* call glut to render handle some events */
		glutMainLoop();
		
		/* should we redraw the current window ?*/
		
		
	}
	
}
