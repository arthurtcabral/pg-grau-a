#pragma once

#include <iostream>

//GLAD
#include <glad/glad.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//STB
#include "stb_image.h"

class Parallax
{
public:
	Parallax();
	~Parallax();

	GLfloat width;
	GLfloat heigth;

	GLfloat positionX;
	GLfloat positionY;

	void initialize(GLfloat x, GLfloat y, GLfloat widthImage, GLfloat heightImage, char* texture);
	void render(GLint attrModel, GLint attrTexture);

private:
	glm::mat4 model;
	GLuint VAO;

	int spriteWidth;
	int spriteHeight;
	unsigned int texture;
	char* texture_file;

	void setupScene();
	void setupTexture();

};