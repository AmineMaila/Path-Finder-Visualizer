#include "Screen.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

Screen::Screen()
{
	SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
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

void Screen::SetPixel(int x, int y, Uint32 color)
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
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
