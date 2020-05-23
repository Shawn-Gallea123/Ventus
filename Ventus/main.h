#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "shader/shader_manager.h"

class Main {
public:
	Main();
	void Run();

private:
	void ProcessInput();

	std::unique_ptr<ShaderManager> shader_manager_;
	GLFWwindow* window_ = nullptr;
};