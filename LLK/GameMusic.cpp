#include "StdAfx.h"
#include "GameMusic.h"

Sound::Sound()
{
	Initsound();
}

Sound::~Sound()
{
	for(int i = 0; i < MAX_MUSIC; i++)
		FMOD_Sound_Release(g_Sound[i]);
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void Sound::Initsound()
{
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System,320,FMOD_INIT_NORMAL,NULL);
	FMOD_System_CreateStream(g_System,"Sounds\\mainBGM.mp3",FMOD_LOOP_NORMAL,0,&g_Sound[0]);
	FMOD_System_CreateStream(g_System,"Sounds\\InGameBGM.mp3",FMOD_LOOP_NORMAL,0,&g_Sound[1]);
	FMOD_System_CreateStream(g_System,"Sounds\\GameLose.mp3",FMOD_LOOP_NORMAL,0,&g_Sound[2]);	
	FMOD_System_CreateStream(g_System,"Sounds\\Win.mp3",FMOD_LOOP_NORMAL,0,&g_Sound[3]);			
	FMOD_System_CreateSound(g_System,"Sounds\\SwapSound.mp3",FMOD_DEFAULT,0,&g_Sound[4]);	
	FMOD_System_CreateSound(g_System,"Sounds\\ButtonClick.mp3",FMOD_DEFAULT,0,&g_Sound[5]);		
	FMOD_System_CreateSound(g_System,"Sounds\\InGameClick.mp3",FMOD_DEFAULT,0,&g_Sound[6]);		
	FMOD_System_CreateSound(g_System,"Sounds\\Erase.mp3",FMOD_DEFAULT,0,&g_Sound[7]);	
	FMOD_System_CreateSound(g_System,"Sounds\\Select.mp3",FMOD_DEFAULT,0,&g_Sound[8]);	
	FMOD_System_CreateSound(g_System,"Sounds\\TimeCaution.mp3",FMOD_DEFAULT,0,&g_Sound[9]);
}
	

void Sound::FirstScreen()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[0],0,&g_channel[0]);
	FMOD_System_Update(g_System);
}

void Sound::InGameBGM()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[1],0,&g_channel[1]);
	FMOD_System_Update(g_System);
}

void Sound::Lose()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[2],0,&g_channel[2]);
	FMOD_System_Update(g_System);
}

void Sound::Win()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[3],0,&g_channel[3]);
	FMOD_System_Update(g_System);
}

void Sound::SwapClick()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[4],0,&g_channel[4]);
	FMOD_System_Update(g_System);
}

void Sound::ButtonClick()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[5],0,&g_channel[5]);
	FMOD_System_Update(g_System);
}

void Sound::InGameClick()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[6],0,&g_channel[6]);
	FMOD_System_Update(g_System);
}

void Sound::Erase()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[7],0,&g_channel[7]);
	FMOD_System_Update(g_System);
}

void Sound::Select()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[8],0,&g_channel[8]);
	FMOD_System_Update(g_System);
}

void Sound::Stop()
{
	for(int i=0;i<4;i++)
		FMOD_Channel_Stop(g_channel[i]);
}

void Sound::SetMute()
{
	float v = 0.0f;
	for(int i = 0 ; i < MAX_MUSIC; i++)
		FMOD_Channel_SetVolume(g_channel[i],v);
}

void Sound::SetOn()
{
	float v = 1.0f;
	for(int i= 0 ; i<MAX_MUSIC; i++)
		FMOD_Channel_SetVolume(g_channel[i],v);
}

void Sound::TimeCaution()
{
	FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[9],0,&g_channel[9]);
	FMOD_System_Update(g_System);
}