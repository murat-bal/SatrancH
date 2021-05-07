#pragma once
#include "satranchdoc.h"

// CChatDialog dialog

class CChatDialog : public CDialog
{
	DECLARE_DYNAMIC(CChatDialog)

public:
	CChatDialog(CWnd* pParent = NULL, CSatrancHDoc *doc=NULL);   // standard constructor
	virtual ~CChatDialog();

// Dialog Data
	enum { IDD = IDD_CHATDIALOG };
	CSatrancHDoc *pDoc;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnChangeEditchat();
	void displayMsg(CString msg);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};
