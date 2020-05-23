#include "main.h"

#include <iostream>
#include <streambuf>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "enemy/goomba.h"
#include "enemy/koopa.h"

namespace {

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

} // namespace

Main::Main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(1920, 1080, "Super Mario Bros", glfwGetPrimaryMonitor(), NULL);
	if (window_ == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, 1920, 1080);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	
	shader_manager_ = std::make_unique<ShaderManager>();
}

void Main::ProcessInput()
{
	if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window_, true);
	} 
	else if (glfwGetKey(window_, GLFW_KEY_1) == GLFW_RELEASE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (glfwGetKey(window_, GLFW_KEY_1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void Main::Run() {
	std::unique_ptr<Tile> goomba = std::make_unique<Koopa>();

	while (!glfwWindowShouldClose(window_))
	{
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		goomba->Draw();

		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
	glfwTerminate();
}
