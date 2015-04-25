#ifndef MEMORYH
	#define MEMORYH
	#include <inttypes.h>
	#include <stdlib.h>
	
	void * mem_realloc(void * ptr, int32_t new_sz);
	void * mem_alloc(int32_t size, bool zero_set);
	void free_mem(void * ptr);

	
#endif