#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "opengl-api.h"
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

	/* Create our shader */
	/* -------------------------------------------------------------------- */
	struct Shader defaultShader = NewShader("src/vertex-shader.glsl", "src/fragment-shader.glsl");

	/* Setup vertex data, buffers, and configure vertex attributes for triangle. */
	/* -------------------------------------------------------------------- */
	float triVertices[] =
	{
		// Positions
		0.0f,  0.5f, 0.0f, 
		0.5f,  -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
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
	/* Position attribute */
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

		/* Use shader */
		useShader(defaultShader);

		/* Change triangle color. */
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		setShaderVec3(defaultShader, "ourColor", 0.0f, greenValue, 0.0f);

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
