#ifndef INPUTMANAGER_HPP
# define INPUTMANAGER_HPP

#include "AlgoManager.hpp"
#include "Map.hpp"
#include "SDL2/SDL.h"

class InputManager
{
public:
	~InputManager();
	InputManager();

	void	input(Map& map, AlgoManager& algoManager);

private:
	bool	buttonLeft;
	bool	buttonRight;
	int		mouseX;
	int		mouseY;
};

#endif