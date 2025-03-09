#ifndef MAP_HPP
# define MAP_HPP

# include <vector>
# include "../Utils.hpp"

class Screen;

struct Map
{
	std::vector<std::vector <Tile> >	tiles;
	Coords	start;
	Coords	end;

	void	drawHeader(Screen& screen);
	void	drawGrid(Screen& screen);
	void	setTile(int x, int y, Uint8 type);
	void	reset( void );
	void	clearWalls( void );
	void	randomizeWalls( void );

	Map() : tiles(ROWS, std::vector<Tile>(COLS))
	{
		start = (Coords){-1, -1};
		end = (Coords){-1, -1};
	}
};

bool	canMove(Map& map, Coords& dir, Coords& node);

#endif