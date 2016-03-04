#pragma once


// CGameResult dialog

class CGameResult : public CDialogEx
{
	DECLARE_DYNAMIC(CGameResult)

public:
	CGameResult(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGameResult();
	int TotalCombo;
	int TotalScore;
	int TimeBonus;
	virtual BOOL OnInitDialog();
// Dialog Data
	enum { IDD =IDD_GAME_RESULT};

protected:

	CDC m_dcMem;
	HICON m_hIcon;
	void ShowScore(void);
	void ShowCombo(void);
	void ShowBonus(void);
	void InitBackground (void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void UpdateWindow(void);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
