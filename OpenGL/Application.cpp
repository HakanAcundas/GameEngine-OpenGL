#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include "API/VertexBuffer.h"
#include "API/VertexArray.h"
#include "res/shaders/ShadersManeger.h"
#include "res/vendor/stb_image/stb_image.h"
#include "API/TextureManager.h"
#include "res/vendor/glm/glm.hpp"
#include "res/vendor/glm/gtc/matrix_transform.hpp"
#include "res/vendor/glm/gtc/type_ptr.hpp"

#define WIDTH 860
#define HEIGHT 640

void initTest()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Error!" << std::endl;
	}
	else
	{
		std::cout << "GLFW Success!" << std::endl;
	}

	if (!glewInit())
	{
		std::cout << "GLEW Error!" << std::endl;
	}
	else
	{
		std::cout << "GLEW Success!" << std::endl;
	}
}

void windowInitTest(GLFWwindow* window)
{
	if (window == NULL)
	{
		std::cout << "Failed to initialize window!!!";
		glfwTerminate();
	}
	else
	{
		std::cout << "Window initialized successfully!!!";
	}
}

void resizeWindow(int x, int y, int width = HEIGHT, int height = HEIGHT)
{
	glViewport(x, y, width, height);
}

void handleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	};
}

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	char windowName[] = "Portal";
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, windowName, NULL, NULL);
	glfwMakeContextCurrent(window);

	float vertices[] = {
		//positions				//colors			//texture coordinates
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
		-0.5f,  0.5f ,0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f  // top left
	};

	float vertices36[] = {
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

	float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
	};

	int indices[] = {
		3,0,2,
		0,1,2
	};
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glewInit();
	glEnable(GL_DEPTH_TEST);

	VertexArray vertexArrayObject;
	VertexBuffer vertexBufferObject(sizeof(vertices), vertices);

	unsigned int elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	std::string filePath = "res/shaders/shaders.shader";
	ShaderManeger shaderManeger;
	ShaderSources shaderSources = shaderManeger.ParseShaders(filePath);
	unsigned int shaderProgram = shaderManeger.CreateShader(shaderSources.vertexSource, shaderSources.fragmentSource);

	TextureManager texture;
	std::string imagePath = "res/textures/ATAM.jpg";
	//int width, height, nrChannels;
	texture.TextureFlipVertically();
	texture.LoadTexture(imagePath, 1000, 1000, 3);
	texture.FreeImageData();
	
	glUseProgram(shaderProgram);

	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	while (!glfwWindowShouldClose(window))
	{
		handleInput(window);
		//resizeWindow();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection;
		model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(-0.2f, -0.2f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	vertexArrayObject.~VertexArray();
	vertexBufferObject.~VertexBuffer();
	glDeleteBuffers(1, &elementBuffer);
	texture.~TextureManager();
	glfwTerminate();
	return 0;
}