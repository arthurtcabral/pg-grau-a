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

class Character
{
public:
	Character();
	~Character();

	GLfloat width;
	GLfloat heigth;

	GLfloat positionX;
	GLfloat positionY;

	GLfloat matrixPositions[4][2];

	void initialize(GLfloat x, GLfloat y, GLfloat widthImage, GLfloat heightImage, GLfloat matrix[4][2], char* texture);
	void render(GLint attrModel, GLint attrTexture);
	bool conflictedWith(Character character);

private:
	glm::mat4 model;
	GLuint VAO;

	int spriteWidth;
	int spriteHeight;
	unsigned int texture;
	char* textureFile;

	void setupScene();
	void setupTexture();
};