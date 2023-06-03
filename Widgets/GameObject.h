#pragma once

#include <string>

#include<SDL.h>
#include "IObject.h"
#include "../Physics/Transform.h"

struct Properties {
public:
	Properties(std::string textureID = "", float x = 0, float y = 0, int width = 0, int heigth = 0, double compression = 1, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		X = x;
		Y = y;
		Flip = flip;
		Width = width;
		Heigth = heigth;
		TextureID = textureID;
		Compression = compression;
	}
	int Width, Heigth;
	double Compression;
	float X, Y;
	std::string TextureID;
	SDL_RendererFlip Flip;
};

class GameObject :public IObject
{
public:
	GameObject(Properties* props) {
		m_TextureID = props->TextureID;
		m_Width = props->Width;
		m_Heigth = props->Heigth;
		m_Compression = props->Compression;
		m_Flip = props->Flip;
		m_Transform = new Transform(props->X, props->Y);
	};
	virtual void Draw() = 0;
	virtual void* Update(float dt) = 0;
	virtual void Clean() = 0;


protected:
	friend class Hunter;
	Transform* m_Transform;
	int m_Width, m_Heigth;
	double m_Compression;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;

private:



};

