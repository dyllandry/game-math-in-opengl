#include <stdlib.h>
#include <stdio.h>
#include "shader.h"
#include "file-helpers.h"
#include "opengl-api.h"

struct Shader NewShader(const char *vertexPath, const char *fragmentPath)
{
	// 1) Get the vertex & fragment shader source code from file path.
	const char *vertexSrc = getFileBytes(vertexPath);
	const char *fragmentSrc = getFileBytes(fragmentPath);
	if (!vertexSrc || !fragmentSrc)
	{
		printf("ERROR::SHADER::NEW_SHADER::GET_SOURCE_FILE_FAILED\n");
		exit(EXIT_FAILURE);
	}

	// 2) Compile the two shaders.
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexSrc, NULL);
	glCompileShader(vertexShaderId);
	{
		char compilationLog[512];
		int success;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShaderId, sizeof(compilationLog), NULL, compilationLog);
			printf("ERROR::SHADER::NEW_SHADER::SHADER_COMPILATION_FAILED %s\n", compilationLog);
			exit(EXIT_FAILURE);
		}
	}
	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShaderId);
	{
		char compilationLog[512];
		int success;
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShaderId, sizeof(compilationLog), NULL, compilationLog);
			printf("ERROR::SHADER::NEW_SHADER::SHADER_COMPILATION_FAILED %s\n", compilationLog);
			exit(EXIT_FAILURE);
		}
	}

	// 3) Create shader program and link two shaders.
	unsigned int shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glLinkProgram(shaderProgramId);
	{
		char programLinkLog[512];
		int success;
		glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgramId, sizeof(programLinkLog), NULL, programLinkLog);
			printf("ERROR::SHADER::NEW_SHADER::SHADER_PROGRAM_LINK_FAILED %s\n", programLinkLog);
			exit(EXIT_FAILURE);
		}
	}

	// 4) Delete/free no longer needed resources.
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	free((void *)vertexSrc);
	free((void *)fragmentSrc);

	struct Shader shader;
	shader.id = shaderProgramId;
	printf("INFO::SHADER::NEW_SHADER::SHADER_CREATED ID=%u\n", shader.id);
	return shader;
}

void useShader(const struct Shader shader)
{
	glUseProgram(shader.id);
}

void setShaderBool(const struct Shader shader, const char *name, int value)
{
	glUniform1i(glGetUniformLocation(shader.id, name), value);
}

void setShaderInt(const struct Shader shader, const char *name, int value)
{
	glUniform1i(glGetUniformLocation(shader.id, name), value);
}

void setShaderFloat(const struct Shader shader, const char *name, float value)
{
	glUniform1f(glGetUniformLocation(shader.id, name), value);
}

void setShaderVec3(const struct Shader shader, const char *name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shader.id, name), x, y, z);
}

void setShaderMat4(const struct Shader shader, const char *name, const mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.id, name), 1, GL_FALSE, mat[0]);
}

