#pragma once

#include "../tile/tile.h"

#include <time.h>

class Goomba : public Tile {
public:
	Goomba();

	void Draw() override;

private:
	void BindTexture() override;
	void FlipTile();

	time_t time_;
};