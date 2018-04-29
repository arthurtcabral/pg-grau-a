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

	int spriteToRender;

	//Parallax
	void initialize(GLfloat x, GLfloat y, GLfloat widthImage, GLfloat heightImage, char* texture);

	//Characer - spriteToRender: 1 - MarioUp | 2 - MarioForward | 3 - MarioDown | 4 - 1UP
	void initialize(GLfloat x, GLfloat y, GLfloat widthImage, GLfloat heightImage, int spt, char* texture);
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