#pragma once
#include<SDL_ttf.h>
#include"../Core/Engine.h"
#include <string>
static int d = 0;
class Text
{
public:
	static Text* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new Text()); }
	void Write(std::string message, int x, int y, int size, int r = 202, int g = 69, int b = 255,int count=0)
	{
		int width, heigth;
		if (count == 1)
		{
			for (size_t i = 0; i < message.length(); i++)
			{
				if (message[i] == '.')
				{
					std::string mes(message,0, i + 2+1);
					message = mes;
				}
			}
		}
		TTF_Font* Sans = TTF_OpenFont("../assets/calibri.ttf", size);
		SDL_Color White = { r, g, b };
		SDL_Surface* surfaceMessage = TTF_RenderUTF8_Solid(Sans, message.c_str(), White);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);
		SDL_QueryTexture(Message, NULL, NULL, &width, &heigth);
		SDL_Rect Message_rect = { x,y,width,heigth };
		SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
		SDL_DestroyTexture(Message);
		SDL_FreeSurface(surfaceMessage);
		TTF_CloseFont(Sans);

	}
	std::string Read(int x, int y, std::string& in) {
		SDL_StartTextInput();
		bool running = true;
		d = in.size();
		Menu::GetInstance()->Render();
		while (running) {
			SDL_Event ev;
			while (SDL_PollEvent(&ev)) {
				if (ev.type == SDL_TEXTINPUT)
				{
					char* a = ev.text.text;
					if ((*a>=48&&*a<=57&&(d==0||in[0]!='0')&&(d<1||in[0]!='-'||*a!='0'||d>1) || *a == 45 && d == 0) && d < 9)
					{
						in += ev.text.text;
						d++;
					}
				}
				else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE&&in.size()) {
					{
						d--;
						in.pop_back();
						Menu::GetInstance()->Render();
					}
				}
				else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN && in.size()) {
					running = 0;

				}
				Write(in, x, y, 15);
				SDL_RenderPresent(m_Renderer);
			}
		}
		return in;
	}







private:

	Text() {
		if (TTF_Init() != 0)
			SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		m_Window = Engine::GetInstance()->GetWindow();
		m_Renderer = Engine::GetInstance()->GetRenderer();
	}
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Text* s_Instance;
};
Text* Text::s_Instance = nullptr;
