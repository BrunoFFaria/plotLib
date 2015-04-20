#ifndef OGLH
	#define OGLH
	/* pl defines all the current state of plotlib */
	extern plotLib pL;
	
	void plotlib_thread(void);
	void register_plt(plot_t * plt);
	void unregister_plt(plot_t * plt);
#endif