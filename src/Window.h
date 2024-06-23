#pragma once

#include <SDL2/sdl.h>
#include <GL/glew.h>

#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
	Window(int _width, int _height);
	~Window();

	void Update();

	void ClearWindow()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void SwapWindows() { SDL_GL_SwapWindow(mWindow); }

	SDL_Window* GetWindow() { return mWindow; }
	
	void GetWindowSize(int& _width, int& _height) { _width = mWidth; _height = mHeight; }

private:
	SDL_Window* mWindow;
	
	int mWidth;
	int mHeight;
};

#endif // WINDOW_H