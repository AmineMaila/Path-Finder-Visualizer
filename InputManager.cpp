#include "InputManager.hpp"
#include "Map.hpp"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

InputManager::~InputManager() {}

InputManager::InputManager() : buttonLeft(false), buttonRight(false) {}

void	InputManager::input(Map& map)
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
					case SDLK_a:
						SDL_GetMouseState(&mouseX, &mouseY);
						map.setType(mouseX, mouseY, START);
						break;
					case SDLK_d:
						SDL_GetMouseState(&mouseX, &mouseY);
						map.setType(mouseX, mouseY, END);
						break;
					case SDLK_SPACE:
						map.bfsActivate = !map.bfsActivate;
				}
			case SDL_MOUSEBUTTONDOWN:
				switch (ev.button.button)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					case SDL_BUTTON_LEFT:
						buttonLeft = true;
						map.setType(mouseX, mouseY, WALL);
						break;
					case SDL_BUTTON_RIGHT:
						buttonRight = true;
						map.setType(mouseX, mouseY, EMPTY);
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (buttonLeft)
					map.setType(mouseX, mouseY, WALL);
				else if (buttonRight)
					map.setType(mouseX, mouseY, EMPTY);
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