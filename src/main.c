#include <GLFW/glfw3.h>
#include <stdio.h>
#include "opengl-api.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core \n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

	/* Setup vertex data, buffers, and configure vertex attributes for left triangle. */
	/* -------------------------------------------------------------------- */
	float leftTriVertices[] =
	{
		-0.6f,  0.5f, 0.0f,   // top left
		0.4f,  0.5f, 0.0f,   // top right
		-0.6f, -0.5f, 0.0f,  // bottom left
	};
	/* Setup vertex buffer object, vertex array object */
	unsigned int leftTriVBO, leftTriVAO;
	glGenBuffers(1, &leftTriVBO);
	/* glGenBuffers(1, &lTriEBO); */
	glGenVertexArrays(1, &leftTriVAO);
	/* Bind VAO first, then VBO, then setup vertex attributes. */
	glBindVertexArray(leftTriVAO);
	glBindBuffer(GL_ARRAY_BUFFER, leftTriVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftTriVertices), leftTriVertices, GL_STATIC_DRAW);
	/* Link vertex attributes */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* Unbind VBO. */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Unbind VAO. */
	glBindVertexArray(0);

	/* Setup vertex data, buffers, and configure vertex attributes for right triangle. */
	/* -------------------------------------------------------------------- */
	float rightTriVertices[] =
	{
		0.6f,  0.5f, 0.0f,   // top right
		0.6f, -0.5f, 0.0f,   // bottom right
		-0.4f, -0.5f, 0.0f,  // bottom left
	};
	unsigned int rightTriVBO;
	unsigned int rightTriVAO;
	/* Get ids for vbo and vao */
	glGenBuffers(1, &rightTriVBO);
	glGenVertexArrays(1, &rightTriVAO);
	/* Bind them for manipulation, vao first, vbo second */
	glBindVertexArray(rightTriVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rightTriVBO);
	/* Fill VBO with data */
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightTriVertices), rightTriVertices, GL_STATIC_DRAW);
	/* Tell opengl it should give first 3 floats of vertex data to shader as a vertex attribute. */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	/* Enable vertex attributes for shader. */
	glEnableVertexAttribArray(0);

	/* unbind vbo first, vao second */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

		/* Draw triangle */
		glUseProgram(shaderProgram);

		glBindVertexArray(leftTriVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glBindVertexArray(rightTriVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		/* glfw: swap the double render buffer & poll IO events */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* De-allocate resources */
	glDeleteVertexArrays(1, &leftTriVAO);
	glDeleteBuffers(1, &leftTriVBO);
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
