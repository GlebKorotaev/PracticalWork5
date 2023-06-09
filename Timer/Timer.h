#pragma once



const int TARGET_FPS = 40;
const float TARGET_DELTATIME = 1.5f;



class Timer
{
public:
	inline static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : s_Instance = new Timer()); }
	void Tick();
	inline float GetDeltaTime() { return m_DeltaTime; }

private:
	Timer() {};
	static Timer* s_Instance;
	float m_DeltaTime;
	float m_LastTime;

};

