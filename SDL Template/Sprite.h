#ifndef SPRITE_H
#define SPRITE_H

#include <iostream> 
#include "SDL.h"
#include <SDL_image.h>
#include <string>
#include "Renderer.h"


class Sprite
{
public:
	Sprite();
	void SetPosition(float x, float y);
	void SetWidth(float w);
	void SetHeight(float h);
	void SetDestinationRect(SDL_Rect destination);
	void SetSourceRect(SDL_Rect source);
	void SetOffset(int x, int y);/*offset is relative width and height of the sprite not the texture */
	void Draw();
	void Draw(std::string name);
	void DrawCloud();
	void DrawBackground(SDL_Rect player);
	void Init(std::string imagePath, SDL_Rect destination, SDL_Rect source);
	float GetX();
	float GetY();
private:
	SDL_Texture* loadTexture(std::string path, SDL_Renderer*);
	SDL_Texture* myTexture;
	int x_offset, y_offset;
	SDL_Rect m_Destrination, m_Source;
};
#endif
