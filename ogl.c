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
	
	while(1){
		/* query plotLib thread msg (should this thread exit?)*/
		if(pL.thread_msg == thread_msg_exit)
			break;
			
		/* verify that every plot has a window for where to be draw,
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
		C_SAFE_CALL( pL.plts = (plot_t **) mem_realloc(
							pL.plts, (pL.num_plts+1) * sizeof(plot_t *)) 
					);
		C_SAFE_CALL( pL.plts_state = (bool *) mem_realloc(
							pL.plts_state, (pL.num_plts+1) * sizeof(plot_t *)
					);
		
		
		pL.num_plts++;
		
		/* add new plt to the queue */
		pL.plts[pL.num_plts-1] = plt;
		
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
	
	/* queue plot */
	pL.plts_state[i] = true;
	
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
	
	
	C_SAFE_CALL( acquire_lock() );
	
	C_SAFE_CALL( release_lock() );
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