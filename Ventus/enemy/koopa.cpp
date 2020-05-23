#include "koopa.h"

#include <ctime> 
#include <string>

#include "../shader/shader_manager.h"

namespace {
	const std::string texture_path_up = "textures/koopa_walk_up.png";
	const std::string texture_path_down = "textures/koopa_walk_down.png";
}

Koopa::Koopa() : Tile(ShaderManager::GetShaderProgram(ShaderManager::DEFAULT)) {
	time_ = std::time(nullptr);
	textures_.emplace_back(LoadTexture(texture_path_down));
	textures_.emplace_back(LoadTexture(texture_path_up));
}

void Koopa::Draw() {
	if (std::difftime(std::time(nullptr), time_) > 0.5) {
		time_ = std::time(nullptr);
		if (active_texture_)
			active_texture_--;
		else
			active_texture_++;
	}
	Tile::Draw();
}

unsigned int Koopa::GetActiveTexture() {
	return textures_[active_texture_];
}