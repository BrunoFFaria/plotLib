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
		/* declare pointer to function of this type 
		 * functions are of the form void function(plot_t * plt, int32_t layer)
		 */
		typedef void (* plt_aux_data_func_ptr)(plot_t *, int32_t);
		 
		plt_aux_data_func_ptr[PL_NUM_PLOT_TYPES] = {	
														plt_2d_line_aux, 
														plt_3d_line_aux,
														plt_mesh_aux,
														plt_surf_aux
													};
								 
		/* validate requirements on new layer */
		typedef void (* plt_val_req_func_ptr)(plot_t *, double *, double *, double *);
		plt_val_req_func_ptr[PL_NUM_PLOT_TYPES] = {	
														plt_2d_line_req,
														plt_3d_line_req,
														plt_mesh_req,
														plt_surf_req
													};
							
		/* draw functions */
		typedef void (* plt_draw_func_ptr)(plot_t *, int32_t, int32_t);
		plt_draw_func_ptr[PL_NUM_PLOT_TYPES] = {	
													plt_2d_line_draw,
													plt_3d_line_draw,
													plt_mesh_draw,
													plt_surf_req
												};
		
		/* functions to be called on layer property change */
		typedef void (* plt_set_layer_prop_func_ptr)(int32_t, int32_t);
		
		plt_set_layer_prop_func_ptr[PL_NUM_PLOT_TYPES] = {
															plt_2d_line_layer,
															plt_3d_line_layer,
															plt_mesh_layer,
															plt_surf_layer,
														};
		/* free plot layer */
		typedef void (*plt_free_aux_data_func_ptr);
		
		plt_free_aux_data_func_ptr[PL_NUM_PLOT_TYPES] = {
															plt_2d_line_free_aux,
															plt_3d_line_free_aux,
															plt_mesh_free_aux,
															plt_surf_free_aux
														};
		
		

#endif