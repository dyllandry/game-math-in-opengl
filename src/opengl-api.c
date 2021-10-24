#include "opengl-api.h"
#include <dlfcn.h>
#include <stdio.h>

/* Here we define pointers to each of the opengl functions we use by defining a
 * function-like macro "GL_FUNC" and applying it to each "GL_FUNC" macro
 * contained by "GL_FUNC_LIST". */
#define GL_FUNC(returnType, funcName, ...) funcName##Type * funcName;
GL_FUNC_LIST
#undef GL_FUNC

int openglApiInit()
{
	void * libGL = dlopen("libGL.so", RTLD_LAZY);
	if (!libGL)
	{
		printf("ERROR: libGL.so couldn't be loaded\n");
		return 0;
	}

	/* Here we load each opengl function by again defining a macro GL_FUNC
	 * and applying it to each GL_FUNC macro contained by GL_FUNC_LIST. */
	#define GL_FUNC(returnType, funcName, ...) \
	funcName = (funcName##Type *) dlsym(libGL, #funcName); \
	if (!funcName) \
	{ \
		printf("Function " #funcName "couldn't be loaded from libGL.so\n");\
		return 0; \
	}
	GL_FUNC_LIST
	#undef GL_FUNC

	return 1;
}
