#include "draw.h"
#include "ogl.h"

/* show current plot */
void plt_show(plot_t * plt){

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

// add another layer to the current plot
void plt_add_layer(plot_t * plt){
	/* invalidate any plot redraw command */

	/* allocate memory for the layer */
	
	/* increase number of layers */
	
	/* adjust mapping parameters */
}

