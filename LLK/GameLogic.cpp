#include "StdAfx.h"
#include "GameLogic.h"


CGameLogic::CGameLogic(void) :
m_nVexNums(0)
{

}


CGameLogic::~CGameLogic(void)
{

}


void CGameLogic::InitMap(int anMap[MAX_ROW][MAX_COL])
{
	srand((unsigned)time(NULL));
	for(int i=0; i<m_nSetRow; i++)
	{
		for(int j=0; j<m_nSetCol; j++)
		{
			anMap[i][j]=j;

		}
	}


}

bool CGameLogic::IsLink(int anMap[MAX_ROW][MAX_COL],Vertex v1, Vertex v2)
{
	PushVertex(v1);
	//Link is a straight line of horizontal
	if(v1.row == v2.row)
	{
		if(LinkInRow(anMap,v1,v2))
			return true;
		if(TwoCornerLink(anMap,v1,v2))
			return true;
	}

	//link in a straight line of vertical
	else if(v1.col == v2.col)
	{
		if(LinkInCol(anMap,v1,v2))
			return true;
		if(TwoCornerLink(anMap,v1,v2))
			return true;
	}

	else if(OneCornerLink(anMap,v1,v2))
	{
		PushVertex(v2);
		return true;
	}
	else if(TwoCornerLink(anMap,v1,v2))
	{
		return true;
	}
	PopVertex();
	return false;
}


bool CGameLogic::LinkInRow(int anMap[MAX_ROW][MAX_COL],Vertex v1, Vertex v2)
{
	
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;
	//Link is a straight line
	if(nCol1<nCol2)
		for(int i = nCol1 +1 ; i < nCol2; i++)
		{
			if(anMap[nRow][i]!=-1)
				return false;
		}
	else
		for(int i = nCol2 +1 ; i < nCol1; i++)
		{
			if(anMap[nRow][i]!=-1)
				return false;
		}
		PushVertex(v2);
		return true;
}

bool CGameLogic::LinkInCol(int anMap[MAX_ROW][MAX_COL] ,Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;
	if(nRow1 > nRow2)
	{
		for(int i = nRow2 +1 ; i <nRow1; i++)
		{
			if(anMap[i][nCol]!=-1)
				return false;
		}
	}
	//Link in a straight line
	else
	{
		for(int i = nRow1 + 1 ; i < nRow2; i++)
		{
			if(anMap[i][nCol]!=-1)
				return false;
		}
	}
	PushVertex(v2);
	return true;
}

bool CGameLogic::LineX(int anMap[MAX_ROW][MAX_COL], int nRow , int nCol1, int nCol2)
{
	if(nCol1>nCol2)
	{
		for(int nCol = nCol2; nCol <= nCol1; nCol++)
		{
			if(anMap[nRow][nCol]!=-1)
				return false;
		}
	}
	else
	for(int nCol = nCol1; nCol<= nCol2; nCol++)
	{
			if(anMap[nRow][nCol]!=-1)
				return false;
	}
	return true;
}

bool CGameLogic::LineY(int anMap[MAX_ROW][MAX_COL],int nRow1, int nRow2, int nCol)
{
	if(nRow1>nRow2)
	{
		for(int nRow = nRow2; nRow <= nRow1; nRow++)
		{
			if(anMap[nRow][nCol]!=-1)
				return false;
		}
	}
	else
		for(int nRow=nRow1; nRow <= nRow2; nRow++)
		{
			if(anMap[nRow][nCol]!=-1)
				return false;
		}
	return true;
}

bool CGameLogic::OneCornerLink(int anMap[MAX_ROW][MAX_COL],Vertex v1,Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	Vertex temp;
	if(nRow1 > nRow2)
	{
		if(nCol1<nCol2)
		{
			if(LineY(anMap,nRow2,nRow1-1,nCol1)&&LineX(anMap,nRow2,nCol1,nCol2-1)){
				temp.row = nRow2; 
				temp.col = nCol1; 
				PushVertex(temp);
				return true;}
			if(LineY(anMap,nRow2+1,nRow1,nCol2)&&LineX(anMap,nRow1,nCol1+1,nCol2)){
				temp.row = nRow1; 
				temp.col = nCol2; 
				PushVertex(temp);
				return true;}
			}
		else
		{
			if(LineY(anMap,nRow2+1,nRow1,nCol2)&&LineX(anMap,nRow1,nCol2,nCol1-1)){
				temp.row = nRow1; 
				temp.col = nCol2; 
				PushVertex(temp);
				return true;}
			if(LineY(anMap,nRow2,nRow1-1,nCol1)&&LineX(anMap,nRow2,nCol2+1,nCol1)){
				temp.row = nRow2; 
				temp.col = nCol1; 
				PushVertex(temp);
				return true;}
		}
	}
	else
	{
		if(nCol1 < nCol2)
		{
			if(LineY(anMap,nRow1,nRow2-1,nCol2)&&LineX(anMap,nRow1,nCol1+1,nCol2)){
				temp.row = nRow1; 
				temp.col = nCol2; 
				PushVertex(temp);
				return true;}
			if(LineY(anMap,nRow1+1,nRow2,nCol1)&&LineX(anMap,nRow2,nCol1,nCol2-1)){
				temp.row = nRow2; 
				temp.col = nCol1; 
				PushVertex(temp);
				return true;}
		}
		else
		{
			if(LineY(anMap,nRow1+1,nRow2,nCol1)&&LineX(anMap,nRow2,nCol2+1,nCol1)){
				temp.row = nRow2; 
				temp.col = nCol1; 
				PushVertex(temp);
				return true;}
			if(LineY(anMap,nRow1,nRow2-1,nCol2)&&LineX(anMap,nRow1,nCol2,nCol1-1)){
				temp.row = nRow1; 
				temp.col = nCol2; 
				PushVertex(temp);
				return true;}
		}
	}
	return false;
}

bool CGameLogic::TwoCornerLink(int anMap[MAX_ROW][MAX_COL],Vertex v1, Vertex v2)
{
	Vertex left,right,temp;

	left.col=v1.col;
	right.col=v2.col;
	for(int i = 0; i< MAX_ROW; i++)
	{
		if(LineX(anMap,i,v1.col,v2.col)){
			if(LineY(anMap,i,(v1.row > i) ? v1.row-1 : v1.row+1 , v1.col) &&
				LineY(anMap,i,(v2.row > i) ? v2.row-1 : v2.row+1, v2.col)){

					temp.col=v1.col;
					temp.row=i;
					PushVertex(temp);
					temp.col=v2.col;
					temp.row=i;
					PushVertex(temp);
					PushVertex(v2);
					return true;
			}
		}
	}

	left.row=v1.row;
	right.row=v2.row;

	for(int i = 0; i< MAX_COL; i++)
	{
		if(LineY(anMap,v1.row,v2.row,i)){
			if(LineX(anMap,v1.row,i,(v1.col >i) ? v1.col-1 :v1.col+1) &&
				LineX(anMap,v2.row,i,(v2.col>i) ? v2.col-1 : v2.col+1)){
					temp.col=i;
					temp.row=v1.row;
					PushVertex(temp);
					temp.col=i;
					temp.row=v2.row;
					PushVertex(temp);
					PushVertex(v2);
					return true;
			}
		}
	}

	return false;
}

void CGameLogic::Clear(int anMap[MAX_ROW][MAX_COL],Vertex v1,Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
	m_nVexNums=0;
}

void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNums]= v;
	m_nVexNums++;
}

void CGameLogic::PopVertex()
{
	m_nVexNums--;
}

int CGameLogic::GetVexPath(Vertex avPath[MAX_SAVED_VERTEX_NUM])
{
	for(int i = 0 ; i < m_nVexNums; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNums;
}

bool CGameLogic::IsBlanked(int anMap[MAX_ROW][MAX_COL])
{
	bool clear = true;
	for(int i = 0 ; i < m_nSetRow ; i++)
	{
		for(int j = 0 ; j < m_nSetCol ; j++)
		{
			if(anMap[i][j]!=BLANK)
				clear = false;
		}
	}
	if(clear)
		return true;
	return false;

}

bool CGameLogic::SearchValidPath(int anMap[MAX_ROW][MAX_COL])
{
	int nInfo1, nInfo2;
	Vertex v1, v2;
	for(int i = 0 ; i < m_nSetRow ; i++)
	{
		for(int j = 0 ; j < m_nSetCol ; j++)
		{
			if(anMap[i][j]!=BLANK)
			{
				nInfo1 = anMap[i][j];
				v1.row = i ;
				v1.col = j ;
				for(int m = 0 ; m < m_nSetRow ; m++)
				{
					for(int n = 0 ; n < m_nSetCol ; n++)
					{
						if(anMap[i][j]!=BLANK && (i!=m || j!=n) && nInfo1 == anMap[m][n])
						{
							nInfo2 = anMap[m][n];
							v2.row = m ;
							v2.col = n ;
							if(IsLink(anMap,v1,v2))
								return true;
						}
					}
				}
			}
		}

	}	
	return false;
}


void CGameLogic::SetHelpAfter(void)
{
	m_nVexNums = 0;
}

void CGameLogic::ResetMap(int anMap[MAX_ROW][MAX_COL])
{
	srand((unsigned)time(NULL));

	for(int i = 0 ;i < MAX_ROW; i++)
	{
		for(int j= 0 ; j < MAX_COL; j++)
		{
			int row1 = rand()%m_nSetRow;
			int col1 = rand()%m_nSetCol;
			int row2 = rand()%m_nSetRow;
			int col2 = rand()%m_nSetCol;
			if(anMap[row1][col1]!=BLANK && anMap[row2][col2]!=BLANK)
			{
				int temp = anMap[row1][col1];
				anMap[row1][col1] = anMap[row2][col2];
				anMap[row2][col2] = temp;
			}
		}
	}
}

	



