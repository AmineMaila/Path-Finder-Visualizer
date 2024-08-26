#include "InputManager.hpp"
#include "AlgoManager.hpp"
#include "Map.hpp"

InputManager::~InputManager() {}

InputManager::InputManager() : buttonLeft(false), buttonRight(false) {}

void	InputManager::input(Map& map, AlgoManager& algoManager)
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
						if (!algoManager.simulate)
							map.setTile(mouseX / TILE_SIZE, mouseY / TILE_SIZE, START);
						break;
					case SDLK_d:
						SDL_GetMouseState(&mouseX, &mouseY);
						if (!algoManager.simulate)
							map.setTile(mouseX / TILE_SIZE, mouseY / TILE_SIZE, END);
						break;
					case SDLK_r:
						map.reset();
						algoManager.reset();
						break;
					case SDLK_SPACE:
						algoManager.setStart(map.start);
						algoManager.simulate = true;
						break;
					case SDLK_RIGHT:
						if (!algoManager.simulate)
							algoManager.nextAlgo();
						break;
					case SDLK_l:
						map.randomizeWalls();
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (!algoManager.simulate)
				{
					if(ev.button.button ==  SDL_BUTTON_LEFT)
					{
						buttonLeft = true;
						map.setTile(mouseX / TILE_SIZE, mouseY / TILE_SIZE, WALL);
					}
					else
					{
						buttonRight = true;
						map.setTile(mouseX / TILE_SIZE, mouseY / TILE_SIZE, EMPTY);
					}
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
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (buttonLeft)
					map.setTile(mouseX / TILE_SIZE, mouseY / TILE_SIZE, WALL);
				else if (buttonRight)
					map.setTile(mouseX / TILE_SIZE, mouseY / TILE_SIZE, EMPTY);
				break;
		}
	}
}