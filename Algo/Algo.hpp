#ifndef ALGO_HPP
# define ALGO_HPP

#include <queue>
#include <vector>
#include "../Map/Map.hpp"
#include <climits>

// ABSTRACT CLASS ALGO
class Algo
{
public:
	virtual ~Algo(){}

	Algo() : prev(ROWS, std::vector<Coords>(COLS, {-2, -2})) /* -2, -2 -> not visited */, endReached(false) {}

	virtual void	run(Map& map) = 0;
	virtual void	setStart(Map& map) = 0;
	virtual void	reset( void ) = 0;

	void	path(Map& map)
	{
		Coords previous = prev[map.end.y][map.end.x];
		int count = 0;
		while (prev[previous.y][previous.x].x != -1 && prev[previous.y][previous.x].y != -1)
		{
			count++;
			map.setTile(previous.x, previous.y, PATH);
			previous = prev[previous.y][previous.x];
		}
	}

	std::vector<std::vector<Coords> >	prev;
	bool								endReached;
};

#endif