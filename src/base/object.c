#include "object.h"


/* object creation copy and related functions defined in this file */
plot_t * new_plot(int32_t plt_type){
	plot_t * new_plt = NULL;
	/* verify plot type before doing anything else */
	C_CHECK_CONDITION( plt_type < 0 && plt_type > PL_NUM_PLOT_TYPES, API_BAD_INPUT );
	
	/* create a default object */
	C_SAFE_CALL( new_plt = mem_alloc(sizeof(plot_t), true) );
	
	/* define plot type */
	new_plt->plt_type = plt_type;
	
	SET_API_ERROR(API_SUCCESS);
	return new_plt;
error:
	SET_API_ERROR(API_NEW_PLOT);
	return NULL;
}

/* WARNING: before killing the object we need to unregister it from the queue */
void delete_plt(plot_t * plt){
	if(plt!=NULL)
		unregister_plt(plt);
	
	mem_free(plt);
	
	SET_API_ERROR(API_SUCCESS);
	return;
error:
	SET_API_ERROR(API_DEL_PLOT);
}
