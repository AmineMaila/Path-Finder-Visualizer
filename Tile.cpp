#include "Tile.hpp"
#include "Map.hpp"
#include "Screen.hpp"
#include <SDL2/SDL_pixels.h>

Tile::~Tile() {}

Tile::Tile() : x(0), y(0) {}

Tile::Tile(int x, int y) : Tile()
{
	this->x = x;
	this->y = y;
	this->type = EMPTY;
	this->color = CREAM;
}

void	Tile::drawOutline(Screen& screen)
{
	for (int i = 0; i < TILE_SIZE; i++)
	{
		screen.SetPixel(x * TILE_SIZE + i, y * TILE_SIZE, BLACK);
		screen.SetPixel(x * TILE_SIZE, y * TILE_SIZE + i, BLACK);
		screen.SetPixel(x * TILE_SIZE + i, y * TILE_SIZE + TILE_SIZE - 1, BLACK);
		screen.SetPixel(x * TILE_SIZE + TILE_SIZE - 1, y * TILE_SIZE + i, BLACK);
	}
}

void	Tile::draw(Screen& screen)
{
	for (int i = 1; i < TILE_SIZE - 1; i++)
		for (int j = 1; j < TILE_SIZE - 1; j++)
			screen.SetPixel(x * TILE_SIZE + j, y * TILE_SIZE + i, color);
}

void	Tile::setColor( void )
{
	if (type == START)
		color = BLUE;
	else if (type == END)
		color = RED;
	else if (type == WALL)
		color = BLACK;
	else if (type == EMPTY)
		color = CREAM;
}

// void	Tile::animate(Screen& screen)
// {

// }