#include "draw.h"

void plt_validate_requirements(const plot_t * plt,const double * x, const double * y, const double * z ){
	
	/* validate plot type */
	C_CHECK_CONDITION( plt->plt_type <= 0, API_BAD_INPUT );
	C_CHECK_CONDITION( plt->plt_type >= PL_NUM_PLOT_TYPES, API_BAD_INPUT ); 
	
	/* get number of restrictions  */
	switch(plt_req_arr[plt->plt_type]){
		case xyz:
			C_CHECK_CONDITION( z == NULL, API_BAD_INPUT);
		case xy:
			C_CHECK_CONDITION( y == NULL, API_BAD_INPUT);
			C_CHECK_CONDITION( x == NULL, API_BAD_INPUT);
			break;
		default:
			SET_API_ERROR( API);
			break;
	}
	SET_API_ERROR( API_SUCCESS );
	return; 
error:
	SET_API_ERROR( API_PLT_VALIDATE );
}

