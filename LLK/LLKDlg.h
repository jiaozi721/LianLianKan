// LLKDlg.h : header file
//

#pragma once

#include <afxtempl.h>


// CLLKDlg dialog
class CLLKDlg : public CDialogEx
{
// Construction
public:
	CLLKDlg(CWnd* pParent = NULL);	// standard constructor
	Sound m_Sound;

// Dialog Data
	enum { IDD = IDD_LLK_DIALOG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:


// Implementation
protected:
	bool mute;
	HICON m_hIcon;
	CDC m_dcMem;//buffer !!!
	void InitBackground(void);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClickedBtnBasic();
	void UpdateWindow(void);
	afx_msg void OnBnClickedBntRelax();
	afx_msg void OnBnClickedBntLevel();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedBtnSetting();
};
