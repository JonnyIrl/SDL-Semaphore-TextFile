#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <SDL.h>

static class Renderer
{
private:
	static bool instanceFlag;
	static Renderer* instance;
	Renderer::Renderer() {
	}
	//renderer
	SDL_Renderer* gRenderer = NULL;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
public:

	static Renderer* GetInstance();
	~Renderer()
	{
		instanceFlag = false;
	}
	bool Init(SDL_Window* window, int screen_Width, int screen_Height);
	void ClearRenderer();
	void RenderScreen();
	void Draw(SDL_Rect rectangle);
	void DrawImage(SDL_Rect*, SDL_Rect*, SDL_Texture*, float z);
	SDL_Renderer* Get_SDL_RENDERER();

	int CameraXOffSet;
	void updateCameraPosition(int x);

};
#endif
