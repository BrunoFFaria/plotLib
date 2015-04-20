#include "init.h"
#include "ogl.h"

/* 
 * init the plot lib thread 
 *
 */
int32_t plotLib_init(void){
	
	/* verify if object thread is already active */
	if(!PL.thread_state){
		#ifdef WIN32
			 _beginthread( plotlib_thread, 0, NULL );
		#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
			result_code = pthread_create(NULL, NULL, plotlib_thread, NULL);
		#endif
		pL.thread_state = true;
	}

	/* thread is active */
	return 0;
error:
	pL.thread_state = false;
	return -1;
}


void plotLib_stop(void){
	/* send kill signal to thread */
	
	/* variable access is mutexed */
}