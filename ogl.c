#include "ogl.h"

/* declare the global lib state here */
plotLib_t pL;

/* function responsible to keep the object updated on screen */
void plotlib_thread(void)
{
	int fake = 0;
	glutInit(&fake, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	while(1){
		/* query plotLib thread msg (should this thread exit?)*/
		
		/* verify that all redrawing threads have a window to draw to,
		 * if not create the windows...
		 */
		
	
		/* call glut to render and handle events */
		glutMainLoopUpdate();
	}	
}


/* each time a show command is issued 
 * we need to query if the object is in the queue 
 */
 void register_plt(plot_t * plt){
 
 }
 
 /* schedule plot to be drawn on screen */
 void queue_plt_redraw(plot_t * plot){
 
 }
 
 /* unregister plot from queue */
 void unregister_plt(plot_t * plt){
 
 }