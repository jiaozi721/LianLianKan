#pragma once


// HelpDlg dialog

class HelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDlg)

public:
	HelpDlg(CWnd* pParent = NULL);						// standard constructor
	virtual ~HelpDlg();
	enum { IDD = IDD_DIALOG_HELP };

protected:
	CDC m_dcMem;			
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitBackground(void);
	void UpdateWindow(void);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
