#include "Map.hpp"
#include "Screen.hpp"
#include <cstdlib>

void	Map::setTile(int x, int y, Uint8 type)
{
	tiles[y][x].outlineColor = LIVER;
	switch (type)
	{
		case START:
			if (start.x != -1 && start.y != -1)
				setTile(start.x, start.y, EMPTY);
			start = (Coords){x, y};
			tiles[y][x].color = GREEN;
			break;
		case END:
			if (end.x != -1 && end.y != -1)
				setTile(end.x, end.y, EMPTY);
			end = (Coords){x, y};
			tiles[y][x].color = RED;
			break;
		case WALL:
			tiles[y][x].color = BLACK;
			break;
		case EMPTY:
			if (x == start.x && y == start.y)
				start = (Coords){-1, -1};
			else if (x == end.x && y == end.y)
				end = (Coords){-1, -1};
			tiles[y][x].color = CREAM;
			tiles[y][x].outlineColor = TAN;
			break;
		case CLOSED:
			tiles[y][x].color = LIGHT_BLUE;
			break;
		case PATH:
			tiles[y][x].color = BLUE;
			tiles[y][x].outlineColor = BLUE;
			break;
	}
	tiles[y][x].type = type;
}

void	Map::reset( void )
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (tiles[i][j].type != WALL
				&& tiles[i][j].type != START
				&& tiles[i][j].type != END)
				setTile(j, i, EMPTY);
		}
	}
}

void Map::drawGrid( Screen& screen )
{
	screen.lock();
	int y = 0;
	for (auto& row : tiles)
	{
		int x = 0;
		for (auto& tile : row)
		{
			// draws outline
			for (int i = 0; i < TILE_SIZE; i++)
			{
				screen.SetPixel(x + i, y, tile.outlineColor);
				screen.SetPixel(x, y + i, tile.outlineColor);
				screen.SetPixel(x + i, y + TILE_SIZE - 1, tile.outlineColor);
				screen.SetPixel(x + TILE_SIZE - 1, y + i, tile.outlineColor);
			}
			// fills cell
			for (int i = 1; i < TILE_SIZE - 1; i++)
				for (int j = 1; j < TILE_SIZE - 1; j++)
					screen.SetPixel(x + j, y + i, tile.color);;
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	screen.unlock();
}

void Map::randomizeWalls( void )
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			if (tiles[i][j].type == WALL)
				setTile(j, i, EMPTY);
	std::srand(std::time(0));
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			if (std::rand() % 4 == 0 && tiles[i][j].type != START && tiles[i][j].type != END)
				setTile(j, i, WALL);
}