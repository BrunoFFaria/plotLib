#ifndef INTERFACEH
	#define INTERFACEH
	#include <stdarg.h>
	#include <GL/glut.h>
	#include "vars.h"
	#include "draw.h"
	#include "error_handling.h"
	#include "memory.h"
	
	/* pL defines all the current state of plotlib */
	extern plotLib_t pL;
	
	#ifdef WIN32
		void plotlib_thread(void * arg);
	#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
		void * plotlib_thread(void * arg);
	#endif
	void check_plts_windows(void);
	void plt_show(const plot_t * plt);
	void plt_add_layer(plot_t * plt, const double * x, const double * y, const double * z, size_t size);
	void multiplot(int32_t dim_x, int32_t dim_y, ...);
	void register_plt(const plot_t * plt);
	void queue_plt_redraw(const plot_t * plt);
	void unregister_plt(plot_t * plt);
	void acquire_lock(void);
	void release_lock(void);
#endif
