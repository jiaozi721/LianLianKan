#include "StdAfx.h"
#include "GameControl.h"
#include "global.h"

CGameControl::CGameControl(void)  // Constructor
{	
}
 
CGameControl::~CGameControl(void)  //Desturctor
{
}

void CGameControl::StartGame(void)
{
	logic.m_nSetRow = CRow;
	logic.m_nSetCol = CCol;
	logic.InitMap(m_anMap);

	ResetMap();

}

bool CGameControl::Link(Vertex avPath[MAX_SAVED_VERTEX_NUM],int &nVexnum)
{
	if((m_svSelFst.row!=m_svSelSec.row) || (m_svSelFst.col!=m_svSelSec.col))
	if(GetElement(m_svSelFst.row,m_svSelFst.col)==GetElement(m_svSelSec.row,m_svSelSec.col))
	{
		if(logic.IsLink(m_anMap,m_svSelFst,m_svSelSec))
		{
			nVexnum = logic.GetVexPath(avPath);
			logic.Clear(m_anMap,m_svSelFst,m_svSelSec);
	
		return true;
		}

	}
	return false;
}

void CGameControl::SetFirstPoint(int nRow,int nCol)
{ // To set m_ptSelFirst Information
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow,int nCol)
{  // To set m_ptSelSec Information
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}


int CGameControl::GetElement(int nRow,int nCol)
{
	return m_anMap[nRow][nCol];
}

bool CGameControl::IsWin(void)
{
	if(logic.IsBlanked(m_anMap))
		return true;
	return false;
	
}

bool CGameControl::Help(Vertex avsPath[MAX_SAVED_VERTEX_NUM],int &nVexnum)
{
	if(!logic.IsBlanked(m_anMap))
	{
		if(logic.SearchValidPath(m_anMap))
		{
			nVexnum = logic.GetVexPath(avsPath);
			logic.SetHelpAfter();
			return true;
		}
		
	}
	logic.SetHelpAfter();
	return false;
}

void CGameControl::ResetMap(void)
{
	logic.ResetMap(m_anMap);
}