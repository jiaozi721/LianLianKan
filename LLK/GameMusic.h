#include <windows.h>
#include <fmod.h>

#define MAX_MUSIC 10

class Sound{
private:

	FMOD_SYSTEM *g_System;   
	FMOD_SOUND *g_Sound[MAX_MUSIC]; 
	FMOD_CHANNEL *g_channel[MAX_MUSIC];

public:
	Sound();
	~Sound();
	void Initsound();
	void InGameBGM();
	void FirstScreen();
	void SwapClick();
	void ButtonClick();
	void Erase();
	void Caution();
	void InGameClick();
	void Win();
	void Lose();
	void Select();
	void Stop();
	void SetMute();
	void SetOn();
	void TimeCaution();
};