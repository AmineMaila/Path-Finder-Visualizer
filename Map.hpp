#ifndef MAP_HPP
# define MAP_HPP

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
# include <vector>
# include "Tile.hpp"

# define START 1
# define END 2
# define WALL 3
# define EMPTY 4
# define CLOSED 5

class Map
{
public:
	~Map();
	Map();

	void	drawGrid(Screen& screen);
	void	setType(int& x, int& y, Uint8 type);


private:
	// int					algoMat[ROWS][COLS];
	std::vector<Tile>	tiles;
};

#endif