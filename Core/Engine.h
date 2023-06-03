#pragma once
#include<SDL.h>
#include <SDL_image.h>


class Engine
{
public:
	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}

	bool Init();

	bool Clean();

	void Quit();

	void Update();

	void Render();

	void Events();

	inline bool IsRunning() { return m_IsRunning; };
	inline void Run() { m_IsRunning = true; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; };
	inline SDL_Window* GetWindow() { return m_Window; }
	inline int GetWindowWidth() { return m_WindowWidth; }
	inline int GetWindowHeigth() { return m_WindowHeigth; }

private:
	SDL_Window* m_Window;
	int m_WindowHeigth;
	int m_WindowWidth;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;
	Engine() {};
	static Engine* s_Instance;
};

class Menu
{
public:
	static Menu* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu();
	}

	bool Init(SDL_Renderer* m_Renderer, SDL_Window* m_Window);


	void Quit();

	void Update();

	void Render();

	void Events();

	inline bool IsRunning() { return m_IsRunning; };
	inline int GetWindowWidth() { return m_WindowWidth; }
	inline int GetWindowHeigth() { return m_WindowHeigth; }
	inline void Run() { m_IsRunning = true; }

private:
	SDL_Window* m_Window;
	int m_WindowHeigth;
	int m_WindowWidth;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;
	Menu() {};
	static Menu* s_Instance;
};


class Pause
{
public:
	static Pause* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Pause();
	}

	bool Init(SDL_Renderer* m_Renderer, SDL_Window* m_Window);
	inline void Run() { m_IsRunning = true; }

	void Quit();

	void Update();

	void Render();

	void Events();

	inline bool IsRunning() { return m_IsRunning; };
	inline int GetWindowWidth() { return m_WindowWidth; }
	inline int GetWindowHeigth() { return m_WindowHeigth; }

private:
	SDL_Window* m_Window;
	int m_WindowHeigth;
	int m_WindowWidth;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;
	Pause() {};
	static Pause* s_Instance;
};


