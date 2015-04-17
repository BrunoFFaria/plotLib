#include "draw.h"
#include "ogl.h"

// show current plot
void plt_show(plot_t * plt){
	static int thread_number = 0;
	/* verify if object thread is already active */
	if(plt->thread_state){
		plt->thread_number = thread_number;
		
		#ifdef WIN32
			
		#elif __linux__
			 // create all threads one by one
			result_code = pthread_create(plt->thread_number, NULL, display_plot, NULL);
		#endif
		thread_state = true;
		thread_number++;
	}else{
		
	
	}
	
	/* thread is active */
	
	/* now show data on screen */

}

// add another layer to the current plot
void plt_add_layer(){
	/* allocate memory for the layer */
	
	/* increase number of layers */

}

