#ifndef SURF_H
	#define SURF_H
	void * plt_surf_aux(int32_t layer_num);
	int32_t plt_surf_req(plot_t * plt, const double * x, const double * y, const double * z);
	int32_t plt_surf_draw(void * ptr, const double * x, const double * y, const double * z, int32_t layer, int32_t num_layers);
	void plt_surf_layer(int32_t property, int32_t value);
	void plt_surf_free_aux(void * ptr);
#endif
