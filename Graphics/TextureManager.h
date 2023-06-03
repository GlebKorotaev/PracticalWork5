#pragma once

#include <string>
#include<map>
#include <vector>
#include <SDL.h>


class TextureManager
{
public:
	static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new TextureManager()); }

	bool Load(std::string id, std::string filename);

	void Drop(std::string);

	void Clean();

	void Draw(std::string id, int x, int y, int width, int heigth, double compresion = 1, SDL_RendererFlip flip = SDL_FLIP_NONE, double angel = 0);
	void DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int heigth, double compression, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE, double angel = 0);
	~TextureManager() {
		std::vector<std::string>::iterator it = AllID.begin();
		for (; it != AllID.end(); it++)
		{
			Drop(*it);
		}
	}
private:
	TextureManager() {};
	static TextureManager* s_Instance;
	std::map<std::string, SDL_Texture*> m_TextureMap;
	std::vector<std::string> AllID;
};

