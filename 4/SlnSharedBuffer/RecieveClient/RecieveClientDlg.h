// RecieveClientDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CRecieveClientDlg dialog
class CRecieveClientDlg : public CDialog
{
// Construction
public:
	CRecieveClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RECIEVECLIENT_DIALOG };

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
	CEdit CMsgReciever;
	afx_msg LRESULT onMessageWasSent(WPARAM, LPARAM);
	CButton CButtonRecieve;
};
