#include"../Core/Engine.h"
#include"../Timer/Timer.h"
int main(int argc, char** argv)
{
	Engine::GetInstance()->Init();
	Menu::GetInstance()->Init(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow());
	Pause::GetInstance()->Init(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow());
	while (true)
	{
		while (Menu::GetInstance()->IsRunning())
		{
			Menu::GetInstance()->Events();
			Menu::GetInstance()->Update();
			Menu::GetInstance()->Render();
			Timer::GetInstance()->Tick();
		}
		while (Engine::GetInstance()->IsRunning())
		{

			Engine::GetInstance()->Events();
			Engine::GetInstance()->Update();
			Engine::GetInstance()->Render();
			Timer::GetInstance()->Tick();
		}
		if ((Menu::GetInstance()->IsRunning() || Engine::GetInstance()->IsRunning()) == 0)
			break;
	}
	Engine::GetInstance()->Clean();
	return 0;
}