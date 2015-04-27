#ifndef MODULESH
	#define MODULESH
		/* 
		* Any new module is exposed in this file through a set of functions...
		*/
		#include "2d_line.h"
		#include "3d_line.h"
		#include "surf.h"
		#include "mesh.h"
		
		enum PLOT_TYPE{PL_LINE2D, PL_LINE3D, PL_MESH, PL_SURF, PL_NUM_PLOT_TYPES};
		
		void plt_validate_requirements(const plot_t * plt,const double * x, const double * y, const double * z );
		
		/* the next table is related to the auxiliary data
		 * and is called on layer creation
		 */
		void * plt_aux_data_func[	plt_2d_line_aux, 
									plt_3d_line_aux,
									plt_mesh_aux,
									plt_surf_aux
								 ];
		
		/* validate requirements on new layer */
		void * plt_val_req_func[	plt_2d_line_req,
									plt_3d_line_req,
									plt_mesh_req,
									plt_surf_req
								];
							
		/* draw functions */
		void * plt_draw_func[	plt_2d_line_draw,
								plt_3d_line_draw,
								plt_mesh_draw,
								plt_surf_req
							];
		
		/* functions to be called on layer property change */
		void * plt_layer_prop[	plt_2d_line_layer,
								plt_3d_line_layer,
								plt_mesh_layer,
								plt_surf_layer,
		
							];
		
		

#endif