#include "error_handling.h"

const char * error_strings[NUM_ERROR_CODES]={"API SUCCESS",
											 "API ALLOCATION ERROR",
											 "API REALLOCATION ERROR"
											 "API BAD INPUT",
											 "API thread init failed",
											 "API mutex init failed",
											 "API could not add layer into plot",
											 "Warning: wrong matrix dimensions - multiplot - \"no object specified\"",
											 "Warning: matrix badly formatted wrong number of arguments or invalid plot",
											 "Warning: matrix badly formatted or wrong number of arguments",
											 "API could not register plot",
											 "API could not queue plot",
											 "API error invalid subplot link",
											 "API unregister plot",
											 "API error could not create plot",
											 "API error could not destroy plot"
											 };
