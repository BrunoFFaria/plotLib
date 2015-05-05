#ifndef INTERFACEH
	#define INTERFACEH
	#include <stdarg.h>
	
	/* pl defines all the current state of plotlib */
	extern plotLib_t pL;
	
	void plotlib_thread(void);
	void check_plts_windows(void);
	void plt_show(plot_t * plt);
	void plt_add_layer(plot_t * plt);
	void multiplot(int32_t dim_x, int32_t dim_y, ...);
	void register_plt(plot_t * plt);
	void queue_plt_redraw(plot_t * plt);
	void unregister_plt(plot_t * plt);
	void acquire_lock(void);
	void release_lock(void);
#endif
