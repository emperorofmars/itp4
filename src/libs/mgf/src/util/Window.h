/*
**	Author:		Martin Schwarz
**	Name:		Window.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_WINDOW_H
#define MGF_WINDOW_H

#include "../Include.h"

namespace mgf{

class Window{
public:
	Window(const std::string &name, unsigned int w = 800, unsigned int h = 600, bool fullscreen = 0,
			unsigned int monitor = 0, bool inputGrabbed = 0, bool vsync = 0);
	~Window();

	//int setup(unsigned int w = 800, unsigned int h = 600, bool fullscreen = 0,
	//				unsigned int monitor = 0, bool inputGrabbed = 0, bool vsync = 0);
	int open();
	int close();

	int use();
	int swap();
	int blit(std::shared_ptr<SDL_Surface> image);
	float getAspectRatio();

private:
	int initSDL(int GLMajor, int GLMinor);
	int closeSDL();

	SDL_Window *mWindow;
	unsigned int mW, mH, mMonitor;
	bool mFullscreen, mInputGrabbed, mVsync;
	bool mOpened;
	std::string mName;

	static SDL_GLContext mContext;

	static bool mSDLInited;
	static unsigned int mNumWindows;
};


} // mgf

#endif // MGF_WINDOW_H
