#pragma once


#include "GameLogic.h"


class CGameControl 
{
public:


	CGameControl(void);
	~CGameControl(void);
	
	int CRow;
	int CCol;
	int GetElement(int nRow,int nCol);

	bool IsWin(void);
	bool Help(Vertex avsPath[MAX_SAVED_VERTEX_NUM],int &nVexnum);
	bool Link(Vertex avPath[MAX_SAVED_VERTEX_NUM],int &nVexnum);
	
	void StartGame(void);
	void SetFirstPoint(int nRow,int nCol);
	void SetSecPoint(int nRow,int nCol);
	void ResetMap(void);

	CGameLogic logic;

protected:
	int m_anMap[MAX_ROW][MAX_COL];
	Vertex m_svSelFst;						//The first selected point
	Vertex m_svSelSec;						//The second selected point

};
