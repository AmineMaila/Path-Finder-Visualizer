#ifndef TILE_HPP
# define TILE_HPP

#include <SDL2/SDL_stdinc.h>
# include <iostream>

# include "Screen.hpp"
# include <list>

# define REDWOOD 0xFF8D5B4C
# define LIGHT_BLUE 0xFF7EA3CC
# define RED 0xFFB3001B
# define TAN 0xFFCCAD8F
# define BLUE 0xFF255C99
# define BLACK 0xFF262626
# define WHITE 0xFFFFFFFF
# define CREAM 0xFFF3E9DC
# define LIVER 0xFF5C4742
# define GREEN 0xFF008000

void	hexToSDL(SDL_Color& res, unsigned int color);

struct Coords
{
	int x, y;
};

class Tile
{
public:
	~Tile();
	Tile();
	Tile(int x, int y);

	void	drawOutline(Screen& screen);
	void	draw(Screen& screen);
	void	setType(Uint8 type);
	int&	getType( void );
	Coords&	getCoords( void );

private:
	Uint32		color;
	Uint32		outlineColor;
	int			type;
	Coords		p;
};

#endif