#include "BFS.hpp"

BFS::BFS() {}

BFS::~BFS() {}

void	BFS::run(Map& map)
{
	int	directions[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
	if (!bfs.empty() && !endReached)
	{
		Coords node = bfs.front();
		bfs.pop();

		for (int i = 0; i < 4; i++)
		{
			Coords next;
			next.x = node.x + directions[i][0];
			next.y = node.y + directions[i][1];
			if (next.x < COLS && next.x >= 0 && next.y < ROWS && next.y >= 0 && prev[next.y][next.x].x == -2 && prev[next.y][next.x].y == -2 && map.tiles[next.y][next.x].type != WALL)
			{
				bfs.push({next.x, next.y});
				prev[next.y][next.x] = node;
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