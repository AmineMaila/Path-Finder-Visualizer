#ifndef SCREEN_HPP
# define SCREEN_HPP

// # include <SDL_image.h>

# include "Button.hpp"
#include "Dijkstra.hpp"
#include "Astar.hpp"
#include "BFS.hpp"
#include "Algo.hpp"
#include "utils.hpp"
#include "Map.hpp"

class Screen
{
public:
	~Screen();
	Screen();

	void	reset( void );
	void	run(Map& map);
	void	input(Map& map);
	void	draw();
	void	setPixel(int x, int y, Uint32 color);
	void	unlock( void );
	void	lock( void );

	bool	simulate;
	bool	walls;
	bool	buttonLeft;
	bool	buttonRight;
	Coords	mouse;

private:
	Uint32				*pixels;
	int					bytesPerRow;
	SDL_Texture			*texture;
	SDL_Renderer		*renderer;
	SDL_Window			*window;
	Button				DijkstraButton;
	Button				AstarButton;
	Button				BFSButton;
	Button				ResetButton;
	Button				WallsButton;

	Algo		*algorithm;
	BFS			bfs;
	Dijkstra	dijkstra;
	Astar		aStar;
	
};

#endif