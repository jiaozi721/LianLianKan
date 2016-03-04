// GameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "global.h"
#include "HelpDlg.h"
#include "GameResult.h"

// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	ComboScore = 0;
	m_combo_check1 = 0;
	m_combo_check2 = 0;
	m_combo = false;
	m_bFirstPoint = true;
	m_bPlaying = false;
	TotalCombo = 0;
	TimeBonus = 0;
	Output_combo = false;
	mute = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDB_MAIN_BG);

	m_ptGameEnd.x = MAX_COL*PIC_WIDTH+MAP_LEFT;
	m_ptGameEnd.y = MAX_ROW*PIC_HEIGHT+MAP_TOP;

	m_rtGameRect.SetRect(m_ptGameTop,m_ptGameEnd);

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_GAME_TIME,m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_REARRANGE, &CGameDlg::OnClickedBtnRearrange)
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnBnClickedBtnPrompt)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BUTTON5, &CGameDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BTN_MUTE, &CGameDlg::OnBnClickedBtnMute)
END_MESSAGE_MAP()
// CGameDlg message handlers

BOOL CGameDlg::OnInitDialog()
{
	//mainBGM();
	CDialogEx::OnInitDialog();
	InitBackground();
	InitElement();
	InitMask();
	InitComboMask();
	InitComboInit();
	Pause();
	UpdateWindow();
	Score = 0;
	ShowScore();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this);
	dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
}

void CGameDlg::InitSetRowCol(int row,int col,int time)
{
	m_GameC.CRow = row;
	m_GameC.CCol = col;
	SetTime = time;
	SetRow = row;
	SetCol = col;
}

void CGameDlg::InitBackground()
{
	CClientDC dc(this);
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_GAME_BG);
	m_back.CreateCompatibleDC(&dc);
	m_back.SelectObject(bmpMain);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpmen;
	bmpmen.CreateCompatibleBitmap(&dc,800,600);
	m_dcMem.SelectObject(bmpmen);

	m_dcMem.BitBlt(0,0,800,600,&m_back,0,0,SRCCOPY);
}

void CGameDlg::InitComboInit(void)
{
	CClientDC dc(this);
	m_dcComboInit.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_GAME_COMBO_INIT);
	m_dcComboInit.SelectObject(bmp);
}

void CGameDlg::InitComboMask(void)
{
	CClientDC dc(this);
	m_dcComboMask.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_GAME_COMBO_MASK);
	m_dcComboMask.SelectObject(bmp);
}


void CGameDlg::InitElement(void)
{
	CClientDC dc(this);
	m_dcElement.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_FRUIT_ELEMENT);
	m_dcElement.SelectObject(bmp);
}

void CGameDlg::InitMask(void)
{
	CClientDC dc(this);
	m_dcMask.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_FRUIT_MASK);
	m_dcMask.SelectObject(bmp);
}

void CGameDlg::Pause(void)
{
	CClientDC dc(this);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_GAME_PAUSE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(bmp);
}

void CGameDlg::PauseMask(void)
{
	CClientDC dc(this);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_GAME_PAUSEMASK);
	m_dcPauseMask.CreateCompatibleDC(&dc);
	m_dcPauseMask.SelectObject(bmp);
}

void CGameDlg::Combo(void)
{
	m_dcMem.BitBlt(MAP_LEFT,MAP_TOP,m_ptGameEnd.x,m_ptGameEnd.y, &m_dcComboMask, 0, 0, SRCPAINT);
	m_dcMem.BitBlt(MAP_LEFT,MAP_TOP,m_ptGameEnd.x,m_ptGameEnd.y, &m_dcComboInit, 0,0, SRCAND);
}

void CGameDlg::UpdateMap(void)
{
	m_dcMem.BitBlt(0,0,800,600,&m_back,0,0,SRCCOPY);
	for(int i=0; i<SetRow;i++)
	{
		for(int j = 0; j < SetCol ; j++)
		{ 
			m_dcMem.BitBlt(MAP_LEFT+j*PIC_WIDTH, MAP_TOP+i*PIC_HEIGHT, PIC_WIDTH, PIC_HEIGHT, &m_dcMask, 0, m_GameC.GetElement(i,j)*PIC_HEIGHT, SRCPAINT);
			m_dcMem.BitBlt(MAP_LEFT+j*PIC_WIDTH, MAP_TOP+i*PIC_HEIGHT, PIC_WIDTH, PIC_HEIGHT, &m_dcElement, 0,m_GameC.GetElement(i,j)*PIC_HEIGHT, SRCAND);
		}
	}
	
	InvalidateRect(m_rtGameRect,FALSE);
}

void CGameDlg::UpdateWindow(void)
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

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(point.y<m_ptGameTop.y || point.x<m_ptGameTop.x || !m_bPlaying || m_bPause)
	{
		CDialogEx::OnLButtonUp(nFlags, point);
	}
	else{
	if(!m_GameC.IsWin())
	{
	int nRow = (point.y-m_ptGameTop.y)/m_sizeElem.cy;
	int nCol = (point.x-m_ptGameTop.x)/m_sizeElem.cx;
	
	if( m_GameC.GetElement(nRow,nCol)!=BLANK && nRow < SetRow && nCol < SetCol)
	{
		if(m_bFirstPoint) //the First Point
		{
			m_bFirstPoint = false;
			DrawTipFrame(nRow,nCol);
			m_GameC.SetFirstPoint(nRow,nCol);
			if(!mute)
			m_nSound.Select();
		}
		else              //the Second Point
		{
			m_bFirstPoint = true;
			DrawTipFrame(nRow,nCol);
			m_GameC.SetSecPoint(nRow,nCol);
			Vertex avPath[MAX_SAVED_VERTEX_NUM];
			if(!mute)
			m_nSound.Select();
			if(m_GameC.Link(avPath,vex))
			{
				DrawTipLine(avPath,vex);
				if(!mute)
				m_nSound.Erase();
				Score+=10;

				ShowScore();
				if(!m_combo)
				{
					m_combo_check1 = m_GameProgress.GetPos();
					m_combo = true;
				}
				else if(m_combo)
				{
					m_combo_check2 = m_GameProgress.GetPos();
					m_combo = false;
				}
				int firsttime,lasttime;
				(m_combo_check1 > m_combo_check2)?  (firsttime = m_combo_check1, lasttime = m_combo_check2) : (firsttime = m_combo_check2, lasttime = m_combo_check1);
				if(firsttime - lasttime < 3)
				{
					Output_combo = true;
					TotalCombo += 1;
					ComboScore += 5;
					Score +=ComboScore;
					ShowScore();	
				}
				else
				{
					ComboScore = 0;	
				}
							
			}
		
		UpdateMap();
		if(Output_combo)
		{
			Combo();
			Output_combo = false;
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect,FALSE);
		
		}
	}
	}
	else
	{
		if(!mute){
		m_nSound.Stop();
		m_nSound.Win();
		}
		m_bPlaying = false;
		int Lefttime = m_GameProgress.GetPos() ;
		TimeBonus =  (double)Score*((double)Lefttime/300);
		CGameResult result;
		result.TotalScore = Score+TimeBonus;
		result.TotalCombo = TotalCombo;
		result.TimeBonus = TimeBonus;
		result.DoModal();


	}
	}
	
}



void CGameDlg::DrawTipLine(Vertex asvPath[MAX_SAVED_VERTEX_NUM],int nVexnum)
{
	
	CClientDC dc(this);
	CPen penLine(PS_SOLID,2,RGB(0,255,0));
	CPen* pOldPen = dc.SelectObject(&penLine);
	
	for(int i = 0 ; i<nVexnum-1; i++)
	{
		dc.MoveTo(m_ptGameTop.x + asvPath[i].col*m_sizeElem.cx + m_sizeElem.cx/2,
		m_ptGameTop.y+asvPath[i].row*m_sizeElem.cy+m_sizeElem.cy/2);
	dc.LineTo(m_ptGameTop.x + asvPath[i+1].col*m_sizeElem.cx+m_sizeElem.cx/2,
		m_ptGameTop.y+asvPath[i+1].row*m_sizeElem.cy+m_sizeElem.cy/2);
	}
	Combo();
	dc.SelectObject(pOldPen);

}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{

	CDC* dc = GetDC();
	CBrush brush;

	brush.CreateSolidBrush(RGB(233,43,43));
	dc->SelectObject(brush);
	
	RECT rect = { m_ptGameTop.x + nCol*m_sizeElem.cx,  m_ptGameTop.y + nRow*m_sizeElem.cy, 
		m_ptGameTop.x + (nCol+1)*m_sizeElem.cx, m_ptGameTop.y + (nRow+1) *m_sizeElem.cy};
	
	dc->FrameRect(&rect,&brush);
	ReleaseDC(dc);
}

void CGameDlg::ShowScore(void)
{
	CDC* pDC = GetDC();
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));
	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0,0,255));
	pDC->SetBkColor(RGB(255, 255, 255));
	CString stringScore;
	stringScore.Format(_T("Score: %4d"),Score);
	CSize size = pDC->GetTextExtent(stringScore, stringScore.GetLength());
	pDC->TextOutW(500,455, stringScore);
}

void CGameDlg::OnClickedBtnRearrange()
{
	if(!mute)
	m_nSound.ButtonClick();
	if(m_bPause == true || Score < 10) return;
	Score -= 10;
	ShowScore();
	m_GameC.ResetMap();
	UpdateMap();
}


void CGameDlg::OnBnClickedBtnPrompt()
{
	if(!mute)
	m_nSound.ButtonClick();
	if(m_bPlaying == false || m_bPause == true || Score < 5) return;

	Score -= 5;
	ShowScore();
	Vertex avsPath[MAX_SAVED_VERTEX_NUM];
	int n_vex;
	bool bSuc = m_GameC.Help(avsPath,n_vex);
	if(bSuc)
	{
		DrawTipFrame(avsPath[0].row,avsPath[0].col);
		DrawTipFrame(avsPath[n_vex-1].row,avsPath[n_vex-1].col);
		DrawTipLine(avsPath,n_vex);
	}
		UpdateMap();
		Sleep(200);
		InvalidateRect(m_rtGameRect,FALSE);

}
void CGameDlg::OnBnClickedBtnStart()
{
	if(!mute)
	m_nSound.ButtonClick();
	m_nSound.InGameBGM();
	m_GameProgress.SetRange(0,SetTime);
	m_GameProgress.SetStep(-1);
	m_GameProgress.SetPos(300);
	SetTimer(PLAY_TIMER_ID, 1000,NULL);
	ShowScore();
	DrawGameTime();
	GetDlgItem(IDC_BTN_START)->EnableWindow(m_bPlaying);
	m_bPlaying = true;
	m_bPause = false;
	m_GameC.StartGame();
	UpdateMap();
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && !m_bPause)
	{
		m_GameProgress.StepIt();
		DrawGameTime();
		if(m_GameProgress.GetPos()==10)
			if(!mute)
			m_nSound.TimeCaution();
		if (m_GameProgress.GetPos()==0)
		{
			if(!mute){
			m_nSound.Stop();
			m_nSound.Lose();
			}
			KillTimer(1);
			m_bPlaying = false;
			GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
			CGameResult result;
			result.TotalScore = Score+TimeBonus;
			result.TotalCombo = TotalCombo;
			result.TimeBonus = TimeBonus;
			result.DoModal();

		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime(void)
{

	CDC* pDC = GetDC();
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));
	CFont* oldFont = pDC->SelectObject(&font);

	pDC->SetBkColor(RGB(255,255,255));
	pDC->SetTextColor(RGB(255,0,0));

	CString strTime;
	strTime.Format(_T("Time Left: %3d"),m_GameProgress.GetPos());
	CSize size = pDC->GetTextExtent(strTime, strTime.GetLength());
	pDC->TextOutW(500,485, strTime);


}

void CGameDlg::OnBnClickedBtnPause()
{
	if(!mute)
	m_nSound.ButtonClick();
	if (!m_bPlaying)
		return;
	if (m_bPause)
	{
		m_bPause = false;
		UpdateMap();
		CWnd* pButton = GetDlgItem(IDC_BTN_PAUSE);
		pButton->SetWindowTextW(TEXT("Pause"));
	}
	else
	{
		m_bPause = true;
		m_dcMem.BitBlt(MAP_LEFT,MAP_TOP,m_ptGameEnd.x,m_ptGameEnd.y, &m_dcPauseMask, 0, 0 , SRCPAINT);
		m_dcMem.BitBlt(MAP_LEFT,MAP_TOP,m_ptGameEnd.x,m_ptGameEnd.y, &m_dcPause, 0,0, SRCAND);
		
		InvalidateRect(m_rtGameRect, FALSE);
		CWnd* pButton = GetDlgItem(IDC_BTN_PAUSE);
		pButton->SetWindowTextW(TEXT("Continue"));
	}
}


void CGameDlg::OnBnClickedButton5()
{
	if(!mute)
		m_nSound.ButtonClick();
	HelpDlg help;
	help.DoModal();
}


void CGameDlg::OnBnClickedBtnMute()
{
	if (mute)
	{
		mute = false;
		m_nSound.SetOn();
		CWnd* pButton = GetDlgItem(IDC_BTN_MUTE);
		pButton->SetWindowTextW(TEXT("MUSIC ON"));
	}
	else
	{
		mute = true;
		m_nSound.SetMute();
		CWnd* pButton = GetDlgItem(IDC_BTN_MUTE);
		pButton->SetWindowTextW(TEXT("Mute"));
	}
}
