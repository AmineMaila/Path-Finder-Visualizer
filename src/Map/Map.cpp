#include "Map.hpp"
#include "../Screen/Screen.hpp"
#include "../Utils.hpp"
#include <cstdlib>
#include <ctime>

void	Map::setTile(int x, int y, Uint8 type)
{
	if (x >= COLS || x < 0 || y >= ROWS || y < 0)
		return ;
	tiles[y][x].outlineColor = LIVER;
	switch (type)
	{
		case START:
			if (start.x != -1 && start.y != -1)
				setTile(start.x, start.y, EMPTY);
			if (x == end.x && y == end.y)
				end = (Coords){-1, -1};
			start = (Coords){x, y};
			tiles[y][x].color = GREEN;
			break;
		case END:
			if (end.x != -1 && end.y != -1)
				setTile(end.x, end.y, EMPTY);
			if(x == start.x && y == start.y)
				start = (Coords){-1, -1};
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
			tiles[y][x].color = WHITE;
			tiles[y][x].outlineColor = TAN;
			break;
		case PATH:
			tiles[y][x].color = BLUE;
			tiles[y][x].outlineColor = BLUE;
			break;
		case CLOSED:
			tiles[y][x].color = LIGHT_BLUE;
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

void	Map::drawHeader(Screen& screen)
{
	int middle = (COLS * TILE_SIZE) / 2;
	for (int i = 0; i < HEADER_OFFSET - 2; i++)
		for (int j = 0; j < COLS * TILE_SIZE; j++)
			screen.setPixel(j, i, TAN);
	for (int i = 20; i < HEADER_OFFSET - 20; i++)
		screen.setPixel(middle, i, COLOR);
	for (int i = HEADER_OFFSET - 2; i < HEADER_OFFSET; i++)
		for (int j = 0; j < COLS * TILE_SIZE; j++)
			screen.setPixel(j, i, TAN);
}

void Map::drawGrid( Screen& screen )
{
	screen.lock();
	drawHeader(screen);
	int y = HEADER_OFFSET;
	for (auto& row : tiles)
	{
		int x = 0;
		for (auto& tile : row)
		{
			// draws outline
			for (int i = 0; i < TILE_SIZE; i++)
			{
				screen.setPixel(x + i, y, tile.outlineColor);
				screen.setPixel(x, y + i, tile.outlineColor);
				screen.setPixel(x + i, y + TILE_SIZE - 1, tile.outlineColor);
				screen.setPixel(x + TILE_SIZE - 1, y + i, tile.outlineColor);
			}
			// fills cell
			for (int i = 1; i < TILE_SIZE - 1; i++)
				for (int j = 1; j < TILE_SIZE - 1; j++)
					screen.setPixel(x + j, y + i, tile.color);;
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	screen.unlock();
}

void	Map::clearWalls( void )
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			if (tiles[i][j].type == WALL)
				setTile(j, i, EMPTY);
}

void	Map::randomizeWalls( void )
{
	clearWalls();
	std::srand(std::time(0));
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			if (std::rand() % 4 == 0 && tiles[i][j].type != START && tiles[i][j].type != END)
				setTile(j, i, WALL);
}

bool	canMove(Map& map, Coords& dir, Coords& node) // this function prevent the algo to move through walls diagonally
{
	if (dir.x + node.x != node.x && dir.y + node.y != node.y)
		if (map.tiles[node.y + dir.y][node.x].type == WALL && map.tiles[node.y][node.x + dir.x].type == WALL)
			return (false);
	return (true);
}