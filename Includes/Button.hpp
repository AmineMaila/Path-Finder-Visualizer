#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "utils.hpp"
#include <iostream>
class Button
{
public:
	~Button() {}
	Button() : selected(false)
	{
		srect.w = 1500;
		srect.h = 420;
		srect.x = 0;
		srect.y = 0;
		drect.w = 150;
		drect.h = 42;
	}

	void	setButtonCoords(int x, int y)
	{
		drect.x = x;
		drect.y = y;
	}

	void	update(Coords& mouse)
	{
		SDL_Rect mouseRect = {mouse.x, mouse.y, 1, 1};
		if (SDL_HasIntersection(&drect, &mouseRect))
		{
			tex = texSelected;
			selected = true;
		}
		else
		{
			tex = texNotSelected;
			selected = false;
		}
	}

	bool	selected;
	SDL_Texture	*tex;
	SDL_Texture	*texNotSelected;
	SDL_Texture	*texSelected;
	SDL_Rect	srect;
	SDL_Rect	drect;
};

#endif