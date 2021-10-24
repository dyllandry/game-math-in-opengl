/*
 * opengl-api.h: gets function pointers to gpu driver's opengl api
 *
 * Implementation learned from <https://apoorvaj.io/loading-opengl-without-glew/>
 *
 */

#ifndef OPENGL_API_H
#define OPENGL_API_H

#include <GL/gl.h>

/*
 * GL_FUNC_LIST is a macro that whenever used will produce a list of
 * function-like macro "GL_FUNC" that can be defined, undefined, and redefined
 * to do different things with the provided arguments.
 *
 * For example, GL_FUNC is defined below to create both typedefs for these
 * opengl functions and declare them as extern. And in opengl-api.c, GL_FUNC is
 * repeatedly defined, undefined, and redefined to create code that will define
 * pointers to each of these functions as well as load them dynamically using
 * libGL.so
 */
#define GL_FUNC_LIST \
	/* params: returnType, funcName, args... */ \
	GL_FUNC(GLuint, glCreateShader, GLenum type) \
	GL_FUNC(void, glShaderSource, GLuint shader, GLsizei count, const GLchar **string, const GLint *length)

#define GL_FUNC(returnType, funcName, ...) \
	/* Create a typedef for the opengl function so the function pointers are shorter to type. */ \
	typedef returnType funcName##Type(__VA_ARGS__); \
	/* Declare function pointer as extern so files that include this header can reference it. */ \
	extern funcName##Type * funcName;

/* So, because we've just defined GL_FUNC, when we next use the GL_FUNC_LIST
 * macro, our GL_FUNC macro will run for each GL_FUNC in GL_FUNC_LIST. */
GL_FUNC_LIST
#undef GL_FUNC

int openglApiInit();

#endif // OPENGL_API_H

