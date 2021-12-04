#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "opengl-api.h"
#include "shader.h"
#include "../ext/include/stb_image.h"
#include "../ext/include/cglm/vec4.h"
#include "../ext/include/cglm/mat4.h"
#include "../ext/include/cglm/affine.h"
#include "../ext/include/cglm/cam.h"

#define DEBUG

#include "../ext/include/cglm/io.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void changeTextureMix(float delta);
void increaseTextureMix();
void decreaseTextureMix();
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
void scaleUp();
void scaleDown();
void rotateClockwise();
void rotateCounterClockwise();

struct Shader defaultShader;
float textureMix = 0.2f;

vec4 position = { 0.0f, 0.0f, 0.0f, 1.0f };
vec3 scale = { 1.0f, 1.0f, 1.0f };
float rotationRadians = 0.0f;

int screenWidth;
int screenHeight;

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
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	/* opengl: init function pointers to gpu driver's opengl api. */
	/* -------------------------------------------------------------------- */
	openglApiInit();

	/* Create our shader */
	/* -------------------------------------------------------------------- */
	defaultShader = NewShader("src/vertex-shader.glsl", "src/fragment-shader.glsl");

	/* Setup vertex data, buffers, and configure vertex attributes. */
	/* -------------------------------------------------------------------- */
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 cubePositions[] = {
		{0.0f,  0.0f, 0.0f },
		{2.0f, 5.0f, -15.0f },
		{-1.5f, -2.2f, -2.5f },
		{-3.8f, -2.0f, -12.3f },
		{2.4f, -0.4f, -3.5f },
		{-1.7f, 3.0f, -7.5f },
		{1.3f, -2.0f, -2.5f },
		{1.5f, 2.0f, -2.5f },
		{1.5f, 0.2f, -1.5f },
		{-1.3f, 1.0f, -1.5f }
	};

	glEnable(GL_DEPTH_TEST);

	/* Setup vertex buffer object, vertex array object */
	unsigned int vbo, vao;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	/* Bind VAO first, then VBO, then setup vertex attributes. */
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/* Link vertex attributes */
	/* Position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* Texture coordinate attribute */
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* load and create a texture*/
	/* -------------------------------------------------------------------- */
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	/* Set texture wrapping/filtering options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/* Load and generate the texture */
	stbi_set_flip_vertically_on_load(1);
	int textureWidth, textureHeight, textureNumChannels;
	unsigned char *textureData = stbi_load("media/container.jpg", &textureWidth, &textureHeight, &textureNumChannels, 0);
	if (!textureData)
	{
		printf("TEXTURE::LOAD_TEXTURE_DATA_FAILED\n");
		exit(EXIT_FAILURE);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData);
	glBindTexture(GL_TEXTURE_2D, 0);
	/* load and create a second texture*/
	/* -------------------------------------------------------------------- */
	unsigned int faceTexture;
	glGenTextures(1, &faceTexture);
	glBindTexture(GL_TEXTURE_2D, faceTexture);
	/* Set texture wrapping/filtering options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/* Load and generate the texture */
	int faceTextureWidth, faceTextureHeight, faceTextureNumChannels;
	unsigned char *faceTextureData = stbi_load("media/awesomeface.png", &faceTextureWidth, &faceTextureHeight, &faceTextureNumChannels, 0);
	if (!faceTextureData)
	{
		printf("TEXTURE::LOAD_FACE_TEXTURE_DATA_FAILED\n");
		exit(EXIT_FAILURE);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, faceTextureWidth, faceTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceTextureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(faceTextureData);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* Necessary for transparency in textures. */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* uncomment this call to draw in wireframe polygons. */
	/* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

	/* handle Input */
	glfwSetKeyCallback(window, &keyPressed);

	/* Render loop */
	/* -------------------------------------------------------------------- */
	while (!glfwWindowShouldClose(window))
	{
		/* render */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Bind textures */
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, faceTexture);

		for (int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++)
		{
			/* Create model, view, and projection matrixes so*/
			/* opengl can transform our local vectors to clip*/
			/* space.*/
			// Model matrix
			mat4 modelMatrix;
			glm_translate_make(modelMatrix, cubePositions[i]);
			glm_rotate(modelMatrix, glm_rad(-10.0f * glfwGetTime()), GLM_YUP);
			glm_rotate(modelMatrix, glm_rad(10.0f * glfwGetTime()), GLM_XUP);
			// View matrix
			mat4 viewMatrix;
			glm_mat4_identity(viewMatrix);
			glm_translate_z(viewMatrix, -3.0f);
			// Projection matrix
			mat4 perspectiveMatrix;
			glm_mat4_identity(perspectiveMatrix);
			glm_perspective(glm_rad(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f, perspectiveMatrix);

			/* Use shader */
			useShader(defaultShader);
			/* Set textures */
			setShaderInt(defaultShader, "texture1", 0);
			setShaderInt(defaultShader, "texture2", 1);
			setShaderFloat(defaultShader, "smileyOpacity", 0.8f);
			/* Pass uniforms */
			setShaderMat4(defaultShader, "modelMatrix", modelMatrix);
			setShaderMat4(defaultShader, "viewMatrix", viewMatrix);
			setShaderMat4(defaultShader, "perspectiveMatrix", perspectiveMatrix);

			/* Use VAO to remember location of vertex attributes. */
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		/* glfw: swap the double render buffer & poll IO events */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* De-allocate resources */
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	/* glfw: terminate, clears all allocated GLFW resources */
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
}

void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS) return;

	if (key == GLFW_KEY_UP) increaseTextureMix();
	else if (key == GLFW_KEY_DOWN) decreaseTextureMix();
	else if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, 1);
	else if (key == GLFW_KEY_A) moveLeft();
	else if (key == GLFW_KEY_D) moveRight();
	else if (key == GLFW_KEY_W) moveUp();
	else if (key == GLFW_KEY_S) moveDown();
	else if (key == GLFW_KEY_Q) rotateCounterClockwise();
	else if (key == GLFW_KEY_E) rotateClockwise();
	else if (key == GLFW_KEY_R) scaleUp();
	else if (key == GLFW_KEY_F) scaleDown();
}

void moveLeft()
{
	position[0] -= 0.1f;
}

void moveRight()
{
	position[0] += 0.1f;
}

void moveUp()
{
	position[1] += 0.1f;
}

void moveDown()
{
	position[1] -= 0.1f;
}

void scaleUp()
{
	scale[0] += 0.1f;
	scale[1] += 0.1f;
}

void scaleDown()
{
	scale[0] -= 0.1f;
	scale[1] -= 0.1f;
}

void rotateClockwise()
{
	rotationRadians -= (2.0f * GLM_PI) / 18.0f;
}

void rotateCounterClockwise()
{
	rotationRadians += (2.0f * GLM_PI) / 18.0f;
}

void increaseTextureMix()
{
	changeTextureMix(0.2f);
}

void decreaseTextureMix()
{
	changeTextureMix(-0.2f);
}

void changeTextureMix(float delta)
{
	textureMix += delta;
	if (textureMix > 1.0f) textureMix = 1;
	else if (textureMix < 0.0f) textureMix = 0.0f;
	setShaderFloat(defaultShader, "textureMix", textureMix);
}

