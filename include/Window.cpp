#include "Window.h"

#include <exception>

Window::Window(int _width, int _height)
{
	mWidth = _width;
	mHeight = _height;

	mWindow = SDL_CreateWindow("My Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_width, _height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(mWindow))
	{
		throw std::exception("Couldn't create SDL window.");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Couldn't initialise glew.");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Window::~Window()
{
	SDL_DestroyWindow(mWindow);
}

void Window::Update()
{
	SDL_GetWindowSize(mWindow, &mWidth, &mHeight);
	glViewport(0, 0, mWidth, mHeight);
}