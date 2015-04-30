#include "draw.h"

static void plt_idle(void)
{
	const double now_t = ftime();
	const double delta_t = now_t - last_t;
	
  	if(delta_t > pL.wait_time )
  	{
		/* update everything on screen */		
		last_t = now_t;
		glutPostRedisplay();
	}
}


/* 
 * Core draw function: call the 
 * every plot type draw method
 */
static void plt_draw(void)
{
	int32_t i = 0;
	/* for each plot type call 
	 * the respective drawing function
	 */ 
	for(i = 0; i < pL.num_plts; i++){
		/*		
		 * do some checks before
		 * calling the function
		 */ 
		if(pL.plts[i]==NULL)
			continue;
		if(pL.plts[i]->plt_type <= 0 || 
			pL.plts[i]->plt_type >= PL_NUM_PLOT_TYPES)
			continue;
		
		if(plt_draw_func_ptr[pL.plts[i]->plt_type] == NULL)
			continue;
		
		/*
		 * change to the plt window
		 */
		 if(glutSetWindow(pL.window_handle[i])==0)
			continue;
		
		/*
		 * subplotting enabled?
		 */
		if(pL.plts[i]->subplot_state){
			
			vp_xstart = 
			vp_xend =
			vp_ystart =
			vp_yend = 
			
			/* set viewport */
			glViewport( )
		
		}
		
		/*
		 * call draw module
		 */
		plt_draw_func_ptr[pL.plts[i]->plt_type]();
		
		/*
		 * draw axes
		 */
	}
}
/*
 * Reshape callback
 */
static void plt_reshape(int width, int height){
	/* 
	 * before calling plt_reshape glut 
	 * sets the current window to the 
	 * reshaped window, so use it to 
	 * track which window to modify
	 */

	 
}

static void plt_redraw(void){


}