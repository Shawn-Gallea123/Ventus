#pragma once

#include "../tile/tile.h"

#include <time.h>

class Koopa : public Tile {
public:
	Koopa();


private:
	unsigned int GetActiveTexture() override;
	void Draw() override;

	int active_texture_ = 0;
	time_t time_;
};