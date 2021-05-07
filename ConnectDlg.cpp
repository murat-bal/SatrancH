// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SatrancH.h"
#include "ConnectDlg.h"


// CConnectDlg dialog

IMPLEMENT_DYNAMIC(CConnectDlg, CDialog)
CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{

}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIOCONNECT, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIOLISTEN, OnBnClickedRadio3)
END_MESSAGE_MAP()


// CConnectDlg message handlers


void CConnectDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    CEdit *e1=(CEdit *) GetDlgItem(IDC_EDITNAME);
	CEdit *e2=(CEdit *) GetDlgItem(IDC_EDITSERVER);
	CButton *b1 = (CButton *) GetDlgItem(IDC_RADIOCONNECT);
	//e1->GetWindowText(
	e1->GetWindowText(myName);
	e2->GetWindowText(svr);
	isServer = ! b1->GetCheck();
	CDialog::OnOK();
}

void CConnectDlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	CEdit *e2=(CEdit *) GetDlgItem(IDC_EDITSERVER);
	CButton *b1 = (CButton *) GetDlgItem(IDC_RADIOCONNECT);
	CButton *b2 = (CButton *) GetDlgItem(IDC_RADIOLISTEN);
	if(b1->GetCheck()!=BST_CHECKED)e2->ShowWindow(SW_HIDE);
	else e2->ShowWindow(SW_SHOW);
}

void CConnectDlg::PreInitDialog()
{
	// TODO: Add your specialized code here and/or call the base class
	CButton *b1 = (CButton *) GetDlgItem(IDC_RADIOLISTEN);
	b1->SetCheck(BST_CHECKED);
	CEdit *e2=(CEdit *) GetDlgItem(IDC_EDITSERVER);
	e2->ShowWindow(SW_HIDE);

	CDialog::PreInitDialog();
}
