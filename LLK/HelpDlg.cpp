// HelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLK.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// HelpDlg dialog

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HelpDlg::IDD, pParent)
{

}

HelpDlg::~HelpDlg()
{

}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void HelpDlg::InitBackground(void)
{
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_GAME_HELP);
	m_dcMem.SelectObject(bmpMain);

}

void HelpDlg::UpdateWindow(void)
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
	MoveWindow(0, 0, 400 + nSpanWidth, 400 + nSpanHeight);
	// Set dialog box displayed in midpoint of the window
	CenterWindow();
}

BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HelpDlg message handlers


void HelpDlg::OnPaint()
{
	InitBackground();
	UpdateWindow();
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0,0,400,400,&m_dcMem,0,0,SRCCOPY);
}

