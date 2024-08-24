#include "Tile.hpp"
#include "Map.hpp"
#include "Screen.hpp"

Tile::~Tile() {}

Tile::Tile() 
{
	p.x = 0;
	p.y = 0;
}

Tile::Tile(int x, int y)
{
	this->p.x = x;
	this->p.y = y;
	this->type = EMPTY;
	this->color = CREAM;
	this->outlineColor = TAN;
}

Coords&	Tile::getCoords( void )
{
	return (p);
}

void	Tile::drawOutline(Screen& screen)
{
	for (int i = 0; i < TILE_SIZE; i++)
	{
		screen.SetPixel(p.x * TILE_SIZE + i, p.y * TILE_SIZE, outlineColor);
		screen.SetPixel(p.x * TILE_SIZE, p.y * TILE_SIZE + i, outlineColor);
		screen.SetPixel(p.x * TILE_SIZE + i, p.y * TILE_SIZE + TILE_SIZE - 1, outlineColor);
		screen.SetPixel(p.x * TILE_SIZE + TILE_SIZE - 1, p.y * TILE_SIZE + i, outlineColor);
	}
}

void	Tile::draw(Screen& screen)
{
	for (int i = 1; i < TILE_SIZE - 1; i++)
		for (int j = 1; j < TILE_SIZE - 1; j++)
			screen.SetPixel(p.x * TILE_SIZE + j, p.y * TILE_SIZE + i, color);;
}

int&	Tile::getType( void )
{
	return (type);
}

void	Tile::setType(Uint8 type)
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
		case CLOSED:
			color = LIGHT_BLUE;
			break;
		case PATH:
			color = BLUE;
			break;
	}
}
