#pragma once

#include <SDL2/sdl.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window(int _width, int _height);
	~Window();

	void Update();

	void ClearWindow();
	
	void SwapWindows() { SDL_GL_SwapWindow(mWindow); }

	SDL_Window* GetWindow() { return mWindow; }
	
	void GetWindowSize(int& _width, int& _height) { _width = mWidth; _height = mHeight; }

	void SetClearColour(glm::vec4 _colour);

private:
	SDL_Window* mWindow;
	
	int mWidth;
	int mHeight;

	glm::vec4 mClearColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
};