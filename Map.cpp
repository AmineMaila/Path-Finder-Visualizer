#include "Map.hpp"
#include "Tile.hpp"
#include "Screen.hpp"
#include <SDL2/SDL_stdinc.h>
#include <cstddef>
#include <iterator>
#include <list>
#include <queue>
#include <vector>

Map::~Map() {}

Map::Map()
{
	endReached = false;
	bfsActivate = false;
	start = NULL;
	end = NULL;
	visited.fill(false);
	prev.fill(NULL);
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			tiles.push_back(Tile(j, i));
}

void	Map::clearBfs()
{
	while (bfs.size())
		bfs.pop();
}

void	Map::setType(int& x, int& y, Uint8 type)
{
	if (type == START)
	{
		if (start != NULL)
		{
			start->setType(EMPTY);
			bfs.pop();
			start = NULL;
			visited.fill(false);
		}
		start = &tiles[(y / TILE_SIZE) * COLS + (x / TILE_SIZE)];
		bfs.push(start);
		visited[(y / TILE_SIZE) * COLS + (x / TILE_SIZE)] = true;
	}
	else if (type == END)
	{
		if (end != NULL)
		{
			end->setType(EMPTY);
			end = NULL;
		}
		end = &tiles[(y / TILE_SIZE) * COLS + (x / TILE_SIZE)];
	}
	else if (type == EMPTY)
	{
		if (&tiles[(y / TILE_SIZE) * COLS + (x / TILE_SIZE)] == start)
			start = NULL;
		else if (&tiles[(y / TILE_SIZE) * COLS + (x / TILE_SIZE)] == end)
			end = NULL;
	}
	tiles[(y / TILE_SIZE) * COLS + (x / TILE_SIZE)].setType(type);
}

void	Map::reset( void )
{
	clearBfs();
	bfs.push(start);
	endReached = false;
	bfsActivate = false;
	visited.fill(false);
	prev.fill(NULL);
	for (std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		int type = it->getType();
		if (type != WALL
			&& type != START
			&& type != END)
			it->setType(EMPTY);
	}
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

std::list<Tile*>	Map::getAdj(Tile& node)
{
	std::list<Tile*>	adj;
	Coords				point = node.getCoords();

	if (point.x + 1 < COLS)
		adj.push_back(&tiles[point.y * COLS + point.x + 1]);
	if (point.y + 1 < ROWS)
		adj.push_back(&tiles[(point.y + 1) * COLS + point.x]);
	if (point.y - 1 >= 0)
		adj.push_back(&tiles[(point.y - 1) * COLS + point.x]);
	if (point.x - 1 >= 0)
		adj.push_back(&tiles[point.y * COLS + point.x - 1]);
		
	return (adj);
}

void	Map::BFSPath( void )
{
	Coords	endCoords = end->getCoords();
	int index = endCoords.y * COLS + endCoords.x;
	
	while (prev[index] != NULL)
	{
		Tile* curr = prev[index];
		index = curr->getCoords().y * COLS + curr->getCoords().x;
		if (prev[index] != NULL)
			curr->setType(PATH);
	}
}

void	Map::BFS( void )
{
	if (!bfs.empty() && !endReached)
	{
		Tile* node = bfs.front();
		std::list<Tile*> neighbours = getAdj(*node);
		for (auto& next : neighbours)
		{
			Coords	nextCoords = next->getCoords();
			if (visited[nextCoords.y * COLS + nextCoords.x] == false && next->getType() != WALL)
			{
				bfs.push(next);
				visited[nextCoords.y * COLS + nextCoords.x] = true;
				prev[nextCoords.y * COLS + nextCoords.x] = node;
				if (next == end)
				{
					endReached = true;
					break;
				}
				next->setType(CLOSED);
			}
		}
		bfs.pop();
	}
	else
	{
		BFSPath();
		bfsActivate = false;
	}

}