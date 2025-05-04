#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL.h>
#include <SDL_image.h>

# define START 1
# define END 2
# define WALL 3
# define EMPTY 4
# define CLOSED 5
# define PATH 6

# define CREAM 0xFFFFEBCF
# define GREY 0xFF5F5E5D
# define RED 0xFFB3001B
# define GREEN 0xFF008000
# define BLACK 0xFF262626
# define BLUE 0xFF255C99
# define LIGHT_BLUE 0xFF7EA3CC
# define WHITE 0xFFFCFBEE
# define LIVER 0xFFC2A883
# define TAN 0xFFF1D6B0
# define DARKRED 0xFF8C3131
# define WEATH 0xFFF5E4D0
# define RICHBLACK 0xFF252325
# define SELECTED 0xFFFFF5e8
# define COLOR 0xFFeeba73
# define TEXTCOLOR 0xFF2D2D2C

# define INF INT_MAX

# define SPEED 5
# define TILE_SIZE 24
# define ROWS 40
# define COLS 72
# define HEADER_OFFSET 200
# define SCREEN_WIDTH COLS * TILE_SIZE
# define SCREEN_HEIGHT ROWS * TILE_SIZE + HEADER_OFFSET

struct	Tile
{
	Uint32	color;
	Uint32	outlineColor;
	int		type;

	Tile(): color(WHITE), outlineColor(TAN), type(EMPTY) {}
};

struct	Coords
{
	int x, y;

	bool	operator==(const Coords& other)
	{
		return (other.x == x && other.y == y);
	}

	bool	operator!=(const Coords& other)
	{
		return (other.x != x || other.y != y);
	}
};

struct	ANode
{
	int		gcost;
	int		fcost;
	Coords	coords;

	bool operator>(const ANode& other) const
	{
        return fcost > other.fcost;
	}
};

struct	DNode
{
	int		cost;
	Coords	coords;

	bool operator>(const DNode& other) const
	{
        return cost > other.cost;
	}
};

#endif