#pragma once


#include "resource.h"
#include "GameControl.h"

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);		// standard constructor
	void UpdateWindow(void);
	void UpdateMap(void);
	virtual ~CGameDlg();
	void InitSetRowCol(int row = 10, int col = 16, int time = 180);
	Sound m_nSound;
	bool mute;
	enum { IDD = IDD_DIALOG_GAME };

protected:

	HICON m_hIcon;
	CDC m_dcMem;
	CDC m_back;
	CDC m_dcElement;
	CDC m_dcMask;
	CPoint m_ptGameTop;					// Start point of game zon
	CPoint m_ptGameEnd;
	CSize m_sizeElem;					//Element photo size
	CRect m_rtGameRect;					// game zone size
	CDC m_dcCache;						//cache memery DC
	CDC m_dcPause;						//memory DC of the pause map
	CDC m_dcComboInit;
	CDC m_dcComboMask;
	CRect m_TextRect;
	CDC m_dcPauseMask;

	bool Output_combo;
	bool m_combo;
	bool m_bPlaying;					//indicates whether any game is on going. True = yes ,False = no
	bool bSuc;
	bool m_bPause;						//pause mark, true for pause, false for un-pause
	bool m_bFirstPoint;					//Whether it is the first selected
	int vex;
	int SetRow;
	int SetCol;
	int SetTime;
	int Score;
	int m_combo_check1;
	int m_combo_check2;
	int ComboScore;
	int TotalCombo;
	int TotalScore;
	int TimeBonus;
	

	Vertex m_ptSelFirst;				//first selected point
	Vertex m_ptSelSec;					//second selected point
	CGameControl m_GameC;
	CGameLogic Logic;
	
	
	void InitBackground(void);
	void InitElement(void);
	void InitMask(void);
	void DrawGameTime(void);			//Draw game time
	void JudgeWin(void);				//Draw the game
	void Pause(void);
	void ShowScore(void);
	void InitComboInit(void);
	void InitComboMask(void);
	void Combo(void);
	void PauseMask(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	void DrawTipLine(Vertex asvPath[4],int nVexnum);
	void DrawTipFrame(int nRow, int nCol);

public:


	CProgressCtrl m_GameProgress;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnRearrange();
	afx_msg void OnBnClickedBtnPrompt();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawGameTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedBtnMute();
};
