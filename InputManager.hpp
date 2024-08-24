#ifndef INPUTMANAGER_HPP
# define INPUTMANAGER_HPP

#include "Map.hpp"
#include "SDL2/SDL.h"

class InputManager
{
public:
	~InputManager();
	InputManager();

	void	input(Map& map);

private:
	bool	buttonLeft;
	bool	buttonRight;
	int		mouseX;
	int		mouseY;
};

#endif