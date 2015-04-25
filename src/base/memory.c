#include "memory.h"

void * mem_realloc(void * ptr, int32_t new_sz)
{
	void * new_ptr = realloc( ptr, new_sz );
	if(new_ptr == NULL){
		SET_API_ERROR(API_REALLOC);
		return NULL;	
	}
	SET_API_ERROR(API_SUCCESS); 
	return new_ptr;
}


/* memory allocation function */
void * mem_alloc(int32_t size, bool zero_set)
{
     void * p = malloc(size);
    
     if(p == NULL){ 
		SET_API_ERROR(API_ALLOCATION_ERROR); 
		return NULL;
	 }
     
     if(zero_set == true){
        memset(p, 0, size);
     }
     SET_API_ERROR(API_SUCCESS); 
     return p;
}

/* memory deallocation function */
void free_mem(void * ptr)
{
	free( ptr );
}

