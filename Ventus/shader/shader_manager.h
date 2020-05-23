#pragma once

#include <string>

class ShaderManager {
public:
	enum ShaderType {
		DEFAULT
	};

	ShaderManager();

	static unsigned int GetShaderProgram(ShaderType type);

private:
	void BuildShaders();
	unsigned int BuildShaderProgram(const std::string& vertex_shader_path, 
		const std::string& fragment_shader_path);

	unsigned int default_shader_program_;
};