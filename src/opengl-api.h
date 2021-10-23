/*
 * opengl-api.h: gets function pointers to gpu driver's opengl api
 */

/* TODO: try turning glCreateShader and glShaderSource into macros */

#ifndef OPENGL_API_H
#define OPENGL_API_H

#include <GL/gl.h>

typedef GLuint CreateShaderFunc(GLenum type);
extern CreateShaderFunc * glCreateShader;

typedef void ShaderSourceFunc(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
extern ShaderSourceFunc * glShaderSource;

int openglApiInit();

#endif // OPENGL_API_H
