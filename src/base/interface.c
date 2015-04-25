#include "interface.h"

/* 
 * This file makes the interface between the plotLib thread 
 * and the aplication using it...
 *
 */


/* declare the global lib state here */
plotLib_t pL;

/* function responsible to keep the object updated on screen */
void plotlib_thread(void)
{
	int fake = 0;
	glutInit(&fake, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	/* register drawing functions */
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	
	while(1){
		/* query plotLib thread msg (should this thread exit?)*/
		if(pL.thread_msg == thread_msg_exit)
			break;
			
		/* verify that the window for where 
		 * every plot must be drawn is open
		 * if not create the window...
		 */
		check_plts_windows();
	
		/* call glut to render and handle events */
		glutMainLoopUpdate();
	}
	
	/* shutdown glut */
	
}

/* show current plots */
/*
 * function needs variable number of arguments
 *
 */
void plt_show(const plot_t * plt){

	/* register thread in the queue */
	C_SAFE_CALL( register_plt(plt) );
	
	/* thread may be in the queue,
	 * but will not be updated 
	 * unless we mark it to redraw
	 */
	C_SAFE_CALL( queue_plt_redraw(plt) );
	
	SET_API_ERROR(API_SUCCESS);
	return;
error:

	SET_API_ERROR();
}

/* add another layer to the current plot
 *
 */
void plt_add_layer(plot_t * plt, const double * x, const double * y, const double * z, size_t size){
	plt_layer_t * layer = NULL;
	
	C_CHECK_CONDITION( plt == NULL, API_BAD_INPUT);
	C_CHECK_CONDITION( size <= 0, API_BAD_INPUT);
	
	/* 
	 * the following are done based  
	 * on function requirements
	 */
	C_SAFE_CALL( plt_validate_requirements(plt, x, y, z ) );
	
	/* allocate memory for the layer */
	C_SAFE_CALL(layer = mem_alloc( sizeof(plt_layer_t), true) );
	
	/* allocate memory for data */
	C_SAFE_CALL(layer->x = mem_alloc(3 * size * sizeof(double), true) ); 
	layer->y = &layer->x[size];
	layer->z = &layer->y[size];

	/* copy data */
	memcpy(layer->x, x, size * sizeof(double));
	memcpy(layer->y, y, size * sizeof(double));
	memcpy(layer->z, z, size * sizeof(double));
	
	/* adjust mapping parameters */
	for(i = 0; i < size; i++){
		/* validate data nans and infs don't count */
			
	}
	
	
	/* optional parameters such as color 
	 * and linestyle are to be given later
	 * for now just set them to none
	 */
	
	/* add layer to plot and increase num layers */

	SET_API_ERROR( API_SUCCESS );
	return;
error:
	/* free layer */
	free_mem(layer);
	SET_API_ERROR( API_PLT_ADD_LAYER );
}



/* 
 * multiplot 
 * fixed inputs: plot dimension
 * variable inputs : plots 
 *  -> order of plots matters 
 * 		-> plots are displayed left to right and top to down
 * 		-> to ensure that the format is correct this function should be
 *		   called in the following manner multiplot(xdim,ydim, ..., NULL);
 */
void plt_multiplot(int32_t dim_x, int32_t dim_y, ...){
	static int32_t link = 1;
	va_list ap, ap_c;
	plot_t * plt;
	int32_t i = 0;
	
	C_CHECK_CONDITION( dim_x * dim_y <= 0, 
		"Warning: wrong matrix dimensions - multiplot - \"no object specified\"");
	
	va_start(ap,dim_y); 
	va_copy(ap_c, ap);
	
	for(i = 0; i < dim_x * dim_y; i++){
		/* consume arguments one by one */
		plt = va_arg(ap, plot_t *);
		
		C_CHECK_CONDITION( plt == NULL && (i+1) <= dim_x*dim_y,   
			"Warning: matrix badly formatted wrong number of arguments or invalid plot");
	}
	
	/* check if the last argument is null if it is not give error*/
	plt = va_arg(ap, plot_t *);
	C_CHECK_CONDITION( plt!=NULL,   
			"Warning: matrix badly formatted or wrong number of arguments");
	
	va_end(ap);
	
	/* now that inputs have been verified input, lets work */		
	for(i = 0; i < dim_x * dim_y ; i++){
		plt = va_arg(ap_c, plot_t *);
		plt->subplot_state = true;
		plt->subplot_dim[0] = x_dim;
		plt->subplot_dim[1] = y_dim;
		plt->subplot_num = i;
		plt->subplot_link = link;
	}
	va_end(ap_c);
	
	/* increment link */
	link++;
	
error:
	return;
}

/* 
 * Before calling the drawn routines check if there is any window we need to open...
 *
 */
#define VAR_NAME_LIMIT 128
void check_plts_windows(void){
	int32_t i = 0, j = 0;
	int32_t link = 0;
	
	char buffer[VAR_NAME_LIMIT];
	for(i = 0; i < pL.num_plts; i++){
		if( pL.window_int[i] == -1 ){
			/* is subplotting enabled ? */
			if( pL.plts[i]->subplot_state == true ){
				/* locate all plots 
				 * belonging to this subplot
				 * and open a common window 
				 * ! multiplot should destroy 
				 *   object window if it has one
				 */
				 link = pL.plts[i]->subplot_link;
				 snprintf(buffer,VAR_NAME_LIMIT,"subplot_%d",link);
				 
				 /* use variable name or subplot + link name */
				 pL.window_int[i] = createWindow(buffer);
				 
				 /* get the plots belonging to this subplot */
				 for(j = i+1; j < pL.num_plts; j++){
					if( pL.plts[j]->subplot_link == link){
						/* 
						 * if they already have a window and 
						 * is the same as this one don't
						 * do nothing otherwise kill it
						 */
						if( pL.window_int[j] != -1){
							if(pL.window_int[j] != pL.window_int[i]){
								glutDestroyWindow(pL.window_int[j]);
							}
							pL.window_int[j] = pL.window_int[i];
						}
					}
				 }
				 
			}else{
			     snprintf(buffer,VAR_NAME_LIMIT,"plot_%d",i);
				 /* use variable name or subplot + link name */
				 pL.window_int[i] = createWindow(buffer);
			}
		}
	}
}

/* each time a show command is issued 
 * we need to query if the object is in the queue 
 */
 void register_plt(const plot_t * plt){
	int32_t i = 0;
	bool lock_acquired = false;
	
	C_CHECK_CONDITION( plt == NULL, API_BAD_INPUT);
	
	/* verify if plt is in the queue */
	for(i = 0; i < pL.num_plts; i++){
		if(pL.plts[i]==plt)
			break;
	}
	
	/* add plot to queue */
	if(i >= pL.num_plts){
		C_SAFE_CALL( acquire_lock() );
		lock_acquired = true;
		
		/* allocate new plt in queue */
		C_SAFE_CALL( pL.plts = mem_realloc(
							pL.plts, (pL.num_plts+1) * sizeof(plot_t *)) 
					);
					
		C_SAFE_CALL( pL.windown_int = mem_realloc(
							pL.windown_int, (pL.num_plts+1) * sizeof(int32_t)
					);
	
		/* work out subplot dim pointers */
		for(i = 1; i < pL.num_plts+1; i++ )
			subplot_dim[i] = subplot_dim[0] + i * 2;
			
		pL.num_plts++;
		
		/* add new plt to the queue */
		pL.plts[pL.num_plts-1] = plt;
		
		/* needs to be sorted out!!! 
		 * the variables need to be filled before registering 
		 * (maybe we need to have them on each plot and copy them to pL)
		 */
		
		pL.window_int[pL.num_plts-1] = -1;
		
		C_SAFE_CALL( release_lock() );
		lock_acquired = false;
	}
	
	
	SET_API_ERROR(API_SUCCESS;
	return;
error:
	if(lock_acquired == true)
		release_lock();
	
	SET_API_ERROR(API_REGISTER_PLOT);
 }
 
 /* schedule plot to be drawn on screen */
 void queue_plt_redraw(plot_t * plt){
	int32_t i = 0;
	bool lock_acquired = false;
	plot_t * layer = NULL;
	/* verify if plt is in the queue */
	for(i = 0; i < pL.num_plts; i++){
		if(pL.plts[i]==plt)
			break;
	}
	if( i >= pL.num_plts){
		printf("Warning plot is unregistered! \t registering it for you...\n");
		C_SAFE_CALL( register_plt( plt ) );
		
		for(i = 0; i < pL.num_plts; i++){
			if(pL.plts[i]==plt)
				break;
		}
	}
	
	C_SAFE_CALL( acquire_lock() );
	lock_acquired = true;
	
	/* for each layer in plot commit data to screen */
	for(i=0; i<plt->num_layers; i++){
		layer = plt->layers[i];
		/* verify if the size is the same if it is not reallocate */
		if(layer->size != layer->size_data){
			C_SAFE_CALL( layer->xdata = mem_realloc(
							layer->xdata, layer->size * sizeof(plot_t *)) 
					);
			C_SAFE_CALL( layer->ydata = mem_realloc(
							layer->ydata, layer->size * sizeof(plot_t *)) 
					);
			C_SAFE_CALL( layer->zdata = mem_realloc(
							layer->zdata, layer->size * sizeof(plot_t *)) 
					);
			layer->size_data = layer->size;
		}
		/* copy data */
		memset(layer->xdata, layer->x, layer->size * sizeof(double));
		memset(layer->ydata, layer->y, layer->size * sizeof(double));
		memset(layer->zdata, layer->z, layer->size * sizeof(double));
	}
	
	C_SAFE_CALL( release_lock() );
	lock_acquired = false;
	
	SET_API_ERROR( API_SUCCESS );
	return;
error:
	if(lock_acquired == true)
		release_lock();
		
	SET_API_ERROR( API_QUEUE_PLOT );
 }
 
 /* unregister plot from queue */
 void unregister_plt(plot_t * plt){
	int32_t i = 0, j = 0;
	int32_t link = 0, window_handle = 0;
	bool lock_state = false;
	
	C_CHECK_CONDITION( plt == NULL, API_BAD_INPUT);
	
	C_SAFE_CALL( acquire_lock() );
	lock_state = true;
	
	/* verify if plt is in the queue */
	for(i = 0; i < pL.num_plts; i++){
		if(pL.plts[i]==plt)
			break;
	}
	if(i >= pL.num_plts){
		return;
	}
	
	window_handle = pL.window_handle[i];
	
	/* remove plt and other things from queue */
	for(j=i+1; j < pL.num_plts;j++){
		pL.plts[j-1] = pL.plts[j];
		pL.window_handle[j-1] = pL.window_handle[j];
	}
	
	pL.num_plts--;
	
	/* reescale input */
	
	/* destroy plt window */
	/* in subplotting do it only if the graphs 
	 * belonging to the same window have all been 
	 * unregistered 
	 */
	
	if(plt->subplot_state){
		
		/* get subplot link value */
		C_CHECK_CONDITION( (link = plt -> subplot_link) == 0, 
										"invalid subplot link");
		
		/* look for plots with the same link */
		for(j=0; j < pL.num_plts; j++ )
			if((pL.plts[j])->subplot_link == link)
				break;
	
		/* not found -> destroy plt window */
		if(j>=pL.num_plts && window_handle > 0)
			/* kill window */
			glutDestroyWindow(window_handle);
	}else{
		/* just kill the window */
		if(window_handle > 0)
			glutDestroyWindow(window_handle);
	}

	C_SAFE_CALL( release_lock() );
 
	SET_API_ERROR(API_SUCCESS);
	return;
 error:
	if(lock_state)
		release_lock();
		
	SET_API_ERROR(API_UNREG_PLOT);
 }
 
 /* return only when the lock is acquired */
 void acquire_lock(void){
	#ifdef WIN32
		int32_t ct = 0;
		while( WaitForSingleObject( pL.lock, INFINITE) != WAIT_OBJECT_0 || ct < 10)
			ct++;
	#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
		 pthread_mutex_lock( &pL.lock );
	#endif
 }
 
 /* release lock */
 void release_lock(void){
	#ifdef WIN32
		ReleaseMutex(pL.lock);
	#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
		pthread_mutex_unlock( &pL.lock );
	#endif
 }
