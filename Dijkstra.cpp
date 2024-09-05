#include "Includes/Dijkstra.hpp"

Dijkstra::Dijkstra(): costs(ROWS, std::vector<int>(COLS, INF))
{
	directions = {{{1, 0}, 10}, {{0, 1}, 10}, {{0, -1}, 10}, {{-1, 0}, 10}, {{1, 1}, 14}, {{1, -1}, 14}, {{-1, 1}, 14}, {{-1, -1}, 14}};
}

Dijkstra::~Dijkstra() {}

void	Dijkstra::run(Map& map)
{
	for (int i = 0; i < SPEED; i++)
	{
		if (!dijkstra.empty() && !endReached)
		{
			DNode currNode = dijkstra.top();
			dijkstra.pop();

			for (int i = 0; i < 8; i++)
			{
				DNode	next;
				next.coords.x = currNode.coords.x + directions[i].first.x;
				next.coords.y = currNode.coords.y + directions[i].first.y;

				if (next.coords.x < COLS && next.coords.x >= 0 && next.coords.y < ROWS && next.coords.y >= 0 && map.tiles[next.coords.y][next.coords.x].type != WALL && map.tiles[next.coords.y][next.coords.x].type != START)
				{
					next.cost = currNode.cost + directions[i].second;
					if (next.cost < costs[next.coords.y][next.coords.x] && canMove(map, directions[i].first, currNode.coords))
					{
						costs[next.coords.y][next.coords.x] = next.cost;
						dijkstra.push(next);
						prev[next.coords.y][next.coords.x] = currNode.coords;
						if (next.coords.x == map.end.x && next.coords.y == map.end.y)
						{
							endReached = true;
							path(map);
							return ;
						}
						map.setTile(next.coords.x, next.coords.y, CLOSED);
					}
				}
			}
		}
	}
}

void	Dijkstra::reset( void )
{
	for (auto& row : prev)
		for (auto& prevTile : row)
				prevTile = (Coords){-2, -2};
	endReached = false;
	while (!dijkstra.empty())
		dijkstra.pop();

	for (auto& row : costs)
		for (auto& cost : row)
			cost = INF;
}

void	Dijkstra::setStart(Map& map)
{
	if (map.start.x == -1 && map.start.y == -1)
		return;
	dijkstra.push((DNode){0, map.start});
	prev[map.start.y][map.start.x] = (Coords){-1, -1};
}