#ifndef ALGOMANAGER_HPP
#define ALGOMANAGER_HPP

#include "Astar.hpp"
#include "BFS.hpp"
#include "Dijkstra.hpp"
#include "Algo.hpp"
#include <iostream>

class AlgoManager
{
public:
	AlgoManager() : simulate(false), index(0), algorithm(&bfs) {}
	~AlgoManager() {}

	void nextAlgo( void )
	{
		index = (index + 1) % 3; // increment the divisor when adding new algorthims
		std::cout << index << std::endl;
		switch (index)
		{
			case 0:
				algorithm = &bfs;
				break;
			case 1:
				algorithm = &dijkstra;
				break;
			case 2:
				algorithm = &aStar;
				break;
		}
	}

	void	setStart(Map& map)
	{
		algorithm->setStart(map);
	}

	void	execute(Map& map)
	{
		algorithm->run(map);
	}

	void	reset( void )
	{
		simulate = false;
		algorithm->reset();
	}

	bool	simulate;

private:
	int			index;
	Algo		*algorithm;
	BFS			bfs;
	Dijkstra	dijkstra;
	Astar		aStar;
};

#endif