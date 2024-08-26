#ifndef ALGO_HPP
# define ALGO_HPP

#include <queue>
#include <vector>
#include "Screen.hpp"
#include "Map.hpp"

# define START 1
# define END 2
# define WALL 3
# define EMPTY 4
# define CLOSED 5
# define PATH 6

# define REDWOOD 0xFF7B68EE
# define RED 0xFFB3001B
# define WHITE 0xFFFFFFFF
# define GREEN 0xFF008000
# define BLACK 0xFF262626
# define BLUE 0xFF255C99
# define LIGHT_BLUE 0xFF7EA3CC
# define CREAM 0xFFF3E9DC
# define LIVER 0xFFC2A883
# define TAN 0xFFF1D6B0

struct	Node
{
	int		cost;
	Coords	coords;

	bool operator>(const Node& other) const
	{
        return cost > other.cost;
	}
};

// ABSTRACT CLASS ALGO
class Algo
{
public:
	virtual ~Algo(){}

	Algo() : prev(ROWS, std::vector<Coords>(COLS, {-2, -2})) /* -2, -2 -> not visited */, endReached(false) {}

	virtual void	run(Map& map) = 0;
	virtual void	setStart(Coords& start) = 0;
	virtual void	reset( void ) = 0;

	void	path(Map& map)
	{
		Coords previous = prev[map.end.y][map.end.x];
		while (prev[previous.y][previous.x].x != -1 && prev[previous.y][previous.x].y != -1)
		{
			map.setTile(previous.x, previous.y, PATH);
			previous = prev[previous.y][previous.x];
		}
	}

	std::vector<std::vector<Coords> >	prev;
	bool								endReached;
};

#endif