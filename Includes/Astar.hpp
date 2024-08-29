#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "Algo.hpp"

class Astar : public Algo
{
public:
	~Astar();
	Astar();

	virtual void run(Map& map);
	virtual void setStart(Map& map);
	virtual void reset();

	int	heuristic(Coords& node1, Coords& node2);


private:
	std::vector<std::pair<Coords, int> > directions;
	std::priority_queue<ANode, std::vector<ANode>, std::greater<ANode> >	aStar;
	std::vector<std::vector<int> >											fcosts;
};

#endif