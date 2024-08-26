#include "Dijkstra.hpp"

Dijkstra::Dijkstra(): costs(ROWS, std::vector<int>(COLS, INF)) {}

Dijkstra::~Dijkstra() {}

void	Dijkstra::run(Map& map)
{
	std::vector<std::pair<Coords, int> > directions{{{1, 0}, 10}, {{0, 1}, 10}, {{0, -1}, 10}, {{-1, 0}, 10}, {{1, 1}, 14}, {{1, -1}, 14}, {{-1, 1}, 14}, {{-1, -1}, 14}};

	if (!dijkstra.empty() && !endReached)
	{
		Node currNode = dijkstra.top();
		dijkstra.pop();

		for (int i = 0; i < 8; i++)
		{
			Node	next;
			next.coords.x = currNode.coords.x + directions[i].first.x;
			next.coords.y = currNode.coords.y + directions[i].first.y;
			next.cost = currNode.cost + directions[i].second;

			if (next.coords.x < COLS && next.coords.x >= 0 && next.coords.y < ROWS && next.coords.y >= 0 && map.tiles[next.coords.y][next.coords.x].type != WALL && map.tiles[next.coords.y][next.coords.x].type != START)
			{
				if (next.cost < costs[next.coords.y][next.coords.x])
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

void	Dijkstra::setStart(Coords& start)
{
	dijkstra.push((Node){0, start});
	prev[start.y][start.x] = (Coords){-1, -1};
}