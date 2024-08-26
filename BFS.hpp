#ifndef BFS_HPP
# define BFS_HPP

#include "Algo.hpp"

class BFS : public Algo
{
public:
	BFS();
	~BFS();

	virtual void	run(Map& map);
	virtual void	setStart(Coords& start);
	virtual void	reset( void );

private:
	std::queue<Coords>	bfs;

};

#endif