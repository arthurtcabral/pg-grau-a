#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::initialize(GLfloat x, GLfloat y, GLfloat widthImage, GLfloat heightImage, GLfloat matrix[4][2], char* texture)
{
	textureFile = texture;
	positionX = x;
	positionY = y;
	width = widthImage;
	heigth = heightImage;
	matrixPositions[4][2] = matrix[4][2];

	setupScene();
	setupTexture();
}

void Character::render(GLint attrModel, GLint attrTexture)
{
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(positionX, positionY, 1.0f));
	glUniformMatrix4fv(attrModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 2);

	setupScene();

	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(attrTexture, 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Character::conflictedWith(Character character) {
	return (abs(((positionY + 0.05f) - character.positionY)) < 0.01f) &&
		(positionX <= (character.positionX + character.width)) &&
		((positionX + width) >= character.positionX);
}

void Character::setupScene()
{
	float vertices[] = {
		// positions         // texture coords
		width,  heigth, 0.0f,   matrixPositions[0][0], matrixPositions[0][1], // top right
		width, -heigth, 0.0f,   matrixPositions[1][0], matrixPositions[1][1], // bottom right
		-width, -heigth, 0.0f,  matrixPositions[2][0], matrixPositions[2][1], // bottom left
		-width,  heigth, 0.0f,  matrixPositions[3][0], matrixPositions[3][1],  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void Character::setupTexture()
{
	glGenTextures(1, &texture);	
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int nrChannels;
	unsigned char *data = stbi_load(textureFile, &spriteWidth, &spriteHeight, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spriteWidth, spriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);


}