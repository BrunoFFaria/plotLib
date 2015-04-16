#include "object.h"
#include "memory.h"

/* object creation copy and related functions defined in this file */
plot_t * new_plot(int32_t plt_type){
	
	/* verify plot type before doing anything else */
	C_CHECK_CONDITION( plt_type <0 && plt_type > LP_NUM_PLOT_TYPES, "invalid plot type" );
	
	/* create a default object */
	C_SAFE_CALL( (plot_t * new_plt = (plt_t *)mem_alloc(sizeof(plot_t), true)) );
	
	/* insert default plot type */
	new_plt.
	
	
	
	
	return plot_t;
error:
	return NULL;
}


void delete_plt(plot_t * plt){
	

error:

}
