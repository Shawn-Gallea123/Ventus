#include "goomba.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <ctime> 
#include <iostream>
#include <string>

#include "shader/shader_manager.h"

namespace {
	const std::string texture_path = "textures/goomba_walk.png";
}

Goomba::Goomba() : Tile(texture_path, ShaderManager::GetShaderProgram(ShaderManager::DEFAULT)) {
	time_ = std::time(nullptr);
	model_matrix_ = glm::mat4(1.0f);
}

void Goomba::Draw() {
	if (std::difftime(std::time(nullptr), time_) > 0.5) {
		FlipTile();
		time_ = std::time(nullptr);
	}
	Tile::Draw();
}

void Goomba::FlipTile() {
	glm::mat4 trans = glm::mat4(1.0f);
	trans[2][2] = 0.0f;
	trans = glm::scale(trans, glm::vec3(-1.0, 1.0, 0.0));
	model_matrix_ *= trans;
}