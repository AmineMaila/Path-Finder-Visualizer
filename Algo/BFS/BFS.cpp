#include "BFS.hpp"

BFS::BFS()
{
	directions = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
}

BFS::~BFS() {}

void	BFS::run(Map& map)
{
	for (int i = 0; i < SPEED; i++)
	{
		if (!bfs.empty() && !endReached)
		{
			Coords currNode = bfs.front();
			bfs.pop();

			for (int i = 0; i < 4; i++)
			{
				Coords next;
				next.x = currNode.x + directions[i].x;
				next.y = currNode.y + directions[i].y;
				if (next.x < COLS && next.x >= 0 && next.y < ROWS && next.y >= 0 && prev[next.y][next.x] == (Coords){-2, -2} && map.tiles[next.y][next.x].type != WALL)
				{
					bfs.push({next.x, next.y});
					prev[next.y][next.x] = currNode;
					if (next.x == map.end.x && next.y == map.end.y)
					{
						endReached = true;
						path(map);
						return ;
					}
					map.setTile(next.x, next.y, CLOSED);
				}
			}
		}
	}
}

void	BFS::reset( void )
{
	for (auto& row : prev)
		for (auto& prevTile : row)
				prevTile = (Coords){-2, -2};
	endReached = false;
	while (!bfs.empty())
		bfs.pop();
}

void	BFS::setStart(Map& map)
{
	if (map.start.x == -1 && map.start.y == -1)
		return;
	bfs.push(map.start);
	prev[map.start.y][map.start.x] = (Coords){-1, -1};
}