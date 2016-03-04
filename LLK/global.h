#pragma once

//Define vertex structure

typedef struct tagVertex{
	int row;     //Row
	int col;     //Column
	int info;    //Information
}Vertex;

#define			BLANK						-1
#define			MAX_ROW						10  //Row number of game map
#define			MAX_COL						16  //Column number of game map
#define			MAX_SAVED_VERTEX_NUM		4	//Vertex number
#define			MAX_PIC_NUM					16  //kind number of image
#define			REPEAT_NUM					10  //Number of each kind imege
#define			MAP_TOP						50  //The game map starting point vertical coordinates
#define			MAP_LEFT					20	//The geme map starting point horizontal coordinates
#define			PIC_WIDTH					40  //Width of image
#define			PIC_HEIGHT					40	//Height of image
#define			PLAY_TIMER_ID				1   //To number a timer
#define			GAME_LOSE					-1  //Lose
#define			GAME_SUCCESS				0	//Win
#define			GAME_PLAY					1	//Game is playing



