#include "Screen.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

void	hexToSDL(SDL_Color& res, unsigned int color)
{
	res.r = (color >> 16) & 0xFF;
	res.g = (color >> 8) & 0xFF;
	res.b = color & 0xFF;
	res.a = 255;
}

void	input(Map& map, bool& buttonLeft, bool& buttonRight)
{
	SDL_Event	ev;

	while(SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						exit(0);
						break;
				}
			case SDL_MOUSEBUTTONDOWN:
				switch (ev.button.button)
				{
					int x, y;
					case SDL_BUTTON_LEFT:
						buttonLeft = true;
						SDL_GetMouseState(&x, &y);
						map.setType(x, y, WALL);
						break;
					case SDL_BUTTON_RIGHT:
						buttonRight = true;
						SDL_GetMouseState(&x, &y);
						map.setType(x, y, EMPTY);
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (buttonLeft)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					map.setType(x, y, WALL);
				}
				else if (buttonRight)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					map.setType(x, y, EMPTY);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (ev.button.button)
				{
					case SDL_BUTTON_LEFT:
						buttonLeft = false;
						break;
					case SDL_BUTTON_RIGHT:
						buttonRight = false;
						break;
				}
				break;
		}
	}
}

int main()
{
	Screen	screen;
	Map		map;

	bool	buttonLeft = false;
	bool	buttonRight = false;

	while (true)
	{
		map.drawGrid(screen);
		screen.draw();
		input(map, buttonLeft, buttonRight);
	}
}