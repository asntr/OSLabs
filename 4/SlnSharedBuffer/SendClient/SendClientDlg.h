// SendClientDlg.h : header file
//

#pragma once


// CSendClientDlg dialog
class CSendClientDlg : public CDialog
{
// Construction
public:
	CSendClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SENDCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString textToCopy;
	afx_msg LRESULT OnMessageSent(WPARAM, LPARAM);
};
