#include "draw.h"

void plt_idle(void)
{
	static double last_t = 0;
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
 * Core draw function: call  
 * every plot type draw method
 */
void plt_draw(void)
{
	int32_t i = 0, j = 0;
	int32_t num_axis = 0, w = 0, h = 0;
	int32_t vp_xstart = 0, vp_xend = 0, vp_ystart = 0, vp_yend = 0; 
	int32_t num_plots_h = 0, num_plots_w = 0, num_plot = 0;
	
	plt_layer_t * layer = NULL;
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
		 glutSetWindow(pL.window_handle[i]);
		
		/*
		 * subplotting enabled?
		 */
		if(pL.plts[i]->subplot_state){
			/*
			 * grab window dimensions
			 */
			w = pL.window_w[i];
			h = pL.window_h[i];
			num_plots_w = pL.plts[i]->subplot_dim[0];
			num_plots_h = pL.plts[i]->subplot_dim[1];
			num_plot = pL.plts[i]->subplot_num;
			vp_xstart = (num_plot%num_plots_w)*w/num_plots_w; 
			vp_xend = vp_xstart + w/num_plots_w - 1;
			vp_ystart = num_plot/w * h/num_plots_h;
			vp_yend = vp_ystart + h/num_plots_h;
			
			/* set viewport */
			glViewport(vp_xstart, vp_ystart, vp_xend, vp_yend );
		}
		
		/*
		 * call draw module on each layer
		 */
		 for(j = 0; j < pL.plts[i]->num_layers;j++){
			layer = pL.plts[i]->layers[j];
			num_axis = plt_draw_func_ptr[pL.plts[i]->plt_type]
						(layer->aux_layer_data, 
						layer->x, layer->y, layer->z,
						j, 
						pL.plts[i]->num_layers);
		
		 }
		/*
		 * draw axes
		 */
		switch(num_axis){
			case 2:
				draw_2d_axis();
				break;
			case 3:
				draw_3d_axis();
				break;
			default:
				break;
		}
	}
}
/*
 * Reshape callback
 */
void plt_reshape_window(int width, int height){
	int32_t i = 0, h = 0;
	int32_t window = glutGetWindow();
	/* 
	 * before calling plt_reshape glut 
	 * sets the current window to the 
	 * reshaped window, so use it to 
	 * track which window to modify
	 */
	for(i = 0; i < pL.num_plts; i++)
		if(pL.window_handle[i] == window){
			/* we have the plot or 
			 * one of the subplots 
			 */
			pL.window_w[i] = width;
			pL.window_h[i] = height;
			
			/* fix subplot view port (do it on redraw) */
		}
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -h*2, h*2, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -60.0);
}

