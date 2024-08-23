#include "Map.hpp"
#include "Tile.hpp"
#include "Screen.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <vector>

Map::~Map() {}

Map::Map()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			tiles.push_back(Tile(j, i));
}

void Map::drawGrid( Screen& screen )
{
	screen.lock();
	for (auto& tile : tiles)
	{
		tile.drawOutline(screen);
		tile.draw(screen);
	}
	screen.unlock();
}