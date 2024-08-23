#ifndef TILE_HPP
# define TILE_HPP

#include <SDL2/SDL_stdinc.h>
# include <iostream>

# include "Screen.hpp"

# define RED 0xB3001B
# define BLACK 0x262626
# define BLUE 0x255C99
# define LIGHT_BLUE 0x7EA3CC
# define TAN 0xCCAD8F
# define WHITE 0xFFFFFF
# define CREAM 0xF3E9DC

void	hexToSDL(SDL_Color& res, unsigned int color);

class Tile
{
public:
	~Tile();
	Tile();
	Tile(int x, int y);

	void	drawOutline(Screen& screen);
	void	draw(Screen& screen);
	void	animate(Screen& screen, int flag);
	void	setColor( void );

private:
	Uint32		color;
	int			type;
	int			x;
	int			y;
};

#endif