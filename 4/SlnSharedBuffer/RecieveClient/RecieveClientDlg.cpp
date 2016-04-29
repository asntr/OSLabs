// RecieveClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RecieveClient.h"
#include "RecieveClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRecieveClientDlg dialog




CRecieveClientDlg::CRecieveClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecieveClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRecieveClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, CMsgReciever);
	DDX_Control(pDX, IDC_BUTTON1, CButtonRecieve);
}

BEGIN_MESSAGE_MAP(CRecieveClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CRecieveClientDlg::OnBnClickedButton1)
	ON_MESSAGE(uMsgId, onMessageWasSent)
END_MESSAGE_MAP()


// CRecieveClientDlg message handlers

BOOL CRecieveClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	ChangeWindowMessageFilter(uMsgId, 1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRecieveClientDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRecieveClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRecieveClientDlg::OnBnClickedButton1()
{
	SetDlgItemText(1000, CString(wcSharedBufferDLL));
	bIsMessageInBuffer = false;
	//CButtonRecieve.EnableWindow(0);
}

LRESULT CRecieveClientDlg::onMessageWasSent(WPARAM wParam, LPARAM lParam)
{
	//CButtonRecieve.EnableWindow(1);
	return 0;
}
