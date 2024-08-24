#ifndef MAP_HPP
# define MAP_HPP

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <array>
#include <queue>
# include <vector>
#include "Screen.hpp"
# include "Tile.hpp"
#include <list>

# define START 1
# define END 2
# define WALL 3
# define EMPTY 4
# define CLOSED 5
# define PATH 6

class Map
{
public:
	~Map();
	Map();

	void				drawGrid(Screen& screen);
	void				reset( void );
	void				setType(int& x, int& y, Uint8 type);
	void				BFS( void );
	void				BFSPath( void );
	void				clearBfs();
	std::list<Tile*>	getAdj(Tile& node);

	bool	bfsActivate;
	bool	endReached;

private:
	std::vector<Tile>	tiles;
	Tile				*start;
	Tile				*end;

	std::queue<Tile*>				bfs;
	std::array<Tile*, ROWS * COLS>	prev;
	std::array<bool, ROWS * COLS>	visited;
};

#endif