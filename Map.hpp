#ifndef MAP_HPP
# define MAP_HPP

# include <vector>
#include <iostream>
#include "Screen.hpp"

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

#define INF INT_MAX

struct	Tile
{
	Uint32	color;
	Uint32	outlineColor;
	int		type;

	Tile(): color(CREAM), outlineColor(TAN), type(EMPTY) {}
};

struct	Coords
{
	int x, y;
};

struct Map
{
	std::vector<std::vector <Tile> >	tiles;
	Coords	start;
	Coords	end;

	void	drawOutline(Screen& screen, Tile& tile);
	void	drawGrid(Screen& screen);
	void	setTile(int x, int y, Uint8 type);
	void	reset( void );
	void	randomizeWalls( void );

	Map() : tiles(ROWS, std::vector<Tile>(COLS))
	{
		start = (Coords){-1, -1};
		end = (Coords){-1, -1};
	}
};

bool	canMove(Map& map, Coords& dir, Coords& node);

#endif