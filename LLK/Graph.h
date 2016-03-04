#pragma once
#include "global.h"

class CGraph
{
public:
	CGraph();
	~CGraph(void);

	void InitGraph(void);
	int AddVertex(int info); //To add vertex info into vertex array
	int GetVertex(int nIndex); //To get vertex with index nIndex from vertex array 
	void AddArc(int nV1Index, int nV2Index); //To add relation ofnV1Index and nV2Index to relation matrix
	int GetVexnum(void); //To get vertex number in the vertex array
	void UpdateVertex(int nIndex,int info); //Update the value of vertex array indexed with nIndex as info
	int GetAdj(int nRow,int nCol);
	void ClearGraph(void);
	void AddMap(int num,int nRow, int nCol);
	int GetMap(int nRow, int nCol);

protected:

	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	int m_anMap[MAX_ROW][MAX_COL];
	Vertices   m_Vertices;     //vertex array
	AdjMatrix  m_AdjMatrix;    //Relation matrix
	int        m_nVexnum;	   // Vertex number
	int        m_nArcnum;	   // Edge number
};

