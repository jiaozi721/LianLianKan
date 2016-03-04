#pragma once

#include "global.h"


class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);

	int m_nSetRow;
	int m_nSetCol;
	
	int GetVexPath(Vertex avPath[MAX_SAVED_VERTEX_NUM]);

	
	bool IsLink(int anMap[MAX_ROW][MAX_COL],Vertex v1, Vertex v2);
	bool IsBlanked(int anMap[MAX_ROW][MAX_COL]); 
	bool LinkInRow(int anMap[MAX_ROW][MAX_COL],Vertex v1, Vertex v2);			// Decide horizontal link
	bool LinkInCol(int anMap[MAX_ROW][MAX_COL],Vertex v1, Vertex v2);			//Decide vertical link
	bool OneCornerLink(int anMap[MAX_ROW][MAX_COL],Vertex v1, Vertex v2);		//Decide one corner link
	bool LineY(int anMap[MAX_ROW][MAX_COL],int nRow1, int nRow2, int nCol);		//link on axis Y
	bool LineX(int anMap[MAX_ROW][MAX_COL],int nRow, int nCol1, int nCol2);		//link on axis X
	bool TwoCornerLink(int anMap[MAX_ROW][MAX_COL],Vertex v1,Vertex v2);
	bool SearchValidPath(int anMap[MAX_ROW][MAX_COL]);
 
	void InitSetRowCol(int row = 10 , int col = 16);
	void SetHelpAfter(void);
	void ResetMap(int anMap[MAX_ROW][MAX_COL]);
	void InitMap(int anMap[MAX_ROW][MAX_COL]);
	void Clear(int anMap[MAX_ROW][MAX_COL],Vertex v1,Vertex v2);				//Update two vertexes V1 ans V2 as BLANK And Update the two vertexes and edges left


protected:
	Vertex m_avPath[MAX_SAVED_VERTEX_NUM];										// To store vertexes settled in link decision
	int m_nVexNums;																//vertex number
	int m_anPath[MAX_SAVED_VERTEX_NUM];											//Save vertex indexes to link path
	
	void PushVertex(Vertex v);
	void PopVertex();															//Take out a vertex

};
