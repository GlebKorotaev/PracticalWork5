#include "Engine.h"
#include "../Graphics/TextureManager.h"
#include <iostream>
#include <list>
#include<vector>
#include"../Widgets/Buttons.h"
#include"../Text/Text.h"
#include"../Timer/Timer.h"

Engine* Engine::s_Instance = nullptr;
std::vector<std::vector<std::string>> AllID_ButtonMenu = { {},{},{},{} };//0-menu

int x1 = -10;
int x2 = 10;
static int flag = 1;

bool Engine::Init()
{
	m_WindowHeigth = 700;
	m_WindowWidth = 956;
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow(u8"Практическая N5", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeigth, window_flags);
	if (m_Window == nullptr)
	{
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}
	SDL_Surface* icon = IMG_Load("../assets/icon.png");
	SDL_SetWindowIcon(m_Window, icon);
	TextureManager::GetInstance()->Load("graf", "../assets/graf.gif");
	TextureManager::GetInstance()->Load("n", "../assets/n.png");
	AllID_ButtonMenu[0].push_back("n");
	TextureManager::GetInstance()->Load("h", "../assets/h.png");
	AllID_ButtonMenu[0].push_back("h");
	TextureManager::GetInstance()->Load("c", "../assets/c.png");
	AllID_ButtonMenu[0].push_back("c");
	TextureManager::GetInstance()->Load("anim", "../assets/anim.jpg");
	TextureManager::GetInstance()->Load("grad", "../assets/grad1.png");
	TextureManager::GetInstance()->Load("layer_grad", "../assets/layer_grad.png");

	return m_IsRunning = true;
}

bool Engine::Clean()
{
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}

void Engine::Quit()
{
	m_IsRunning = false;
	flag = 1;
}

void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	
	SDL_GL_GetDrawableSize(m_Window, &m_WindowWidth, &m_WindowHeigth);
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Quit();
		Menu::GetInstance()->Run();
	}
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

	int middle = x1 / 2 - x2 / 2;
	int length=abs(x1 - x2);
	{
		float k = length / 27.0;
		float one_part=(float)length / 26;
		one_part = (int(one_part * 100));
		one_part /= 100;
		{
			TextureManager::GetInstance()->Draw("graf", 0, 0, 956, 865);
			for (int i = 1; i <= 26; i++)
			{
				Text::GetInstance()->Write(std::to_string(x1 + i * one_part), 10 + i * 33, 865 / 2 + 30, 15, 0, 0, 0, 1);
			}

			for (float i = x1, z = 1; i <= x2; i += one_part/100, z += 1/100.0)
			{
				float ni = i + one_part/100;
				float nz = z + 1/100.0;
				SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
				SDL_RenderDrawLineF(m_Renderer, 10 + z * 33, (3 * sin(i / 4) - 2 / sin(2 * i)) + 865 / 2, 10 + nz * 33, (3 * sin(ni / 4) - 2 / sin(2 * ni)) + 865 / 2);
			}
			SDL_RenderPresent(m_Renderer);
		}
	}
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
	
}







Menu* Menu::s_Instance = nullptr;
Button* button_home_menu = nullptr;
Button* button_quit_menu = nullptr;
Button* LeftBorder = nullptr;
Button* RigthBorder = nullptr;
Button* button_record = nullptr;

int flagerror = 0;
float timeerror = 0.0;
std::string namex1 = std::to_string(x1);
std::string namex2 = std::to_string(x2);
void ReadX1()
{
	namex1 = Text::GetInstance()->Read(Menu::GetInstance()->GetWindowWidth() / 2 - 150+39, Menu::GetInstance()->GetWindowHeigth() / 2 + 19 - 100, namex1);
	try
	{
		x1 = stoi(namex1);
	}
	catch (const std::exception&)
	{
		x1 = -10;
		namex1 = "-10";
	}
	Input::GetInstance()->SetMouseLeftKeyDown();
}
void ReadX2()
{
	namex2 = Text::GetInstance()->Read(Menu::GetInstance()->GetWindowWidth() / 2 +50 + 39, Menu::GetInstance()->GetWindowHeigth() / 2 + 19 - 100, namex2);
	try
	{
		x2 = stoi(namex2);
	}
	catch (const std::exception&)
	{
		x2 = 10;
		namex2 = "10";
	}
	Input::GetInstance()->SetMouseLeftKeyDown();
}
void FalseRanningMenu()
{
	if (x1 >= x2)
	{
		x1 = -10;
		x2 = 10;
		namex1 = "-10";
		namex2 = "10";
		flagerror = 1;
		timeerror = 60.0;
		Input::GetInstance()->SetMouseLeftKeyDown();
		return;
	}
	Menu::GetInstance()->Quit();
	Engine::GetInstance()->Run();
}


void AllQuit() {
	Engine::GetInstance()->Quit();
	Pause::GetInstance()->Quit();
	Menu::GetInstance()->Quit();
}

void StartRecord()
{
	Pause::GetInstance()->Run();
	SDL_Event ev;
	while (SDL_PollEvent(&ev));
	SDL_PumpEvents();
	while (Pause::GetInstance()->IsRunning())
	{
		Pause::GetInstance()->Events();
		Pause::GetInstance()->Render();
		Pause::GetInstance()->Update();
		Timer::GetInstance()->Tick();
	}
}

bool Menu::Init(SDL_Renderer* m_Renderer, SDL_Window* m_Window)
{
	void (*callback)() = FalseRanningMenu;
	void (*quit)() = AllQuit;
	void (*record)() = StartRecord;
	void (*readx1)() = ReadX1;
	void (*readx2)() = ReadX2;
	m_WindowHeigth = 640;
	m_WindowWidth = 960;
	this->m_Renderer = m_Renderer;
	this->m_Window = m_Window;
	

	button_home_menu = new Button(m_WindowWidth / 2 - 50, m_WindowHeigth / 2 - 200, 96, 32, callback, AllID_ButtonMenu[0], 0.7);
	LeftBorder = new Button(m_WindowWidth / 2 - 150, m_WindowHeigth / 2 - 100, 96, 32, readx1, AllID_ButtonMenu[0], 0.7);
	RigthBorder = new Button(m_WindowWidth / 2 +50, m_WindowHeigth / 2 - 100, 96, 32, readx2, AllID_ButtonMenu[0], 0.7);
	button_quit_menu = new Button(m_WindowWidth / 2 - 50, m_WindowHeigth / 2 + 0, 96, 32, quit, AllID_ButtonMenu[0], 0.7);
	button_record = new Button(m_WindowWidth / 2 - 50, m_WindowHeigth / 2 + 100, 96, 32, record, AllID_ButtonMenu[0], 0.7);
	return m_IsRunning = true;
}



void Menu::Quit()
{
	m_IsRunning = false;
}

void Menu::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	SDL_GL_GetDrawableSize(m_Window, &m_WindowWidth, &m_WindowHeigth);
	button_home_menu->Update(dt, m_WindowWidth / 2 - 50, m_WindowHeigth / 2 - 200);
	LeftBorder->Update(dt, m_WindowWidth / 2 - 150, m_WindowHeigth / 2 - 100);
	RigthBorder->Update(dt, m_WindowWidth / 2 + 50, m_WindowHeigth / 2 - 100);
	button_record->Update(dt, m_WindowWidth / 2 - 50, m_WindowHeigth / 2 +0);
	button_quit_menu->Update(dt, m_WindowWidth / 2 - 50, m_WindowHeigth / 2 + 100);
}

void Menu::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0,255);
	SDL_RenderClear(m_Renderer);
	button_home_menu->Draw();
	LeftBorder->Draw();
	RigthBorder->Draw();
	button_quit_menu->Draw();
	button_record->Draw();

	Text::GetInstance()->Write(u8"Левая граница", m_WindowWidth / 2 - 150 + 19, m_WindowHeigth / 2 - 100 + 5, 15);
	Text::GetInstance()->Write(namex1, m_WindowWidth / 2 - 150 + 39, m_WindowHeigth / 2 - 100 + 19, 15);
	Text::GetInstance()->Write(namex2, m_WindowWidth / 2 +50 + 39, m_WindowHeigth / 2 - 100 + 19, 15);
	Text::GetInstance()->Write(u8"Правая граница", m_WindowWidth / 2 + 50 + 19, m_WindowHeigth / 2 -100 +5, 15);

	Text::GetInstance()->Write(u8"График", m_WindowWidth / 2 - 50+9, m_WindowHeigth / 2 - 200+10, 25);
	Text::GetInstance()->Write(u8"Анимация", m_WindowWidth / 2 - 50+9, m_WindowHeigth / 2 +10, 25);
	Text::GetInstance()->Write(u8"Выход", m_WindowWidth / 2 - 50+9, m_WindowHeigth / 2 + 100+10, 25);
	if (flagerror)
	{
		Text::GetInstance()->Write(u8"Левая граница больше правой!!!", m_WindowWidth / 2 - 60, m_WindowHeigth -30, 25,255,255,255);
		float dt = Timer::GetInstance()->GetDeltaTime();
		if (dt > 0)
			timeerror -= dt;
		if (timeerror < 0)
			flagerror = 0;
	}
	Text::GetInstance()->Write(u8"Коротаев Г.В О725Б", m_WindowWidth / 2 - 35 - 5, 20, 15, 255, 255, 255);
	SDL_RenderPresent(m_Renderer);
}

void Menu::Events()
{
	Input::GetInstance()->Listen();
}









Pause* Pause::s_Instance = nullptr;
void FalseRanningPause()
{
	Pause::GetInstance()->Quit();
}
void FalseRanningPausetoMenu() {
	Pause::GetInstance()->Quit();
	Engine::GetInstance()->Quit();
	Menu::GetInstance()->Run();
	Input::GetInstance()->SetMouseLeftKeyDown();
}

bool Pause::Init(SDL_Renderer* m_Renderer, SDL_Window* m_Window)
{
	void (*callback)() = FalseRanningPause;
	void (*callbacktomenu)() = FalseRanningPausetoMenu;
	m_WindowHeigth = 640;
	m_WindowWidth = 960;
	this->m_Renderer = m_Renderer;
	this->m_Window = m_Window;


	return m_IsRunning = true;
}


static int m = 0;
static int startanim = 0;
static float timesun = 0.0;
static int flagprintcol = 0;
static int flagprintrow = 1;
static int i = 1;
static int k = 75;
void Pause::Quit()
{
	m_IsRunning = false;
}

void Pause::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	SDL_GL_GetDrawableSize(m_Window, &m_WindowWidth, &m_WindowHeigth);
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
	{
		m = 0;
		startanim = 0;
		flagprintcol = 0;
		flagprintrow = 1;
		i = 1;
		k = 75;
		Quit();
		Menu::GetInstance()->Run();
	}
}

void Pause::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	TextureManager::GetInstance()->Draw("grad", m_WindowWidth - 200, 50, 400, 1000, 5);
	SDL_Event event;
	int length;
	const Uint8* state= SDL_GetKeyboardState(&length);
	for (int i = 0; i < length; i++)
		if (state[i])
		{
			m = 1;
			break;
		}
	if(startanim==0)
	{
		if (m == 0)
			TextureManager::GetInstance()->DrawFrame("anim", 270, 100, 1200 / 3, 800 / 2, 1, 0, 2);
		else
		{
			startanim = 1;
			timesun = (timesun != 0 ? 40 : timesun);
		}
	}
	else
	{
		float dt = Timer::GetInstance()->GetDeltaTime();
		TextureManager::GetInstance()->DrawFrame("anim", 270, 100, 1200 / 3, 800 / 2, 1, flagprintrow, flagprintcol);
		if(dt>0) timesun -= dt;
		for (int j = 0; j < i&&j<75&&flagprintrow==1; j++)
		{
			TextureManager::GetInstance()->Draw("layer_grad", m_WindowWidth - 170, 149-1*j, 70, 10, 5);
		}
		if(flagprintrow==1)
		i++;
		for (int j = 0; j < k && flagprintrow == 0; j++)
		{
			TextureManager::GetInstance()->Draw("layer_grad", m_WindowWidth - 170, 149 - 1 * j, 70, 10, 5);
		}
		if (flagprintrow == 0)
			k--;
		if (timesun < 0)
		{
			timesun = 40;
			flagprintcol++;
			if (flagprintcol == 3)
			{
				flagprintrow = 0;
				flagprintcol = 0;
				i = 1;
				k = 75;
			}
			if (flagprintcol == 2 && flagprintrow == 0)
			{
				startanim = 0;
				flagprintcol = 0;
				flagprintrow = 1;
				m = 0;
				i = 1;
				k = 75;
			}
		}
	}
	SDL_RenderPresent(m_Renderer);
}

void Pause::Events()
{
	Input::GetInstance()->Listen();
}




