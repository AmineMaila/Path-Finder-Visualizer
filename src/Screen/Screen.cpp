#include "Screen.hpp"

Screen::Screen() : simulate(false), walls(false), buttonLeft(false), buttonRight(false), algorithm(&dijkstra)
{
	SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	DijkstraButton.texNotSelected = IMG_LoadTexture(renderer, "src/Buttons/Dijkstra.png");
	DijkstraButton.texSelected = IMG_LoadTexture(renderer, "src/Buttons/DijkstraSelected.png");
	DijkstraButton.setButtonCoords(30, 20);
	AstarButton.texNotSelected = IMG_LoadTexture(renderer, "src/Buttons/A_.png");
	AstarButton.texSelected = IMG_LoadTexture(renderer, "src/Buttons/A_Selected.png");
	AstarButton.setButtonCoords(30, 80);
	BFSButton.texNotSelected = IMG_LoadTexture(renderer, "src/Buttons/BFS.png");
	BFSButton.texSelected = IMG_LoadTexture(renderer, "src/Buttons/BFSSelected.png");
	BFSButton.setButtonCoords(200, 20);
	ResetButton.texNotSelected = IMG_LoadTexture(renderer, "src/Buttons/Reset.png");
	ResetButton.texSelected = IMG_LoadTexture(renderer, "src/Buttons/ResetSelected.png");
	ResetButton.setButtonCoords(((COLS * TILE_SIZE) / 2) + 30, 20);
	WallsButton.texNotSelected = IMG_LoadTexture(renderer, "src/Buttons/Walls.png");
	WallsButton.texSelected = IMG_LoadTexture(renderer, "src/Buttons/WallsSelected.png");
	WallsButton.setButtonCoords(((COLS * TILE_SIZE) / 2) + 30, 80);
}

Screen::~Screen()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void	Screen::lock( void )
{
	SDL_LockTexture(texture, NULL, (void**)&pixels, &bytesPerRow);
}

void Screen::setPixel(int x, int y, Uint32 color)
{
	Uint32* pixelPtr = pixels + (y * (bytesPerRow / sizeof(Uint32)) + x);
    *pixelPtr = color;
}

void	Screen::unlock()
{
	SDL_UnlockTexture(texture);
}

void Screen::draw( void )
{
	(void)mouse;
	SDL_RenderClear(renderer);
	DijkstraButton.update(mouse);
	AstarButton.update(mouse);
	BFSButton.update(mouse);
	ResetButton.update(mouse);
	WallsButton.update(mouse);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderCopy(renderer, AstarButton.tex, &AstarButton.srect, &AstarButton.drect);
	SDL_RenderCopy(renderer, BFSButton.tex, &BFSButton.srect, &BFSButton.drect);
	SDL_RenderCopy(renderer, ResetButton.tex, &ResetButton.srect, &ResetButton.drect);
	SDL_RenderCopy(renderer, WallsButton.tex, &WallsButton.srect, &WallsButton.drect);
	SDL_RenderCopy(renderer, DijkstraButton.tex, &DijkstraButton.srect, &DijkstraButton.drect);
	SDL_RenderPresent(renderer);
}

// void	Screen::genMaze( void )
// {

// }

void	Screen::reset(Map& map)
{
	simulate = false;
	map.reset();
	algorithm->reset();
}

void	Screen::run(Map& map)
{
	algorithm->run(map);
}

void	Screen::input(Map& map)
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
					case SDLK_s:
						SDL_GetMouseState(&mouse.x, &mouse.y);
						if (!simulate)
							map.setTile(mouse.x / TILE_SIZE, (mouse.y - HEADER_OFFSET) / TILE_SIZE, START);
						break;
					case SDLK_e:
						SDL_GetMouseState(&mouse.x, &mouse.y);
						if (!simulate)
							map.setTile(mouse.x / TILE_SIZE, (mouse.y - HEADER_OFFSET) / TILE_SIZE, END);
						break;
					case SDLK_BACKSPACE:
						if (!simulate)
							map.clearWalls();
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouse.x, &mouse.y);
				if (!simulate)
				{
					if(ev.button.button ==  SDL_BUTTON_LEFT)
					{
						buttonLeft = true;
						map.setTile(mouse.x / TILE_SIZE, (mouse.y - HEADER_OFFSET) / TILE_SIZE, scroll.types[scroll.index]);
					}
					else
					{
						buttonRight = true;
						map.setTile(mouse.x / TILE_SIZE, (mouse.y - HEADER_OFFSET) / TILE_SIZE, EMPTY);
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (ev.button.button)
				{
					case SDL_BUTTON_LEFT:
						if (DijkstraButton.selected && map.start != (Coords){-1, -1})
						{
							reset(map);
							dijkstra.setStart(map);
							algorithm = &dijkstra;
							simulate = true;
						}
						else if (AstarButton.selected && map.start != (Coords){-1, -1})
						{
							reset(map);
							aStar.setStart(map);
							algorithm = &aStar;
							simulate = true;
						}
						else if (BFSButton.selected && map.start != (Coords){-1, -1})
						{
							reset(map);
							bfs.setStart(map);
							algorithm = &bfs;
							simulate = true;
						}
						else if (WallsButton.selected && !simulate)
						{
							walls = !walls;
							if (walls)
								map.randomizeWalls();
							else
								map.clearWalls();

						}
						else if (ResetButton.selected)
						{
							reset(map);
						}
						buttonLeft = false;
						break;
					case SDL_BUTTON_RIGHT:
						buttonRight = false;
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse.x, &mouse.y);
				if (buttonLeft)
					map.setTile(mouse.x / TILE_SIZE, (mouse.y - HEADER_OFFSET) / TILE_SIZE, scroll.types[scroll.index]);
				break;
			case SDL_MOUSEWHEEL:
				if (ev.wheel.y < 0)
				{
					scroll.index++;
					if (scroll.index == 3)
						scroll.index = 0;
				}
				else if (ev.wheel.y > 0)
				{
					scroll.index--;
					if (scroll.index == -1)
						scroll.index = 2;
				}
				break;
		}
	}
}