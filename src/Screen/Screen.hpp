#ifndef SCREEN_HPP
# define SCREEN_HPP

# include "Button.hpp"
# include "../Algo/Dijkstra/Dijkstra.hpp"
# include "../Algo/Astar/Astar.hpp"
# include "../Algo/BFS/BFS.hpp"
# include "../Algo/Algo.hpp"

struct Scroll
{
	Uint32	types[3] = {START, END, WALL};
	int		index;

	Scroll() : index(2) {}
};

class Screen
{
public:
	~Screen();
	Screen();

	void	reset(Map& map);
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
	Scroll	scroll;

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
