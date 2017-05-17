// ProiectDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Windows.h"

// CProiectDlg dialog
class CProiectDlg : public CDialog
{
// Construction
public:
	CProiectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROIECT_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShow();
	
	
	CEdit my_edit;
	CListCtrl my_list;

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton ShowButton;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


