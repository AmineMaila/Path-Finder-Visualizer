#include "Map.hpp"
#include "Tile.hpp"
#include "Screen.hpp"
#include <vector>

Map::~Map() {}

Map::Map()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			tiles.push_back(Tile(j, i));
}

void Map::setType(int& x, int& y, Uint8 type)
{
	tiles[(y / TILE_SIZE) * COLS + (x / TILE_SIZE)].setType(type);
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