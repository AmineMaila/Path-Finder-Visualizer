#ifndef MAP_HPP
# define MAP_HPP

#include <array>
#include <queue>
# include <vector>
#include "Screen.hpp"
#include <list>

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

struct	Tile
{
	Uint32	color;
	Uint32	outlineColor;
	int		type;

	Tile(): color(CREAM), outlineColor(TAN), type(EMPTY) {}
};

class Map
{
public:
	~Map();
	Map();

	void	drawOutline(Screen& screen, Tile& tile);
	void	drawGrid(Screen& screen);

	void	setTile(int x, int y, Uint8 type);

	void	reset( void );
	void	BFS( void );
	void	BFSPath( void );
	void	clearBfs();

	bool	bfsActivate;
	bool	endReached;

private:
	std::vector<std::vector <Tile> >	tiles;
	std::pair<int, int>	start;
	std::pair<int, int>	end;

	std::queue<std::pair<int, int> >				bfs;
	std::vector<std::vector<std::pair<int, int> > >	prev;
};

#endif