#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>

class InputHandler {
public:
	InputHandler();
	~InputHandler();
	bool CheckInput(SDL_Keycode key, SDL_Event event);
private:
	//SDL_Event event;
};

#endif
