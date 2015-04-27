#ifndef DRAWH
	#define DRAWH
		
		enum line_types{PL_NONE, PL_POINTS, PL_DASHES, PL_DDASH, PL_DASHPD, PL_NUM_LINE_STYLES};
		enum PLOT_TYPE{PL_LINE2D, PL_LINE3D, PL_MESH, PL_SURF, PL_NUM_PLOT_TYPES};
		enum PLOT_REQUIREMENTS{xy=2, xyz};
		
		/*
 		 * Define PLOT_TYPE variable requirements 
		 *
 		 */
	 	const int32_t plt_req_arr[PL_NUM_PLOT_TYPES] = { xy,	/* PL_LINE2D */
	 													 xyz,	/* PL_LINE3D */ 
	 													 xyz,   /* PL_MESH   */
	 													 xyz, 	/* PL_SURF   */
	 													};
	 	
	 			
#endif
