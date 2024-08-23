#include "Tile.hpp"
#include "Map.hpp"
#include "Screen.hpp"

Tile::~Tile() {}

Tile::Tile() : x(0), y(0) {}

Tile::Tile(int x, int y) : Tile()
{
	this->x = x;
	this->y = y;
	this->type = EMPTY;
	this->color = CREAM;
	this->outlineColor = TAN;
}

void	Tile::drawOutline(Screen& screen)
{
	for (int i = 0; i < TILE_SIZE; i++)
	{
		screen.SetPixel(x * TILE_SIZE + i, y * TILE_SIZE, outlineColor);
		screen.SetPixel(x * TILE_SIZE, y * TILE_SIZE + i, outlineColor);
		screen.SetPixel(x * TILE_SIZE + i, y * TILE_SIZE + TILE_SIZE - 1, outlineColor);
		screen.SetPixel(x * TILE_SIZE + TILE_SIZE - 1, y * TILE_SIZE + i, outlineColor);
	}
}

void	Tile::draw(Screen& screen)
{
	for (int i = 1; i < TILE_SIZE - 1; i++)
		for (int j = 1; j < TILE_SIZE - 1; j++)
			screen.SetPixel(x * TILE_SIZE + j, y * TILE_SIZE + i, color);
}

void	Tile::setType(Uint8& type)
{
	if (this->type == type)
		return;
	this->type = type;
	this->outlineColor = LIVER;
	switch (type)
	{
		case START:
			color = GREEN;
			break;
		case END:
			color = RED;
			break;
		case WALL:
			color = BLACK;
			break;
		case EMPTY:
			color = CREAM;
			outlineColor = TAN;
			break;
	}
}
