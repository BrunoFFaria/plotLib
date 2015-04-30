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
			
			/* the above data is commited to the next 
			 * pointers with plt_show and consequently 
			 * shown on scren
			 */
			 
			double * xdata;
			double * ydata;
			double * zdata;
			size_t   size_data;
			
			/* define layer properties */
			char * legend;
			
			/* expose auxiliary layer data 
			 * through a general pointer
			 */
			void * aux_layer_data;
		}plt_layer_t;
		
		typedef struct tranform_map{
			double xmin;
			double xmax;
			double ymin;
			double ymax;
			double zmin;
			double zmax;
			bool   state;
		}tranf_map_t;
		
		/* define our plot object */
		typedef struct plot{
		
			/* define the plot type (2D, 3D, line surface etc)*/
			int32_t plt_type;
			
			/* define number of layers in plot : i.e. number of lines, surfaces etc*/
			int32_t num_layers;
			
			/* plot layers */
			plt_layer_t * layers;
			
			/* transform mapping properties */
			transf_map_t map;
			
			/* define common operations: titles labels etc */
			char * xlabel;
			char * ylabel;
			char * zlabel;
			char * title;
			
			/* subplotting */
			bool 	subplot_state;
			int32_t subplot_dim[2];
			int32_t subplot_num;
			int32_t	subplot_link;
		}plot_t;

		enum thread_msgs {thread_msg_none,thread_msg_exit};
		
		/* plot lib state object */
		typedef struct plotLib{
			/* plot objects */
			plot_t ** plts;
			
			/* number of plot objects */
			int32_t   num_plts;
			
			/* lib thread status*/
			bool thread_state;
			
			/* messages to thread */
			int32_t thread_msg;
			
			/* window and subplotting handler */
			int32_t * windown_handle;
			
			/* window width and height */
			int32_t * width;
			int32_t * height;
			
			/* thread handle, lock state and plot window handle */
			#ifdef WIN32
				HANDLE h_thread;
				HANDLE lock;
						
			#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
				pthread_t		h_thread;
				pthread_mutex_t lock;				 
			#endif 
		}plotLib_t;
		
#endif
