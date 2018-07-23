// MD5CalcDlg.h : header file
//

#if !defined(AFX_MD5CALCDLG_H__6C39E36C_4564_4C15_88AD_5416D59FB618__INCLUDED_)
#define AFX_MD5CALCDLG_H__6C39E36C_4564_4C15_88AD_5416D59FB618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMD5CalcDlg dialog

class CMD5CalcDlg : public CDialog
{
// Construction
public:
	CMD5CalcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMD5CalcDlg)
	enum { IDD = IDD_MD5CALC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMD5CalcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMD5CalcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnCalc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MD5CALCDLG_H__6C39E36C_4564_4C15_88AD_5416D59FB618__INCLUDED_)
