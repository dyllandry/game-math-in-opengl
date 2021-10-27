#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "opengl-api.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core \n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"        gl_Position = vec4(aPos, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec4 vertexColor;\n"
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"        FragColor = vec4(ourColor);\n"
	"}\n";

int main()
{
	/* glfw: init */
	/* -------------------------------------------------------------------- */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* glfw: create window */
	/* -------------------------------------------------------------------- */
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* opengl: init function pointers to gpu driver's opengl api. */
	/* -------------------------------------------------------------------- */
	openglApiInit();

	/* Build and compile shader program */
	/* -------------------------------------------------------------------- */
	/* Compile our vertex shader */
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	/* Check if vertex shader compiled correctly */
	{
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
			return 1;
		}
	}
	/* Compile our fragment shader. */
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	/* Check if fragment shader compiled correctly */
	{
		int success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
			return 1;
		}
	}
	/* Links shaders into shader program. */
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	/* Check if shader program linked successfuly */
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
			return 1;
		}
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/* Setup vertex data, buffers, and configure vertex attributes for triangle. */
	/* -------------------------------------------------------------------- */
	float triVertices[] =
	{
		0.0f,  0.5f, 0.0f,  // top center
		0.5f,  -0.5f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
	};
	/* Setup vertex buffer object, vertex array object */
	unsigned int triVBO, triVAO;
	glGenBuffers(1, &triVBO);
	/* glGenBuffers(1, &lTriEBO); */
	glGenVertexArrays(1, &triVAO);
	/* Bind VAO first, then VBO, then setup vertex attributes. */
	glBindVertexArray(triVAO);
	glBindBuffer(GL_ARRAY_BUFFER, triVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);
	/* Link vertex attributes */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* Unbind VBO. */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Unbind VAO. */
	glBindVertexArray(0);

	/* uncomment this call to draw in wireframe polygons. */
	/* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

	/* Render loop */
	/* -------------------------------------------------------------------- */
	while (!glfwWindowShouldClose(window))
	{
		/* handle user input */
		processInput(window);
		/* render */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		/* Activate shader */
		glUseProgram(shaderProgram);

		/* Change triangle color. */
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		/* Draw triangle */
		glBindVertexArray(triVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		/* glfw: swap the double render buffer & poll IO events */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* De-allocate resources */
	glDeleteVertexArrays(1, &triVAO);
	glDeleteBuffers(1, &triVBO);
	glDeleteProgram(shaderProgram);

	/* glfw: terminate, clears all allocated GLFW resources */
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}
