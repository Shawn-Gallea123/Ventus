#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Tile {
public:
	explicit Tile(const unsigned int shader_program);

	virtual void Draw();

protected:
	unsigned int LoadTexture(const std::string& texture_path);

	glm::mat4 model_matrix_;
	glm::mat4 view_matrix_;
	const unsigned int shader_program_;
	std::vector<unsigned int> textures_;

private:
	void Init();
	virtual unsigned int GetActiveTexture() = 0;

	unsigned int vao_;
	unsigned int vbo_;
	unsigned int ebo_;
};