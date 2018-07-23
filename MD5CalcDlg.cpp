// MD5CalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MD5Calc.h"
#include "MD5CalcDlg.h"
#include "md5.h"
#include <math.h>
#include "time.h"
#include "windows.h"
#include <mmsystem.h>  // timeGetTime


#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMD5CalcDlg dialog

CMD5CalcDlg::CMD5CalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMD5CalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMD5CalcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMD5CalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMD5CalcDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMD5CalcDlg, CDialog)
	//{{AFX_MSG_MAP(CMD5CalcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDBROWSE, OnBrowse)
	ON_BN_CLICKED(IDCALC, OnCalc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMD5CalcDlg message handlers

BOOL CMD5CalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMD5CalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMD5CalcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMD5CalcDlg::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, NULL, this);

	if(dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDIT1, dlg.GetPathName());
}

unsigned int Endian_Conv(unsigned int dword)
 {
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}

void CMD5CalcDlg::OnCalc() 
{
	// TODO: Add your control notification handler code here
	char* str1 = new char[400];
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1, 400);
	HANDLE hFile = NULL;
	DWORD dwBytesRead, FileSize = 0;
	BYTE * FileOffset;

	try
	{

		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 0)  // if File not checked
		{
		md5_context context = md5::CalculateMD5((unsigned char*)str1, strlen(str1));

		if (!context.Failed)
		{
		char *s = new char[33];
		sprintf(s, "%08x%08x%08x%08x", Endian_Conv(context.A), Endian_Conv(context.B), Endian_Conv(context.C), Endian_Conv(context.D));
		GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		}
		else
		{
		GetDlgItem(IDC_EDIT2)->SetWindowText("MD5 failed!");
		}

		}
		else
		{
		// Open the file
		hFile = CreateFile(str1,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_SEQUENTIAL_SCAN,
			NULL);

		if(hFile != INVALID_HANDLE_VALUE)
		{

FileSize = GetFileSize (hFile,0);
FileOffset = (unsigned char *)GlobalAlloc (GMEM_ZEROINIT,FileSize+64);  // + needed for avoiding buffer overflow

if (ReadFile (hFile,FileOffset,FileSize,&dwBytesRead,0) != 0) 
{

md5_context context = md5::CalculateMD5(FileOffset, FileSize);

if (!context.Failed)
{
char *s = new char[33];
sprintf(s, "%08x%08x%08x%08x", Endian_Conv(context.A), Endian_Conv(context.B), Endian_Conv(context.C), Endian_Conv(context.D));
GetDlgItem(IDC_EDIT2)->SetWindowText(s);
}
else
{
GetDlgItem(IDC_EDIT2)->SetWindowText("MD5 failed!");
}


}

		else
		{
		GetDlgItem(IDC_EDIT2)->SetWindowText("Failed to read file!");
		}

GlobalFree(FileOffset);

		}  //
		else
		{
		GetDlgItem(IDC_EDIT2)->SetWindowText("Invalid file handle!");
		}

	}  // end of big is file checbox checked

	}
	catch(...)
	{

		GetDlgItem(IDC_EDIT2)->SetWindowText("ERROR");
	}

	if(hFile != NULL) CloseHandle(hFile);
}
