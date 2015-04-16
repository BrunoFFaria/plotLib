#ifndef VARSH
	#define VARSH
		/* define the enumerator for plot type */
		enum PLOT_TYPE{ LINE_2D, LINE_3D, SURF, MESH};
		
		/* define plot layer */
		typedef struct plot_layer{
			double * x;
			double * y;
			double * z;
			size_t   size;
			
			/* define layer properties */
			char * legend;
			int32_t color;
			
		}plt_layer_t;
		
		typedef struct tranform_map{
			double xmin;
			double xmax;
			double ymin;
			double ymax;
			double zmin;
			double zmax;
		}tranf_map_t;
		
		/* define our plot object */
		// TODO think how to do subplotting 
		typedef struct plot{
		
			/* define the plot type (2D, 3D, line surface etc)*/
			int32_t plt_type;
			
			/* define number of layers in plot : i.e. number of lines, surfaces etc*/
			int32_t num_layers;
			
			/* plot layers */
			plt_layer_t * layers;
			
			/* transforma mapping properties */
			transf_map_t map;
			
			/* define common operations titles labels etc */
			char * xlabel;
			char * ylabel;
			char * zlabel;
			char * title;
						
			/* define the functions operating over the plot */
			int32_t (* show)(*self);
			int32_t (* add_layer)(self *, double *, double *, double *, int32_t);
			int32_t (* set_layer_col)(self *,int32_t, int32_t);
			int32_t (* set_layer_linetype)(self *,int32_t, int32_t);
			
			/* error code : if there is any error, it is reported in this variable */
			int32_t error_code;
		}plot_t;

		
#endif