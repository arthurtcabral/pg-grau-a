#include <thread>
#include "SceneManager.h"
#include "Character.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;

Character *mario = new Character;
Character *up = new Character;
Character *grassFront = new Character;
Character *grass = new Character;
Character *sky = new Character;
Character *youWin = new Character;
bool hasAlreadyConflicted = false;

//GLfloat matrixPositionsMarioUp[4][2] = {
//	{ 6.0f / 6.0f, 2.0f / 2.0f }, //top right
//	{ 6.0f / 6.0f, 1.0f / 2.0f }, //bottom right
//	{ 5.0f / 6.0f, 1.0f / 2.0f }, //bottom left
//	{ 5.0f / 6.0f, 2.0f / 2.0f } //top left
//};
//
//GLfloat matrixPositionsMarioForward[4][2] = {
//	{ 3.0f / 6.0f, 1.0f / 2.0f }, //top right
//	{ 3.0f / 6.0f, 0.0f / 2.0f }, //bottom right
//	{ 2.0f / 6.0f, 0.0f / 2.0f }, //bottom left
//	{ 2.0f / 6.0f, 1.0f / 2.0f } //top left
//};
//
//GLfloat matrixPositionsMarioDown[4][2] = {
//	{ 5.0f / 6.0f, 1.0f / 2.0f }, //top right
//	{ 5.0f / 6.0f, 0.0f / 2.0f }, //bottom right
//	{ 4.0f / 6.0f, 0.0f / 2.0f }, //bottom left
//	{ 4.0f / 6.0f, 1.0f / 2.0f } //top left
//};
//
//GLfloat matrixPositions1Up[4][2] = {
//	{ 1.0f, 1.0f }, //top right
//	{ 1.0f, 0.0f }, //bottom right
//	{ 0.0f, 0.0f }, //bottom left
//	{ 0.0f, 1.0f } //top left
//};

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;
	initializeGraphics();
}

void SceneManager::initializeGraphics()
{
	glfwInit();
	window = glfwCreateWindow(width, height, "Mario Kart", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glfwSetWindowSizeCallback(window, resize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	addShader("../shaders/transformations.vs", "../shaders/transformations.frag");

	grass->initialize(-0.7f, -0.5f, 4.8f, 1.0f, "../textures/grass.png");
	up->initialize(0.9f, -0.8f, 0.1f, 0.1f, 4, "../textures/1up.png");
	mario->initialize(-0.9f, -0.8f, 0.2f, 0.2f, 2, "../textures/mariokart2.png");
	grassFront->initialize(-0.7f, -0.5f, 5.8f, 1.0f, "../textures/frontgrass.png");
	sky->initialize(-0.7f, -0.5f, 3.5f, 2.0f, "../textures/sky.png");
	youWin->initialize(-0.7f, -0.5f, 3.5f, 2.0f, "../textures/youwin.png");

	resized = true; //para entrar no setup da câmera na 1a vez

}

void SceneManager::addShader(string vFilename, string fFilename)
{
	shader = new Shader(vFilename.c_str(), fFilename.c_str());
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void SceneManager::resize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	glViewport(0, 0, width, height);
}


void SceneManager::do_movement()
{
	if (keys[GLFW_KEY_UP])
	{
		mario->spriteToRender = 1;
		mario->positionY += 0.001f;
	}

	if (keys[GLFW_KEY_DOWN]) {
		mario->spriteToRender = 3;
		mario->positionY -= 0.001f;
	}

	if (keys[GLFW_KEY_LEFT])
	{
		mario->spriteToRender = 2;
		mario->positionX -= 0.001f;
		grass->positionX += 0.00001f;
		grassFront->positionX += 0.00005f;
		sky->positionX -= 0.000005f;
		//up->positionX += 0.0005f;
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		mario->spriteToRender = 2;
		mario->positionX += 0.001f;
		grass->positionX -= 0.00001f;
		grassFront->positionX -= 0.00005f;
		sky->positionX -= 0.000005f;
		//up->positionX -= 0.0005f;
	}

	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

}

void SceneManager::render()
{
	glClearColor(0.5f, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader->Use();

	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	GLint textureLoc = glGetUniformLocation(shader->Program, "ourTexture1");

	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	sky->render(modelLoc, textureLoc);
	grass->render(modelLoc, textureLoc);
	up->render(modelLoc, textureLoc);
	mario->render(modelLoc, textureLoc);
	grassFront->render(modelLoc, textureLoc);

	if (!hasAlreadyConflicted)
	{
		if (mario->conflictedWith(*up))
		{
			numberOfUps++;
			hasAlreadyConflicted = true;
		}
	}

	if (hasAlreadyConflicted)
	{
		youWin->render(modelLoc, textureLoc);
	}
}

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		do_movement();

		render();

		glfwSwapBuffers(window);

	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void SceneManager::setupCamera2D()
{
	//corrigindo o aspecto
	float ratio;
	float xMin = -1.0, xMax = 1.0, yMin = -1.0, yMax = 1.0, zNear = -1.0, zFar = 1.0;
	if (width >= height)
	{
		ratio = width / (float)height;
		projection = glm::ortho(xMin*ratio, xMax*ratio, yMin, yMax, zNear, zFar);
	}
	else
	{
		ratio = height / (float)width;
		projection = glm::ortho(xMin, xMax, yMin*ratio, yMax*ratio, zNear, zFar);
	}

	// Get their uniform location
	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

