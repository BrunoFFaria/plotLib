#include "ogl.h"

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
		
	
		/* call glut to render and handle events */
		glutMainLoopUpdate();
	}
	
	/* shutdown glut */
}


/* each time a show command is issued 
 * we need to query if the object is in the queue 
 */
 void register_plt(plot_t * plt){
	int32_t i = 0;
	bool lock_acquired = false;
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
			C_SAFE_CALL( layer->xdata = (double *) mem_realloc(
							layer->xdata, layer->size * sizeof(plot_t *)) 
					);
			C_SAFE_CALL( layer->ydata = (double *) mem_realloc(
							layer->ydata, layer->size * sizeof(plot_t *)) 
					);
			C_SAFE_CALL( layer->zdata = (double *) mem_realloc(
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
	
	/* destroy plt window */
	/* in subplotting do it only if the graphs 
	 * belonging to the same window have all been 
	 * unregistered 
	 */
	
	if(plt->subplot_state){
		
		/* get subplot link value */
		C_CHECK_CONDITION( (link = plt -> subplot_link) == 0, "invalid subplot link");
		
		/* look for plots with the same link */
		for(j=0; j < pL.num_plts; j++ )
			if((pL.plts[j])->subplot_link == link)
				break;
	
		/* not found -> destroy plt window */
		if(j>=pL.num_plts)
			/* kill window */
			
	}else{
		/* just kill the window */
		
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