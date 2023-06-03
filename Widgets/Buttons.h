#pragma once


#include <SDL.H>
#include <string>
#include<vector>
#include "../Inputs/Input.h"
#include"GameObject.h"
#include"../Graphics/TextureManager.h"

enum ButtonState { NORMAL = 0, HOVER = 1, PRESSED = 2 };
class Button :public GameObject
{
public:
	Button(int x, int y, int width, int heigth, void (*callback)(), std::vector<std::string>& textures, double compresion = 1) :GameObject(new Properties())
	{
		m_Transform->X = x;
		m_Transform->Y = y;
		m_Callback = callback;
		m_textures = textures;
		m_Shape = { x,y,width,heigth };
		m_TextureID = textures[NORMAL];
		m_Compression = compresion;
	}
	~Button() { m_textures.clear(); }
	virtual void clean() {	}
	virtual void* Update(float dt) { return nullptr; }
	void* Update(float dt, int x, int y)
	{
		m_Shape.x = m_Transform->X = x;
		m_Shape.y = m_Transform->Y = y;
		SDL_Rect m_Shape1;
		m_Shape1.x = m_Shape.x;
		m_Shape1.y = m_Shape.y;
		m_Shape1.w = m_Shape.w / m_Compression;
		m_Shape1.h = m_Shape.h / m_Compression;
		Vector_2D* mPos = Input::GetInstance()->GetMousePosition();
		SDL_Point point = { mPos->X,mPos->Y };

		if (SDL_PointInRect(&point, &m_Shape1))
		{
			if (Input::GetInstance()->GetMouseLeftKeyDown() && m_IsRelleased)
			{
				m_Callback();
				m_IsRelleased = false;
				m_TextureID = m_textures[PRESSED];
			}
			else if (!Input::GetInstance()->GetMouseLeftKeyDown())
			{
				m_IsRelleased = true;
				m_TextureID = m_textures[HOVER];
			}
		}
		else
		{
			m_TextureID = m_textures[NORMAL];
		}
		return nullptr;
	}
	virtual void Draw()
	{
		TextureManager::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Shape.w, m_Shape.h, m_Compression);
	}
	virtual void Clean() {};
private:
	SDL_Rect m_Shape;
	bool m_IsRelleased;
	void (*m_Callback)();
	std::vector<std::string> m_textures;
};

