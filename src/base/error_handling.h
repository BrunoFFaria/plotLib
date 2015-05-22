#ifndef ERRORHANDLERH
	#define ERRORHANDLERH
	#include <stdlib.h>
	#include <stdio.h>
	
	/* error codes */
	enum error_codes{
		API_SUCCESS,	
		API_ALLOCATION_ERROR,
		API_REALLOC,
		API_BAD_INPUT,
		API_THREAD_INIT_FAIL,
		API_MUTEX_INIT_FAIL,
		API_PLT_ADD_LAYER,
		API_MATRIX_BAD_FORM,
		API_BAD_MATRIX_PLT,
		API_BAD_MATRIX_INPUT,
		API_REGISTER_PLOT,
		API_QUEUE_PLOT,
		API_INVALID_SUBPLOT_LINK,
		API_UNREG_PLOT,
		API_NEW_PLOT,
		API_DEL_PLOT,
		NUM_ERROR_CODES
	};

	extern const char * error_strings[NUM_ERROR_CODES];

	int32_t error_code = 0;
	
	/* prototype error function */
	#define C_SAFE_CALL(call)																	\
		do																						\
		{																						\
			call;																				\
			if( error_code != API_SUCCESS )														\
			{																					\
				fprintf(stderr,"[ERROR] At function %s:%s in line %d\n\twith message: %s\n",	\
							__FUNCTION__, __FILE__, __LINE__,	error_strings[error_code] );	\
				error_code = API_SUCCESS;														\
				goto error;																		\
			}																					\
		}while(0)
	
	
								
	#define C_CHECK_CONDITION(cond, message)														\
		do																							\
		{																							\
			if((cond) != 0)																			\
			{																						\
				fprintf(stderr, "[ERROR] At function %s:%s (%s) in line %d \n\twith message: %s\n",	\
				__FUNCTION__, __FILE__, #cond,__LINE__,error_strings[message]); 					\
				goto error;																			\
			}																						\
		}while(0)
#endif
