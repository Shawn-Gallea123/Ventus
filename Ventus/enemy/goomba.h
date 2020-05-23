#pragma once

#include "../tile/tile.h"

#include <time.h>

class Goomba : public Tile {
public:
	Goomba();

private:
	unsigned int GetActiveTexture() override;
	void Draw() override;
	void FlipTile();

	time_t time_;
};