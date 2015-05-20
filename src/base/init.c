#include "init.h"
#include "draw.h"


/* 
 * init the plot lib thread 
 *
 */
int32_t plotLib_init(void){
	
	/* verify if object thread is already active */
	if(!pL.thread_state){
		#ifdef WIN32
			C_CHECK_CONDITION( 
				( pL.h_thread = _beginthread( plotlib_thread, 0, NULL ) ) == -1L, 
				"thread init failed" );
			C_CHECK_CONDITION( 
				( pL.lock = CreateMutex( NULL, FALSE, NULL) ) == NULL,
				"mutex init failed" );
			 
		#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
			C_CHECK_CONDITION( 
				pthread_create(&pL.h_thread, NULL, plotlib_thread, NULL) != 0,
				"thread init failed" );
			C_CHECK_CONDITION( 
				pthread_mutex_init(&pL.lock, NULL) != 0, 
				"mutex init failed" ); 
			
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
	pL.thread_msg = thread_msg_exit;
	
	/* close thread and destroy mutex*/
	#ifdef WIN32
		/* wait for thread to exit */
		WaitForSingleObject( pL.h_thread, INFINITE );
		
		CloseHandle(pL.lock);
		CloseHandle(pL.h_thread);
	#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
		
		pthread_join(&pL.h_thread);
		pthread_mutex_destroy(&pL.lock);
	#endif 
}
