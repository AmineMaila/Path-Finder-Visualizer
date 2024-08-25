#include "Map.hpp"
#include "Screen.hpp"
#include <SDL2/SDL_rect.h>
#include <cstdio>
#include <iterator>
#include <utility>

Map::~Map() {}

Map::Map() : tiles(ROWS, std::vector<Tile>(COLS)), prev(ROWS, std::vector<std::pair<int, int> >(COLS, {-2, -2})) // -2, -2 -> not visited
{
	endReached = false;
	bfsActivate = false;
	start = std::make_pair(-1, -1);
	end = std::make_pair(-1, -1) ;
}

void	Map::clearBfs()
{
	while (bfs.size())
		bfs.pop();
}

void	Map::setTile(int x, int y, Uint8 type)
{
	tiles[y][x].outlineColor = LIVER;
	switch (type)
	{
		case START: // this block of code resets the previous start node so we dont have 2 start nodes
			if (start != std::make_pair(-1, -1))
			{
				prev[start.second][start.first] = std::make_pair(-2, -2);
				setTile(start.first, start.second, EMPTY);
				clearBfs();
			}
			start = std::make_pair(x, y);
			bfs.push(start);
			prev[y][x] = std::make_pair(-1, -1);
			tiles[y][x].color = GREEN;
			break;
		case END:
			if (end != std::make_pair(-1, -1))
				setTile(end.first, end.second, EMPTY);
			end = std::make_pair(x, y);
			tiles[y][x].color = RED;
			break;
		case WALL:
			tiles[y][x].color = BLACK;
			break;
		case EMPTY:
			if (std::make_pair(x, y) == start)
			{
				prev[start.second][start.first] = std::make_pair(-2, -2);
				start = std::make_pair(-1, -1);
				clearBfs();
			}
			else if (std::make_pair(x, y) == end)
				end = std::make_pair(-1, -1);
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
	for (auto& row : prev)
	{
		for (auto& prevTile : row)
		{
			if (prevTile != std::make_pair(-1, -1))
				prevTile = std::make_pair(-2, -2);
		}
	}
	clearBfs();
	bfs.push(start);
	endReached = false;
	bfsActivate = false;
	int y = 0;
	for (auto& row : tiles)
	{
		int x = 0;
		for (auto& tile : row)
		{
			if (tile.type != WALL
				&& tile.type != START
				&& tile.type != END)
				setTile(x, y, EMPTY);
			x++;
		}
		y++;
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

void	Map::BFSPath( void )
{
	std::pair<int, int> previous = prev[end.second][end.first];
	while (prev[previous.second][previous.first] != std::pair<int, int>(-1, -1))
	{
		setTile(previous.first, previous.second, PATH);
		previous = prev[previous.second][previous.first];
	}
}

void	Map::BFS( void )
{
	int	directions[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
	if (!bfs.empty() && !endReached)
	{
		int nodeX = bfs.front().first;
		int nodeY = bfs.front().second;

		for (int i = 0; i < 4; i++)
		{
			int newx = nodeX + directions[i][0];
			int newy = nodeY + directions[i][1];
			if (newx < COLS && newx >= 0 && newy < ROWS && newy >= 0 && prev[newy][newx] == std::make_pair(-2, -2) && tiles[newy][newx].type != WALL )
			{
				bfs.push({newx, newy});
				prev[newy][newx] = {nodeX, nodeY};
				if (newx == end.first && newy == end.second)
				{
					endReached = true;
					BFSPath();
					return ;
				}
				setTile(newx, newy, CLOSED);
			}
		}
		bfs.pop();
	}
	else
		bfsActivate = false;

}