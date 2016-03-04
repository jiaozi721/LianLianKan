#include "StdAfx.h"
#include "Graph.h"


CGraph::CGraph(void):
	m_nVexnum(0)
{
	InitGraph();

}
	

CGraph::~CGraph(void)
{
}

void CGraph::InitGraph(void)
{
	//Initialize vertex and dege
	for(int i = 0; i<MAX_VERTEX_NUM; i++)
	{//Initialize vertex
		m_Vertices[i]=-1;
		//Initialize Edge
		for(int j = 0; j<MAX_VERTEX_NUM; j++)
		{
		m_AdjMatrix[i][j]=0;
		}
	}
	m_nVexnum=0;
	/*
	m_anMap[0][0] = 2;
	m_anMap[0][1] = 0;
	m_anMap[0][2] = 1;
	m_anMap[0][3] = 3;
	m_anMap[1][0] = 2;
	m_anMap[1][1] = 2;
	m_anMap[1][2] = 1;
	m_anMap[1][3] = 3;
	m_anMap[2][0] = 2;
	m_anMap[2][1] = 1;
	m_anMap[2][2] = 0;
	m_anMap[2][3] = 0;
	m_anMap[3][0] = 1;
	m_anMap[3][1] = 3;
	m_anMap[3][2] = 0;
	m_anMap[3][3] = 3;*/
}

int CGraph::AddVertex(int info)
{
	m_Vertices[m_nVexnum++]=info;
	return info;
}
/////////////////////////////////////
void CGraph::AddMap(int num, int nRow, int nCol)
{
	m_anMap[nRow][nCol]= num;
}

int CGraph::GetMap(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}
//////////////////////////////////

void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVertex(int nIndex1)
{
	return m_Vertices[nIndex1];
}



void CGraph::UpdateVertex(int nIndex1,int info)
{
	m_Vertices[nIndex1]=info;
	
}

int CGraph::GetVexnum(void)
{
	return m_nVexnum;
}

int CGraph::GetAdj(int nRow,int nCol)
{
	return m_AdjMatrix[nRow][nCol];
}

void CGraph::ClearGraph(void)
{
	InitGraph();
}