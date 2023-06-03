#include "Input.h"
#include "../Core/Engine.h"



Input* Input::s_Instance = nullptr;

Input::Input() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

int Input::Listen()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			Menu::GetInstance()->Quit(); Pause::GetInstance()->Quit(); Engine::GetInstance()->Quit(); return 1; break;
		}
		case SDL_KEYDOWN:
			KeyDown(); break;
		case SDL_KEYUP:
			KeyUp(); break;
		case SDL_MOUSEMOTION:
			MouseUpdatePos();  break;
		case SDL_MOUSEBUTTONDOWN:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				LeftKey = 1;
				break;
			case SDL_BUTTON_RIGHT:
				RigthKey = 1;
				break;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				LeftKey = 0;
				break;
			case SDL_BUTTON_RIGHT:
				RigthKey = 0;
				break;
			}
			break;
		}

		}
	}
	return 0;
}

bool Input::GetKeyDown(SDL_Scancode key)
{
	return (m_KeyStates[key] == 1);
}

bool Input::GetMouseLeftKeyDown()
{
	return LeftKey == 1;
}

bool Input::GetMouseRigthKeyDown()
{
	return RigthKey == 1;
}

void Input::KeyUp()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}


void Input::MouseUpdatePos()
{
	SDL_GetMouseState(&m_MousePosX, &m_MousePosY);
}

