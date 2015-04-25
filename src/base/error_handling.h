#ifndef ERRORHANDLERH
	#define ERRORHANDLERH
/* error codes */
enum error_codes{
		API_SUCCESS,	
		API_ALLOCATION_ERROR,
		API_REALLOC,
		NUM_ERROR_CODES
	};

	extern const char * error_strings[NUM_ERROR_CODES];

	
	/* prototype error function */
	#define C_SAFE_CALL(call)	\
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