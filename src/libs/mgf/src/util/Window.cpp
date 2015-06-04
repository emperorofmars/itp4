/*
**	Author:		Martin Schwarz
**	Name:		Window.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Window.h"

namespace mgf{

bool Window::mSDLInited = false;
unsigned int Window::mNumWindows = 0;
SDL_GLContext Window::mContext = NULL;

Window::Window(const std::string &name, unsigned int w, unsigned int h, bool fullscreen,
		   unsigned int monitor, bool inputGrabbed, bool vsync)
{
	mName = name;
	mWindow = NULL;
	mW = w;
	mH = h;
	mFullscreen = fullscreen;
	mInputGrabbed = inputGrabbed;
	mMonitor = monitor;
	mVsync = vsync;

	if(!mSDLInited) initSDL(3, 3);
	else open();
}

Window::~Window(){
	if(mOpened) close();
	if(mSDLInited && mNumWindows == 0){
		closeSDL();
	}
}

int Window::open(){
	if(!mSDLInited) return -1;
	if(mOpened) return -1;

	int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if(mFullscreen == 1) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if(mInputGrabbed == 1) flags |= SDL_WINDOW_INPUT_GRABBED;

	int posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(mMonitor);
	int posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(mMonitor);

	mWindow = SDL_CreateWindow(mName.c_str(), posX, posY, mW, mH, flags);
	if(mWindow == NULL){
		LOG_F_INFO(MGF_LOG_FILE, "SDL_CreateWindow failed! SDL_Error: ", SDL_GetError());
		return -1;
	}
	mNumWindows++;

	mOpened = true;

	LOG_F_INFO(MGF_LOG_FILE, "window initialized successfully!");
	return 0;
}

int Window::close(){
	if(!mOpened) return -1;

	SDL_DestroyWindow(mWindow);

	mWindow = NULL;
	mOpened = false;
	mNumWindows--;

	LOG_F_INFO(MGF_LOG_FILE, "window closed!");
	return 0;
}

int Window::use(){
	if(!mOpened && !mContext) return -1;
	SDL_GL_MakeCurrent(mWindow, mContext);
	return 0;
}

int Window::swap(){
	if(mOpened == true) SDL_GL_SwapWindow(mWindow);
	return 0;
}

float Window::getAspectRatio(){
	if(mH != 0) return (float)mW / (float)mH;
	return 0;
}

glm::vec2 Window::getResolution(){
	return glm::vec2(mW, mH);
}

int Window::initSDL(int GLMajor, int GLMinor){
	bool success = true;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		LOG_F_ERROR(MGF_LOG_FILE, "SDL_Init failed! SDL_Error: ", SDL_GetError());
		success = false;
	}
	mSDLInited = true;

	if(success){
		int flags = IMG_INIT_PNG | IMG_INIT_JPG;
		if(!(IMG_Init(flags) & flags))
		{
			LOG_F_ERROR(MGF_LOG_FILE, "IMG_Init failed! IMG_Error: ", IMG_GetError());
			success = false;
		}
	}
	if(success){
		if(TTF_Init() < 0){
			LOG_F_ERROR(MGF_LOG_FILE, "TTF_Init failed! SDL_Error: ", SDL_GetError());
			success = false;
		}
	}
	if(success){
		if(open() < 0){
			LOG_F_ERROR(MGF_LOG_FILE, "SDL_CreateWindow failed! SDL_Error: ", SDL_GetError());
			success = false;
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GLMajor);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GLMinor);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		if(success){
			mContext = SDL_GL_CreateContext(mWindow);
			if(!mContext){
				LOG_F_ERROR(MGF_LOG_FILE, "SDL_GL_CreateContext failed!");
				success = false;
			}
		}
		if(success){
			glewExperimental = GL_TRUE;
			GLenum glewError = glewInit();
			if(glewError != GLEW_OK){
				LOG_F_ERROR(MGF_LOG_FILE, "glewInit failed!");
				success = false;
			}
		}

		if(success){
			if(SDL_GL_SetSwapInterval(1) < 0){
				LOG_F_ERROR(MGF_LOG_FILE, "SDL_GL_SetSwapInterval failed! SDL_Error: ", SDL_GetError());
				success = false;
			}
		}
	}

	if(!success){
		mSDLInited = false;
		closeSDL();
		LOG_F_ERROR(MGF_LOG_FILE, "initializing SDL failed!");
		return false;
	}

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    SDL_SetRelativeMouseMode(SDL_TRUE);

	LOG_F_INFO(MGF_LOG_FILE, "SDL initialized successfully!");
	return 0;
}

int Window::closeSDL(){
	if(!mSDLInited){
		LOG_F_INFO(MGF_LOG_FILE, "Cant close SDL: not inited!");
		return -1;
	}
	SDL_GL_DeleteContext(mContext);

	close();
    TTF_Quit();
    IMG_Quit();
	SDL_Quit();

	LOG_F_INFO(MGF_LOG_FILE, "SDL closed!");
	return 0;
}

} // mgf










