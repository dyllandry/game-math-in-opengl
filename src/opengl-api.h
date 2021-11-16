/*
 * opengl-api.h: gets function pointers to gpu driver's opengl api
 *
 * To learn the reasons for loading opengl functions yourself, read
 * <https://apoorvaj.io/loading-opengl-without-glew/>
 *
 * Nice introduction to xmacros (heavily used here)
 * <https://stackoverflow.com/a/9384467/7933478>
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
 *
 * This kind of macro is often called an xmacro, here's a nice explanation
 * often them <https://stackoverflow.com/a/9384467/7933478>
 */
#define GL_FUNC_LIST \
	/* params: returnType, funcName, args... */ \
	GL_FUNC(GLuint, glCreateShader, GLenum type) \
	GL_FUNC(void, glShaderSource, GLuint shader, GLsizei count, const GLchar **string, const GLint *length) \
	GL_FUNC(void, glCompileShader, GLuint shader) \
	GL_FUNC(void, glGetShaderiv, GLuint shader, GLenum pname, GLint *params) \
	GL_FUNC(void, glGetShaderInfoLog, GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog) \
	GL_FUNC(GLuint, glCreateProgram) \
	GL_FUNC(void, glAttachShader, GLuint program, GLuint shader) \
	GL_FUNC(void, glLinkProgram, GLuint program) \
	GL_FUNC(void, glGetProgramiv, GLuint program, GLenum pname, GLint *params) \
	GL_FUNC(void, glGetProgramInfoLog, GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog) \
	GL_FUNC(void, glUseProgram, GLuint program) \
	GL_FUNC(void, glDeleteProgram, GLuint program) \
	GL_FUNC(void, glDeleteShader, GLuint shader) \
	GL_FUNC(void, glGenBuffers, GLsizei n, GLuint * buffers) \
	GL_FUNC(void, glGenVertexArrays, GLsizei n, GLuint *arrays) \
	GL_FUNC(void, glBindVertexArray, GLuint array) \
	GL_FUNC(void, glBindBuffer, GLenum target, GLuint buffer) \
	GL_FUNC(void, glBufferData, GLenum target, GLsizeiptr size, const void *data, GLenum usage) \
	GL_FUNC(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) \
	GL_FUNC(void, glEnableVertexAttribArray, GLuint index) \
	GL_FUNC(void, glDeleteVertexArrays, GLsizei n, const GLuint *arrays) \
	GL_FUNC(void, glDeleteBuffers, GLsizei n, const GLuint * buffers) \
	GL_FUNC(GLint, glGetUniformLocation, GLuint program, const GLchar *name) \
	GL_FUNC(void, glUniform4f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) \
	GL_FUNC(void, glUniform1i, GLint location, GLint v0) \
	GL_FUNC(void, glUniform1f, GLint location, GLfloat v0) \
	GL_FUNC(void, glUniform3f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) \
	GL_FUNC(void, glUniformMatrix4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) \
	GL_FUNC(void, glGenerateMipmap, GLenum target)

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

