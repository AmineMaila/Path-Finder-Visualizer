#ifndef MAP_HPP
# define MAP_HPP

#include <SDL2/SDL_pixels.h>
# include <vector>
# include "Tile.hpp"

# define START 5
# define END 6
# define WALL 7
# define EMPTY 8

class Map
{
public:
	~Map();
	Map();

	void	drawGrid(Screen& screen);


private:
	// int					algoMat[ROWS][COLS];
	std::vector<Tile>	tiles;
};

#endif