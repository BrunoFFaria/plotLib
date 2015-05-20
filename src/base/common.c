#include "common.h"
/*
 * D65 white is used by default
 */
 /* 
  * Colorspace conversion code copied from 
  * http://cran.r-project.org/web/packages/colorspace/index.html
  */
 
#define XN 	95.047
#define YN 	100.000
#define ZN	108.883
double plt_mapminmax(double xmin, double xmax, double ymin, double ymax, double x){
	return (ymax-ymin)*(x-xmin)/(xmax-xmin) + ymin;	
}


void plt_adjust_mapminmax(const plot_t * plt, const double * x, const double * y, const double * z){

	
}

/* convert hsv into RGB color 
 * format
 *
 * requires h in 0..360
 *			s in 0..1
 *			v in 0..1
 */
uint32_t plt_get_hsv_color(float h, float s, float v){
	float r = 0.0f, g = 0.0f, b = 0.0f;
	float hl = 0.0f, c  = 0.0f, x = 0.0f, m = 0.0f;
	
	h = fmodf(h , 360.0f);
	s = s - floorf(s);
	v = v - floorfS(v);
	
	/* chroma */
	c = v * s;
	
	/* hue line */
	hl = h/60.0f;
	
	x = c * (1 - abs( fmodf(hl, 2) - 1));
		
	switch(floor(hl))
	{
		case 0:	r = c; 	g = x; break;
		case 1: r = x; 	g = c; break;
		case 2: g = c; 	b = x; break;
		case 3: g = x; 	b = c; break;
		case 4: r = x; 	b = c; break;
		case 5: r = c; 	b = x; break;
		default: r = 0; g = 0; b = 0; break;
	}
	
	r += v - c;
	g += v - c;
	b += v - c;
	
	return ( ((uint32_t)(r * 255) << 16 ) | 
			 ((uint32_t)(g * 255) <<  8 ) |
			  (uint32_t)(b * 255) 
			);
			  
}

static void polarLUV_to_LUV(float l, float c, float h, float * L, float * U, float * V)
{
    h = DEG2RAD(h);
    *L = l;
    *U = c * cosf(h);
    *V = c * sinf(h);
}

static void XYZ_to_uv(float X, float Y, float Z, float * u, float * v)
{
    float t = 0, x = 0, y = 0;
    t = X + Y + Z;
    
	x = X / t;
    y = Y / t;
    
	*u = 2 * x / (6 * y - x + 1.5);
    *v = 4.5 * y / (6 * y - x + 1.5);
}

static void LUV_to_XYZ(float L, float U, float V, float * X, float * Y, float * Z)
{
    float u = 0, v = 0, uN = 0, vN = 0, a = 0;
    *X = 0; *Y = 0; *Z = 0;
	
	if ( !(L <= 0 && U == 0 && V == 0) ){
		a = (L + 16)/116;
		a*=a; 
		a*=a; 
		*Y = YN * ((L > 7.999592) ? a : L / 903.3);
		
		XYZ_to_uv(XN, YN, ZN, &uN, &vN);
		
		u = U / (13 * L) + uN;
		v = V / (13 * L) + vN;
		
		*X =  9.0 * *Y * u / (4 * v);
		*Z =  - (*X) / 3 - 5 * (*Y) + 3 * (*Y) / v;
    }
}

static void XYZ_to_RGB(float X, float Y, float Z, float * R, float * G, float * B)
{
    *R = ( 3.240479 * X  - 1.537150 * Y   - 0.498535 * Z) / YN;
    *G = (-0.969256 * X + 1.875992 * Y  + 0.041556 * Z) / YN;
    *B = ( 0.055648 * X  - 0.204043 * Y  + 1.057311 * Z) / YN;
}

static int32_t plt_get_hcl_as_rgb(float h, float c, float l){

	float L = 0, U = 0, V = 0, X = 0, Y = 0, Z = 0, R = 0, G = 0, Z = 0;
	polarLUV_to_LUV(l, c, h, &L, &U, &V);
	LUV_to_XYZ(L, U, V,  &X, &Y, &Z);
	XYZ_to_RGB(X, Y, Z, &R, &G, &B);

	/* now return that value as an int32_t */
	return ( ((uint32_t)(R * 255) << 16 ) | 
				 ((uint32_t)(G * 255) <<  8 ) |
				  (uint32_t)(B * 255) 
				);
}
void plt_get_hue_color( int32_t color , int32_t num_colors ){
	plt_get_hcl_color(h, 0.65f, 1.0f);
}


void draw_2d_axes(){


}


void draw_3d_axes(){


}
