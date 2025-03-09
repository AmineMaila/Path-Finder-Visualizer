#include "Astar.hpp"

Astar::~Astar() {}

Astar::Astar(): fcosts(ROWS, std::vector<int>(COLS, INF))
{
	directions = {{{1, 0}, 10}, {{0, 1}, 10}, {{0, -1}, 10}, {{-1, 0}, 10}, {{1, 1}, 14}, {{1, -1}, 14}, {{-1, 1}, 14}, {{-1, -1}, 14}};
}


int	Astar::heuristic(Coords& node1, Coords& node2)
{
	return ((abs(node1.x - node2.x) + abs(node1.y - node2.y)) * 7); // multiplied by 7 so the calculation doesn't overshoot the hypothetical distance (note : this is necessary because the heuristic is calculated with manhaten distance)
}

void	Astar::run(Map& map)
{
	for (int i = 0; i < SPEED; i++)
	{
		if (!aStar.empty() && !endReached)
		{
			ANode currNode = aStar.top();
			aStar.pop();

			for (int i = 0; i < 8; i++)
			{
				ANode	next;
				next.coords.x = currNode.coords.x + directions[i].first.x;
				next.coords.y = currNode.coords.y + directions[i].first.y;

				if (next.coords.x < COLS && next.coords.x >= 0 && next.coords.y < ROWS && next.coords.y >= 0 && map.tiles[next.coords.y][next.coords.x].type != WALL && map.tiles[next.coords.y][next.coords.x].type != START)
				{
					next.gcost = currNode.gcost + directions[i].second;
					next.fcost = next.gcost + heuristic(next.coords, map.end);
					if (next.fcost < fcosts[next.coords.y][next.coords.x] && canMove(map, directions[i].first, currNode.coords))
					{
						fcosts[next.coords.y][next.coords.x] = next.fcost;
						aStar.push(next);
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

void	Astar::reset( void )
{
	for (auto& row : prev)
		for (auto& prevTile : row)
				prevTile = (Coords){-2, -2};
	endReached = false;
	while (!aStar.empty())
		aStar.pop();

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			fcosts[i][j] = INF;
}

void	Astar::setStart(Map& map)
{
	if (map.start.x == -1 && map.start.y == -1)
		return;
	aStar.push((ANode){0, heuristic(map.start, map.end), map.start});
	prev[map.start.y][map.start.x] = (Coords){-1, -1};
}