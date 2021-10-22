/*
 * opengl-api.h: gets function pointers to gpu driver's opengl api
 */

/* TODO: try glShaderSource by hand */
/* TODO: try turning glCreateShader and glShaderSource into macros */

#ifndef OPENGL_API_H
#define OPENGL_API_H

#include <GL/gl.h>

typedef GLuint CreateShaderFunc(GLenum type);
extern CreateShaderFunc * glCreateShader;

int openglApiInit();

#endif // OPENGL_API_H
