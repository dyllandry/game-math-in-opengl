/* #include <glad/glad.h> */
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

	/* glad: load opengl function pointers */
	/* -------------------------------------------------------------------- */
	/* if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) */
	/* { */
	/* 	printf("Failed to initialize GLAD\n"); */
	/* 	return 1; */
	/* } */

	openglApiInit();

	/* Build and compile shader program */
	/* -------------------------------------------------------------------- */
	/* Compile our vertex shader */
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/* glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); */
	/* glCompileShader(vertexShader); */
	/* Check if vertex shader compiled correctly */
	/* { */
	/* 	int success; */
	/* 	char infoLog[512]; */
	/* 	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); */
	/* 	if (!success) */
	/* 	{ */
	/* 		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); */
	/* 		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog); */
	/* 		return 1; */
	/* 	} */
	/* } */
	/* Compile our fragment shader. */
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	/* glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); */
	/* glCompileShader(fragmentShader); */
	/* Check if fragment shader compiled correctly */
	/* { */
	/* 	int success; */
	/* 	char infoLog[512]; */
	/* 	/1* glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); *1/ */
	/* 	if (!success) */
	/* 	{ */
	/* 		/1* glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); *1/ */
	/* 		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog); */
	/* 		return 1; */
	/* 	} */
	/* } */
	/* Links shaders into shader program. */
	unsigned int shaderProgram;
	/* shaderProgram = glCreateProgram(); */
	/* glAttachShader(shaderProgram, vertexShader); */
	/* glAttachShader(shaderProgram, fragmentShader); */
	/* glLinkProgram(shaderProgram); */
	/* Check if shader program linked successfuly */
	/* { */
	/* 	int success; */
	/* 	char infoLog[512]; */
	/* 	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); */
	/* 	if (!success) */
	/* 	{ */
	/* 		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); */
	/* 		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog); */
	/* 		return 1; */
	/* 	} */
	/* } */
	/* glDeleteShader(vertexShader); */
	/* glDeleteShader(fragmentShader); */

	/* Setup vertex data, buffers, and configure vertex attributes. */
	/* -------------------------------------------------------------------- */
	float vertices[] =
	{
		0.5f,  0.5f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};
	unsigned int indices[] =
	{
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};
	/* Setup vertex buffer object, vertex array object */
	unsigned int VBO, VAO;
	unsigned int EBO;
	/* glGenBuffers(1, &VBO); */
	/* glGenBuffers(1, &EBO); */
	/* glGenVertexArrays(1, &VAO); */
	/* Bind VAO first, then VBO, then setup vertex attributes. */
	/* glBindVertexArray(VAO); */
	/* glBindBuffer(GL_ARRAY_BUFFER, VBO); */
	/* glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); */
	/* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */
	/* glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); */
	/* Link vertex attributes */
	/* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); */
	/* glEnableVertexAttribArray(0); */
	/* Unbind VBO. */
	/* glBindBuffer(GL_ARRAY_BUFFER, 0); */
	/* Unbind VAO. */
	/* glBindVertexArray(0); */

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
		/* glUseProgram(shaderProgram); */
		/* glBindVertexArray(VAO); */
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/* Don't have to unbind since we don't draw anything else, but */
		/* you would if you had other shapes to draw. */
		/* glBindVertexArray(0); */

		/* glfw: swap the double render buffer & poll IO events */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* De-allocate resources */
	/* glDeleteVertexArrays(1, &VAO); */
	/* glDeleteBuffers(1, &VBO); */
	/* glDeleteProgram(shaderProgram); */

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
