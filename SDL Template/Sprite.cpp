
#include "Sprite.h"


Sprite::Sprite()
{
	x_offset = 0;
	y_offset = 0;
}
void Sprite::Init(std::string imagePath, SDL_Rect destination, SDL_Rect source)
{
	myTexture = loadTexture(imagePath, Renderer::GetInstance()->Get_SDL_RENDERER());
	m_Destrination = destination;
	m_Source = source;
}
void Sprite::SetPosition(float x, float y)
{
	m_Destrination.x = x;
	m_Destrination.y = y;
}
void Sprite::SetWidth(float w)
{
	m_Destrination.w = w;
}
void Sprite::SetHeight(float h)
{
	m_Destrination.h = h;
}
void Sprite::SetDestinationRect(SDL_Rect destination)
{
	m_Destrination = destination;
}
void Sprite::SetSourceRect(SDL_Rect source)
{
	m_Source = source;
}
float Sprite::GetX()
{
	return m_Destrination.x - x_offset;
}
float Sprite::GetY()
{
	return m_Destrination.y - y_offset;
}
void Sprite::SetOffset(int x, int y)
{
	x_offset = x;
	y_offset = y;
}
void Sprite::Draw()
{
	SDL_Rect newDest{ m_Destrination.x - x_offset, m_Destrination.y - y_offset, m_Destrination.w, m_Destrination.h };
	Renderer::GetInstance()->DrawImage(&m_Source, &newDest, myTexture, 1);
}

void Sprite::Draw(std::string name)
{
	SDL_Rect newDest{ m_Destrination.x - x_offset, m_Destrination.y - y_offset, m_Destrination.w, m_Destrination.h };
	Renderer::GetInstance()->DrawImage(&m_Source, &newDest, myTexture, 1);
}
void Sprite::DrawCloud()
{
	SDL_Rect newDest{ m_Destrination.x - x_offset, m_Destrination.y - y_offset, m_Destrination.w, m_Destrination.h };
	Renderer::GetInstance()->DrawImage(&m_Source, &newDest, myTexture, 5);
}
void Sprite::DrawBackground(SDL_Rect player)
{
	SDL_Rect newDest{ m_Destrination.x - x_offset, m_Destrination.y - y_offset, m_Destrination.w, m_Destrination.h };
	Renderer::GetInstance()->DrawImage(&m_Source, &newDest, myTexture, 550);
}
SDL_Texture* Sprite::loadTexture(std::string path, SDL_Renderer* gRenderer) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}


		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}


	return newTexture;
}