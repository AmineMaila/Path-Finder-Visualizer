#include "InputManager.hpp"
#include "Screen.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <queue>

void	hexToSDL(SDL_Color& res, unsigned int color)
{
	res.r = (color >> 16) & 0xFF;
	res.g = (color >> 8) & 0xFF;
	res.b = color & 0xFF;
	res.a = 255;
}

int main()
{
	Screen			screen;
	InputManager	in;
	Map				map;

	while (true)
	{
		if (map.bfsActivate)
			map.BFS();
		map.drawGrid(screen);
		screen.draw();
		in.input(map);
	}
}