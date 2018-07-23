// MD5Calc.h : main header file for the MD5CALC application
//

#if !defined(AFX_MD5CALC_H__C3457FBA_5F46_496B_AAD5_DFB800B65E7F__INCLUDED_)
#define AFX_MD5CALC_H__C3457FBA_5F46_496B_AAD5_DFB800B65E7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMD5CalcApp:
// See MD5Calc.cpp for the implementation of this class
//

class CMD5CalcApp : public CWinApp
{
public:
	CMD5CalcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMD5CalcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMD5CalcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MD5CALC_H__C3457FBA_5F46_496B_AAD5_DFB800B65E7F__INCLUDED_)
