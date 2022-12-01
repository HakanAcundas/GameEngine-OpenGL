#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include "API/VertexBuffer.h"
#include "API/VertexArray.h"
#include "res/shaders/ShadersManeger.h"
#include "res/vendor/stb_image/stb_image.h"
#include "API/Texture.h"
#include "API/Camera.h"
#include "res/vendor/imgui/imgui.h"
#include "res/vendor/imgui/imgui_impl_glfw.h"
#include "res/vendor/imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#define WIDTH 1920
#define HEIGHT 1080

//need for ImGui initilization
const char* glsl_version = "#version 130";

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
bool isCursorCameraMovement = true;

//Timer normalizers
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void resizeWindow(int x, int y, int width = HEIGHT, int height = HEIGHT);

void processInput(GLFWwindow* window);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	char windowName[] = "Portal";
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, windowName, glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float verticesBasic[] = {
		//positions				//colors			//texture coordinates
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
		-0.5f,  0.5f ,0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f  // top left
	};

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	//For 10 cube spawn
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	int indices[] = {
		3,0,2,
		0,1,2
	};
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glewInit();
	glEnable(GL_DEPTH_TEST);

	VertexBuffer vertexBufferObject(sizeof(vertices), vertices);

	/*unsigned int elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	VertexArray vertexArrayObject;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	VertexArray vertexArrayLightObject;
	vertexBufferObject.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//Shader Resourece File Paths
	std::string filePathCube = "res/shaders/multipleLights.shader";
	std::string filePathLamp = "res/shaders/lamp.shader";

	//Shader Manager
	ShaderManeger shaderManeger;

	//Shader Cube
	ShaderSources shaderSources = shaderManeger.ParseShaders(filePathCube);
	unsigned int shaderProgramCube = shaderManeger.CreateShader(shaderSources.vertexSource, shaderSources.fragmentSource);

	//Shader Lamp
	ShaderSources shaderSourcesLamp = shaderManeger.ParseShaders(filePathLamp);
	unsigned int shaderProgramLamp = shaderManeger.CreateShader(shaderSourcesLamp.vertexSource, shaderSourcesLamp.fragmentSource);

	//Wall Brick Textures
	Texture cube;
	std::string imagePath = "res/textures/container2.png";
	cube.TextureFlipVertically();
	cube.LoadTexture(imagePath, 500, 500);

	Texture textureSpecular;
	std::string imagePath1 = "res/textures/container2_specular.png";
	textureSpecular.TextureFlipVertically();
	textureSpecular.LoadTexture(imagePath1, 500, 500);

	shaderManeger.Use(shaderProgramCube);
	shaderManeger.SetInt(shaderProgramCube, "material.diffuse", 0);
	shaderManeger.SetInt(shaderProgramCube, "material.specular", 1);

	//ImGui initilizers
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	ImVec4 backGroundColor = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui Part START
		{
			static int counter = 0;

			ImGui::Begin("Flat Engine"); // Create a window called "Flat Engine" and append into it.
			   
			ImGui::Text("BACKGROUND SETTINGS");
			//ImGui::SliderFloat("Transperancy: ", &backGroundColorRed, backGroundColorGreen, backGroundColorBlue); // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("Background color", (float*)&backGroundColor); // Edit 3 floats representing a color

			if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		//ImGui Part END

		processInput(window);

		//resizeWindow();
		glClearColor(backGroundColor.x, backGroundColor.y, backGroundColor.z, backGroundColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Render Cube Uniforms
		shaderManeger.Use(shaderProgramCube);

		shaderManeger.SetVec3(shaderProgramCube, "viewPosition", camera.Position);
		shaderManeger.SetFloat(shaderProgramCube, "material.shininess", 32.0f);

		/*
		  Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		  the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		  by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		  by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
	   */
	   // directional light
		shaderManeger.SetVec3(shaderProgramCube, "dirLight.direction", -0.2f, -1.0f, -0.3f);
		shaderManeger.SetVec3(shaderProgramCube, "dirLight.ambient", 0.05f, 0.05f, 0.05f);
		shaderManeger.SetVec3(shaderProgramCube, "dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		shaderManeger.SetVec3(shaderProgramCube, "dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[0].position", pointLightPositions[0]);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[0].constant", 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[0].linear", 0.09f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[0].quadratic", 0.032f);
		// point light 2
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[1].position", pointLightPositions[1]);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[1].constant", 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[1].linear", 0.09f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[1].quadratic", 0.032f);
		// point light 3
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[2].position", pointLightPositions[2]);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[2].constant", 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[2].linear", 0.09f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[2].quadratic", 0.032f);
		// point light 4
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[3].position", pointLightPositions[3]);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		shaderManeger.SetVec3(shaderProgramCube, "pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[3].constant", 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[3].linear", 0.09f);
		shaderManeger.SetFloat(shaderProgramCube, "pointLights[3].quadratic", 0.032f);
		// spotLight
		shaderManeger.SetVec3(shaderProgramCube, "spotLight.position", camera.Position);
		shaderManeger.SetVec3(shaderProgramCube, "spotLight.direction", camera.Front);
		shaderManeger.SetVec3(shaderProgramCube, "spotLight.ambient", 0.0f, 0.0f, 0.0f);
		shaderManeger.SetVec3(shaderProgramCube, "spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		shaderManeger.SetVec3(shaderProgramCube, "spotLight.specular", 1.0f, 1.0f, 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "spotLight.constant", 1.0f);
		shaderManeger.SetFloat(shaderProgramCube, "spotLight.linear", 0.09f);
		shaderManeger.SetFloat(shaderProgramCube, "spotLight.quadratic", 0.032f);
		shaderManeger.SetFloat(shaderProgramCube, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		shaderManeger.SetFloat(shaderProgramCube, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	

		//Cube Object ambient, diffuse, specular and shineness values initilazation
		shaderManeger.SetFloat(shaderProgramCube, "material.shininess", 32.0f);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		shaderManeger.SetMat4(shaderProgramCube, "projection", projection);

		glm::mat4 view = camera.GetViewMatrix(); // make sure to initialize matrix to identity matrix first
		shaderManeger.SetMat4(shaderProgramCube, "view", view);

		glm::mat4 model = glm::mat4(1.0f);
		shaderManeger.SetMat4(shaderProgramCube, "model", model);

		glActiveTexture(GL_TEXTURE0);
		cube.Bind();
		glActiveTexture(GL_TEXTURE1);
		textureSpecular.Bind();

		vertexArrayObject.Bind();
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shaderManeger.SetMat4(shaderProgramCube, "model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//Render Lamp Cubes
		shaderManeger.Use(shaderProgramLamp);

		shaderManeger.SetMat4(shaderProgramLamp, "projectionLamp", projection);
		shaderManeger.SetMat4(shaderProgramLamp, "viewLamp", view);

		vertexArrayLightObject.Bind();

		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			shaderManeger.SetMat4(shaderProgramLamp, "modelLamp", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	vertexArrayObject.~VertexArray();
	vertexArrayLightObject.~VertexArray();
	vertexBufferObject.~VertexBuffer();
	//glDeleteBuffers(1, &elementBuffer);
	cube.~Texture();
	textureSpecular.~Texture();
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	glfwTerminate();
	return 0;
}

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

void resizeWindow(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		//Disable camera movement with mouse
		if (isCursorCameraMovement == true)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isCursorCameraMovement = false;
		}
		//Anable camera movement with mouse
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			isCursorCameraMovement = true;
			firstMouse = true;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn )
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if(isCursorCameraMovement)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}