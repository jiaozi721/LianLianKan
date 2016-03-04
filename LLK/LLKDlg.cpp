
// LLKDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include "GameDlg.h"
#include "HelpDlg.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint(){};
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLLKDlg dialog




CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLLKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BNT_RELAX, &CLLKDlg::OnBnClickedBntRelax)
	ON_BN_CLICKED(IDC_BNT_LEVEL, &CLLKDlg::OnBnClickedBntLevel)
	ON_BN_CLICKED(IDC_BTN_HELP, &CLLKDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CLLKDlg::OnBnClickedBtnSetting)
END_MESSAGE_MAP()


// CLLKDlg message handlers

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	mute = false;
	// Add "About..." menu item to system menu.
	m_Sound.FirstScreen();
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	InitBackground();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
				
		CRect rect;
		GetClientRect(&rect);
		//Get client area size

		CFont font;
		font.CreatePointFont(200,_T("Courier New"));
	    
		CFont* oldFont;
	    //Select font type into DC
	    oldFont = dc.SelectObject (&font);
		
		CString strWel = _T("Welcome to LLK-Game");
	    
		
		dc.SetTextColor(RGB(0,255,0));
		dc.SetBkColor(RGB(255,0,0));
		
		//get text width and height
		CSize size;
		size = dc.GetTextExtent(strWel,strWel.GetLength());
		int x = (rect.Width() - size.cx)/2;
		int y = (rect.Height() - size.cy)/2;

		dc.TextOut(x,y,strWel);
		dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);		
		CDialogEx::OnPaint();
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKDlg::UpdateWindow(void)
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
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	// Set dialog box displayed in midpoint of the window
	CenterWindow();

}

void CLLKDlg::InitBackground()
{
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);
	m_dcMem.SelectObject(bmpMain);

}

void CLLKDlg::OnClickedBtnBasic()
{
	if(!mute){
	m_Sound.ButtonClick();
	m_Sound.SwapClick();}
	m_Sound.Stop();
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.InitSetRowCol(4,4,20);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
	//m_Sound.Stop();
	m_Sound.FirstScreen();
}


void CLLKDlg::OnBnClickedBntRelax()
{
	if(!mute){
	m_Sound.ButtonClick();
	m_Sound.SwapClick();}
	m_Sound.Stop();
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.InitSetRowCol(10,10,60);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
	//m_Sound.Stop();
	m_Sound.FirstScreen();

}


void CLLKDlg::OnBnClickedBntLevel()
{
	if(!mute){
	m_Sound.ButtonClick();
	m_Sound.SwapClick();}
	m_Sound.Stop();
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.InitSetRowCol();
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
	//
	m_Sound.FirstScreen();
	
}


void CLLKDlg::OnBnClickedBtnHelp()
{
	if(!mute){
	m_Sound.ButtonClick();
	m_Sound.SwapClick();}
	HelpDlg help;
	help.DoModal();
}


void CLLKDlg::OnBnClickedBtnSetting()
{
	if (mute)
	{
		mute = false;
		m_Sound.SetOn();
		CWnd* pButton = GetDlgItem(IDC_BTN_SETTING);
		pButton->SetWindowTextW(TEXT("MUSIC ON"));
	}
	else
	{
		mute = true;
		m_Sound.SetMute();
		CWnd* pButton = GetDlgItem(IDC_BTN_SETTING);
		pButton->SetWindowTextW(TEXT("Mute"));
	}
}
