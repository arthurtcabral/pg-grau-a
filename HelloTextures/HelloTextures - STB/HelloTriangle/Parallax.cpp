#include "Parallax.h"

Parallax::Parallax()
{
}
Parallax::~Parallax()
{
}
void Parallax::initialize(GLfloat x, GLfloat y, GLfloat widthImage, GLfloat heightImage, char* texture)
{
	texture_file = texture;
	positionX = x;
	positionY = y;
	width = widthImage;
	heigth = heightImage;

	setupScene();
	setupTexture();
}
void Parallax::render(GLint attrModel, GLint attrTexture) {

	model = glm::mat4();

	glUniformMatrix4fv(attrModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 2);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(attrTexture, 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Parallax::setupScene()
{
	float vertices[] = {
		// positions         // texture coords
		positionX + width, positionY + heigth, 0.0f,   1.0f, 1.0f, // top right
		positionX + width, positionY, 0.0f,   1.0f, 0.0f, // bottom right
		positionX, positionY, 0.0f,  0.0f, 0.0f, // bottom left
		positionX, positionY + heigth, 0.0f,  0.0f, 1.0f  // top left 
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

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}
void Parallax::setupTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int nrChannels, spriteWidth, spriteHeight;
	unsigned char *data = stbi_load(texture_file, &spriteWidth, &spriteHeight, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, spriteWidth, spriteHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
