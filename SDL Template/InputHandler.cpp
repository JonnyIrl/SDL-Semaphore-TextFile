#include "InputHandler.h"

InputHandler::InputHandler() { }

InputHandler::~InputHandler() { }

//E.g - void gameLoop() {
//			if (inputHandler.CheckInput(SDLK_a))
//				move player left 
bool InputHandler::CheckInput(SDL_Keycode key, SDL_Event event) {
	if (event.key.keysym.sym == key)
		return true;
	else
		return false;
}