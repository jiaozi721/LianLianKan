// GameResult.cpp : implementation file
//

#include "stdafx.h"
#include "LLK.h"
#include "GameResult.h"
#include "afxdialogex.h"

// CGameResult dialog

IMPLEMENT_DYNAMIC(CGameResult, CDialogEx)

CGameResult::CGameResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameResult::IDD, pParent)
{


}

CGameResult::~CGameResult()
{
}

BOOL CGameResult::OnInitDialog()
{
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

		
};

void CGameResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CGameResult::UpdateWindow(void)
{
	//Adjust Windows size
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);    //Get window size
	this->GetClientRect(rtClient); //get client area size
	
	// Size of title bar & outer frame
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	
	//Set window size
	MoveWindow(0, 0, 300 + nSpanWidth, 300 + nSpanHeight);
	// Set dialog box displayed in midpoint of the window
	CenterWindow();
}

void CGameResult::InitBackground(void)
{
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_GAME_RESULT);
	m_dcMem.SelectObject(bmpMain);
}


void CGameResult::ShowCombo(void)
{
	CDC* pDC = GetDC();
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));
	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	CString strScore;
	strScore.Format(_T(" TotalCombo : %4d"),TotalCombo);
	CSize size = pDC->GetTextExtent(strScore, strScore.GetLength());
	pDC->TextOutW(20,110, strScore);
}

void CGameResult::ShowBonus(void)
{
	CDC* pDC = GetDC();
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));
	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	CString strScore;
	strScore.Format(_T(" TimeBonus  : %4d"),TimeBonus);
	CSize size = pDC->GetTextExtent(strScore, strScore.GetLength());
	pDC->TextOutW(20,150, strScore);
}


void CGameResult::ShowScore(void)
{
	CDC* pDC = GetDC();
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));
	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	CString strScore;
	strScore.Format(_T(" TotalScore : %4d"),TotalScore);
	CSize size = pDC->GetTextExtent(strScore, strScore.GetLength());
	pDC->TextOutW(20,190, strScore);
}

BEGIN_MESSAGE_MAP(CGameResult, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGameResult message handlers


void CGameResult::OnPaint()
{
	
	InitBackground();
	UpdateWindow();
	CPaintDC dc(this);
	dc.BitBlt(0,0,300,300,&m_dcMem,0,0,SRCCOPY);
	ShowScore();
	ShowBonus();
	ShowCombo();
	 // device context for painting
	
}
