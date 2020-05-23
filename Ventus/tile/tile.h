#pragma once

#include <glm/glm.hpp>
#include <string>

class Tile {
public:
	explicit Tile(const std::string& texture_path, const unsigned int shader_program);

	virtual void Draw();

protected:
	glm::mat4 model_matrix_;
	glm::mat4 view_matrix_;
	const unsigned int shader_program_;

private:
	void Init(const std::string& texture_path);

	unsigned int vao_;
	unsigned int vbo_;
	unsigned int ebo_;
	unsigned int texture_;
};