// ChatDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SatrancH.h"
#include "ChatDialog.h"
#include "satranchdoc.h"
#include "satranchview.h"


// CChatDialog dialog

IMPLEMENT_DYNAMIC(CChatDialog, CDialog)

CChatDialog::CChatDialog(CWnd* pParent /*=NULL*/, CSatrancHDoc *doc)
	: CDialog(CChatDialog::IDD, pParent)
{
    pDoc=doc ;
}

CChatDialog::~CChatDialog()
{
}

void CChatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChatDialog, CDialog)
ON_EN_CHANGE(IDC_EDITCHAT, OnEnChangeEditchat)
END_MESSAGE_MAP()


// CChatDialog message handlers

void CChatDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	MessageBox("test");

	CDialog::OnOK();
}

BOOL CChatDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	MessageBox("test");

	return CDialog::OnNotify(wParam, lParam, pResult);
}



void CChatDialog::OnEnChangeEditchat()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	//MessageBox("kjhkjhkj");
	CEdit *msg = (CEdit *) GetDlgItem(IDC_EDITCHAT);
	CString s;
	msg->GetWindowText( s );
	
	if(strchr(s, 13)){
//		displayMsg(s); 
		msg->SetWindowText("");
//		displayMsg(s);
		pDoc->sendMessage(s);

	}
	
}

void CChatDialog::displayMsg(CString msg)
{
	ShowWindow(SW_SHOW);

		CEdit *lst=(CEdit *) GetDlgItem(IDC_EDITVIEW);
		CString txt;
		lst->GetWindowText( txt );
		txt = txt + msg;
		lst->SetWindowText ( txt );
		SCROLLINFO inf;

		lst->SetSel(txt.GetLength(), txt.GetLength());
/*

		lst->GetScrollInfo(SB_VERT, &inf);
		lst->SetScrollPos(SB_VERT, inf.nMax);
		lst->ScrollWindow(0, 0);
		lst->ScrollWindow(0, inf.nMax);
		lst->UpdateData();
		*/
}

BOOL CChatDialog::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::PreCreateWindow(cs);
}
