#include "shader_manager.h"

#include <glad/glad.h>

#include <assert.h>
#include <fstream>
#include <iostream>

namespace {

ShaderManager* instance = nullptr;

}

ShaderManager::ShaderManager() {
	assert(!instance);
	BuildShaders();
	instance = this;
}

// static
unsigned int ShaderManager::GetShaderProgram(ShaderType type) {
	switch (type) {
		case DEFAULT:
			return instance->default_shader_program_;
	}
}

void ShaderManager::BuildShaders() {

	default_shader_program_ = BuildShaderProgram("shader/default_vertex_shader.vs",
		"shader/default_fragment_shader.fs");
}

unsigned int ShaderManager::BuildShaderProgram(const std::string& vertex_shader_path,
	const std::string& fragment_shader_path) {
	std::ifstream vs_file(vertex_shader_path);
	assert(vs_file);
	std::string vertex_shader_source_str((std::istreambuf_iterator<char>(vs_file)),
		std::istreambuf_iterator<char>());
	const char *vertex_shader_source = vertex_shader_source_str.c_str();
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	std::ifstream fs_file(fragment_shader_path);
	assert(fs_file);
	std::string fragment_shader_source_str((std::istreambuf_iterator<char>(fs_file)),
		std::istreambuf_iterator<char>());
	const char *fragment_shader_source = fragment_shader_source_str.c_str();
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(1);
	}

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(1);
	}

	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return shader_program;
}