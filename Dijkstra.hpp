#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "Algo.hpp"

class Dijkstra : public Algo
{
public:
	Dijkstra();
	~Dijkstra();

	virtual void	run(Map& map);
	virtual void	setStart(Coords& start);
	virtual void	reset( void );

private:
	std::priority_queue<Node, std::vector<Node>, std::greater<Node> >	dijkstra;
	std::vector<std::vector<int> >										costs;
};

#endif