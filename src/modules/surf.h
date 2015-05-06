#ifndef SURF_H
	#define SURF_H
	static void * plt_surf_aux(int32_t layer_num);
	static int32_t plt_surf_req(plot_t * plt, const double * x, const double * y, const double * z);
	static int32_t plt_mesh_draw(void *, const double * x, const double * y, const double * z, int32_t layer, int32_t num_layers);
	static void plt_surf_layer(int32_t property, int32_t value);
	static void plt_surf_free_aux(void * ptr);
#endif