#include "opengl-api.h"
#include <dlfcn.h>
#include <stdio.h>

CreateShaderFunc * glCreateShader;
ShaderSourceFunc * glShaderSource;

int openglApiInit()
{
	void * libGL = dlopen("libGL.so", RTLD_LAZY);
	if (!libGL)
	{
		printf("ERROR: libGL.so couldn't be loaded\n");
		return 0;
	}

	glCreateShader = (CreateShaderFunc *) dlsym(libGL, "glCreateShader");

	if (!glCreateShader)
	{
		printf("Function glCreateShader couldn't be loaded from libGL.so\n");
		return 0;
	}

	glShaderSource = (ShaderSourceFunc * ) dlsym(libGL, "glShaderSource");
	if (!glShaderSource)
	{
		printf("Function glShaderSource couldn't be loaded from libGL.so\n");
		return 0;
	}

	return 1;
}
