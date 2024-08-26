#ifndef SCREEN_HPP
# define SCREEN_HPP

# include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
# include <vector>

# define TILE_SIZE 24

# define ROWS 32
# define COLS 55

# define SCREEN_WIDTH COLS * TILE_SIZE
# define SCREEN_HEIGHT ROWS * TILE_SIZE

struct	point
{
	SDL_Point	p;
	SDL_Color	color;
};

class Screen
{
public:
	~Screen();
	Screen();

	void	draw( void );
	void	SetPixel(int x, int y, Uint32 color);
	void	unlock( void );
	void	lock( void );

private:
	Uint32				*pixels;
	int					bytesPerRow;
	SDL_Texture			*texture;
	SDL_Renderer		*renderer;
	SDL_Window			*window;
	
};

#endif