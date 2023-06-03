#pragma once


#include<SDL.h>
#include"../Physics/Transform.h"



class Input
{
public:
	static Input* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
	}
	int Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetMouseRigthKeyDown();
	bool GetMouseLeftKeyDown();
	void SetMouseLeftKeyDown() { LeftKey = 0; }
	Vector_2D* GetMousePosition() { return new Vector_2D(m_MousePosX, m_MousePosY); }
private:
	Input();
	static Input* s_Instance;
	void KeyUp();
	void KeyDown();
	void MouseUpdatePos();
	const Uint8* m_KeyStates;
	bool LeftKey = 0, RigthKey = 0;
	int m_MousePosX, m_MousePosY;
};

