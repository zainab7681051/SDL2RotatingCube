#include "screen.h"

	Screen::Screen()
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(780, 680, 0, &window, &renderer);
		SDL_RenderSetScale(renderer, 2, 2);
	}
	//stores the x-axis and y-axis floating points
	void Screen::pixel(float x, float y)
	{
		points.emplace_back(x, y);
	}
	//renders and draws
	void Screen::show() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (auto& point : points)
		{
			SDL_RenderDrawPointF(renderer, point.x, point.y);
		}
		SDL_RenderPresent(renderer);
	}

	void Screen::input()
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				exit(0);
			}
		}
	}
	//removes the rendered points
	void Screen::clear() {
		points.clear();
	}