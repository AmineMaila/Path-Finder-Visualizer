#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../Algo.hpp"

class Dijkstra : public Algo
{
public:
	Dijkstra();
	~Dijkstra();

	virtual void	run(Map& map);
	virtual void	setStart(Map& map);
	virtual void	reset( void );

private:
	std::vector<std::pair<Coords, int> > directions;
	std::priority_queue<DNode, std::vector<DNode>, std::greater<DNode> >	dijkstra;
	std::vector<std::vector<int> >										costs;
};

#endif