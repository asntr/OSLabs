// SendClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SendClient.h"
#include "SendClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSendClientDlg dialog




CSendClientDlg::CSendClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendClientDlg::IDD, pParent)
	, textToCopy(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSendClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, textToCopy);
}

BEGIN_MESSAGE_MAP(CSendClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSendClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSendClientDlg message handlers

BOOL CSendClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	uMsgId = RegisterWindowMessage(L"MY_MESSAGESENT");

	ChangeWindowMessageFilter(uMsgId, 1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSendClientDlg::OnPaint()
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
HCURSOR CSendClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSendClientDlg::OnBnClickedButton1()
{
	DWORD er;
	if(bIsMessageInBuffer)
		CSendClientDlg::MessageBoxW(L"you can't send message until previous isn't readen");
	else {
		GetDlgItemTextW( 1000, wcSharedBufferDLL, 500);
		bIsMessageInBuffer = true;
		PostMessageA(HWND_BROADCAST, uMsgId, 0, 0);
		er = GetLastError();
	}
}
