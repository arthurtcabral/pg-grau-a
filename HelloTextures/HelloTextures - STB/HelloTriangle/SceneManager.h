#pragma once

#include "Shader.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void initialize(GLuint width, GLuint height);
	void initializeGraphics();

	void addShader(string vFilename, string fFilename);

	//GLFW callbacks
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void resize(GLFWwindow* window, int width, int height);

	void do_movement();
	void render();
	void run();
	void finish();


	// scene
	void setupScene(GLfloat matrixPosition [4][2]);
	void setupCamera2D();
	void setupTexture(char* imagePath); //apenas mostra como criar uma textura
private:

	GLfloat marioX, marioY;

	GLfloat matrixPositionsMarioUp[4][2] = {
		{ 6.0f/6.0f, 2.0f/2.0f}, //top right
		{ 6.0f/6.0f, 1.0f/2.0f}, //bottom right
		{ 5.0f/6.0f, 1.0f/2.0f }, //bottom left
		{ 5.0f/6.0f, 2.0f/2.0f } //top left
	};

	GLfloat matrixPositionsMarioForward[4][2] = {
		{ 3.0f/6.0f, 1.0f/2.0f }, //top right
		{ 3.0f/6.0f, 0.0f/2.0f }, //bottom right
		{ 2.0f/6.0f, 0.0f/2.0f }, //bottom left
		{ 2.0f/6.0f, 1.0f/2.0f } //top left
	};

	GLfloat matrixPositionsMarioDown[4][2] = {
		{ 5.0f/6.0f, 1.0f/2.0f }, //top right
		{ 5.0f/6.0f, 0.0f/2.0f }, //bottom right
		{ 4.0f/6.0f, 0.0f/2.0f }, //bottom left
		{ 4.0f/6.0f, 1.0f/2.0f } //top left
	};

	//GLfloat parallaxFrontX, parallaxBackX;

	//GLfloat matrixParallaxFront[4][2] = {
	//	{ 5.0f / 6.0f, 1.0f / 2.0f }, //top right
	//	{ 5.0f / 6.0f, 0.0f / 2.0f }, //bottom right
	//	{ 4.0f / 6.0f, 0.0f / 2.0f }, //bottom left
	//	{ 4.0f / 6.0f, 1.0f / 2.0f } //top left
	//};

	//GLfloat matrixParallaxBack[4][2] = {
	//	{ 5.0f / 6.0f, 1.0f / 2.0f }, //top right
	//	{ 5.0f / 6.0f, 0.0f / 2.0f }, //bottom right
	//	{ 4.0f / 6.0f, 0.0f / 2.0f }, //bottom left
	//	{ 4.0f / 6.0f, 1.0f / 2.0f } //top left
	//};

	//GFLW window
	GLFWwindow *window;

	//our shader program
	Shader *shader;

	//scene attributes
	GLuint VAO;

	//Transformations - Model Matrix
	glm::mat4 model;

	//2D Camera - Projection matrix
	glm::mat4 projection;

	//Texture index
	unsigned int texture;

};

