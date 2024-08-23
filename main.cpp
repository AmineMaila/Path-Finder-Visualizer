#include "Screen.hpp"
#include "Map.hpp"
#include <SDL2/SDL.h>

void	hexToSDL(SDL_Color& res, unsigned int color)
{
	res.r = (color >> 16) & 0xFF;
	res.g = (color >> 8) & 0xFF;
	res.b = color & 0xFF;
	res.a = 255;
}

int main()
{
	Screen	screen;
	Map		map;

	while (true)
	{
		map.drawGrid(screen);
		screen.draw();
		screen.input();
	}
}