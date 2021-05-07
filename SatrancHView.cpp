// SatrancHView.cpp : implementation of the CSatrancHView class
//

#include "stdafx.h"
#include "SatrancH.h"
#include "ChatDialog.h"

#include "SatrancHDoc.h"
#include "SatrancHView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSatrancHView

IMPLEMENT_DYNCREATE(CSatrancHView, CFormView)

BEGIN_MESSAGE_MAP(CSatrancHView, CFormView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CSatrancHView construction/destruction

CSatrancHView::CSatrancHView()
	: CFormView(CSatrancHView::IDD)
{
	// TODO: add construction code here
    tasResim.LoadBitmap(IDB_TASLAR);
    tasResimMaske.LoadBitmap(IDB_TASLARMASKE);
}

CSatrancHView::~CSatrancHView()
{
}

void CSatrancHView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CSatrancHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSatrancHView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	SetTimer(0, 1000, NULL);
}


// CSatrancHView diagnostics

#ifdef _DEBUG
void CSatrancHView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSatrancHView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSatrancHDoc* CSatrancHView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSatrancHDoc)));
	return (CSatrancHDoc*)m_pDocument;
}
#endif //_DEBUG


// CSatrancHView message handlers


void CSatrancHView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	int ndc = dc.SaveDC();
	CSatrancHDoc * tas = GetDocument();
	drawBoard(&dc);
	
	dc.RestoreDC(ndc);

	//		drawSquare(&dc, CPoint(0,0));  //TEST FUNCTION
	//dc.DrawEdge(CRect(14+72*0,14+72*0,80+72*0,80+72*0), /*EDGE_BUMP*/EDGE_SUNKEN, BF_RECT);

	
	//dc.SetBkMode();
	//dc.Rectangle(10+0*72, 10+0*72, 83+0*72, 83+0*72);



	//dc.Rectangle(10+0*72, 10+0*72, 83+0*72, 83+0*72);
	//dc.DrawEdge(CRect(14+72*0,14+72*0,80+72*0,80+72*0), /*EDGE_BUMP*/EDGE_SUNKEN, BF_RECT);
}

void CSatrancHView::drawSquare(CDC *dc,CPoint square)
{
	CSatrancHDoc *tas =  GetDocument();	
	CPoint scrCoord = tas->TblToScrCoord(square);
	CBrush wbr;   
	wbr.CreateSolidBrush(RGB(255,255,255));
    CBrush bbr;   
	bbr.CreateSolidBrush(RGB(128,128,128));
	if ((square.x+square.y) & 1)
	{
		//draw black square
		dc->SelectObject(bbr);
		dc->Rectangle(20+scrCoord.x*72, 20+scrCoord.y*72, 93+scrCoord.x*72, 93+scrCoord.y*72);
	}
	else
	{   
	   //draw white scrCoord
	   dc->SelectObject(wbr);
	   dc->Rectangle(20+scrCoord.x*72, 20+scrCoord.y*72, 93+scrCoord.x*72, 93+scrCoord.y*72);
    }
	//draw the tas on the scrCoord
	CPoint SrcTasYer;
	CPoint tblTasYer = scrCoord;
	if (tas->benKimim == CSatrancHDoc::beyaz)
		tblTasYer = CPoint (scrCoord.x,7-scrCoord.y);
		
	switch(tas->akilliTahta[tblTasYer.x][tblTasYer.y]){
		case CSatrancHDoc::bos ://bos
			return;
		case CSatrancHDoc::piyon : 
			SrcTasYer.x = 0; SrcTasYer.y = 0;
			break;
		case -CSatrancHDoc::piyon:
			SrcTasYer.x = 0; SrcTasYer.y = 70;
			break;
		case CSatrancHDoc::at:
			SrcTasYer.x = 72; SrcTasYer.y = 0;
			break;
		case -CSatrancHDoc::at:
			SrcTasYer.x = 72; SrcTasYer.y = 70;
			break;
		case CSatrancHDoc::fil:
			SrcTasYer.x = 2*72; SrcTasYer.y = 0;
			break;
		case -CSatrancHDoc::fil:
			SrcTasYer.x = 2*72; SrcTasYer.y = 70;
			break;
		case CSatrancHDoc::kale:
			SrcTasYer.x = 3*72; SrcTasYer.y = 0;
			break;
		case -CSatrancHDoc::kale:
			SrcTasYer.x = 3*72; SrcTasYer.y = 70;
			break;
		case CSatrancHDoc::vezir:
			SrcTasYer.x = 4*72; SrcTasYer.y = 0;
			break;
		case -CSatrancHDoc::vezir:
			SrcTasYer.x = 4*72; SrcTasYer.y = 70;
			break;
		case CSatrancHDoc::sah:
			SrcTasYer.x = 5*72; SrcTasYer.y = 0;
			break;
		case -CSatrancHDoc::sah:
			SrcTasYer.x = 5*72; SrcTasYer.y = 70;
			break;
	}
    CDC dcMemory;
    dcMemory.CreateCompatibleDC(dc);
	
	// Select the bitmap into the in-memory DC
    dcMemory.SelectObject(&tasResimMaske);
	dc->BitBlt(21+scrCoord.x*72,21+scrCoord.y*72 , 72, 70,&dcMemory,SrcTasYer.x,SrcTasYer.y,SRCAND);
	
	dcMemory.SelectObject(&tasResim);
	dc->BitBlt(21+scrCoord.x*72,21+scrCoord.y*72 , 72, 70,&dcMemory,SrcTasYer.x,SrcTasYer.y,SRCPAINT);
	
}
void CSatrancHView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CFormView::OnLButtonDown(nFlags, point);

	CClientDC dc(this); 
	CSatrancHDoc * tas = GetDocument();
	if(tas->checkIfOnTable(tas->secilenKare)){
       //daha önceden kare seçilmiþ
		drawSquare(&dc, tas->secilenKare);
		CPoint gidilenYer = tas->mapMouseCoord(point);
		CPoint sourceScr =  tas->TblToScrCoord(tas->secilenKare);
		CPoint destScr = tas->TblToScrCoord(gidilenYer);
		if(tas->checkIfOnTable(gidilenYer))
			if(tas->validMove(tas->secilenKare, gidilenYer)){
				tas->doMove(tas->secilenKare, gidilenYer);
				drawSquare(&dc, tas->secilenKare);
				drawSquare(&dc, gidilenYer);
				tas->secilenKare = CPoint(-1, -1);
				//tas->benKimim = tas->benKimim == CSatrancHDoc::siyah ? CSatrancHDoc::beyaz : CSatrancHDoc::siyah;
				for(int i=0;i<8;i++)
					for(int j=0;j<8;j++){
						drawSquare(&dc, CPoint(i,j));
					}
				DispMoveList();
				return;
			}
	}else{
		//daha önce kare seçilmemiþ 
	};

	if(tas->checkIfOnTable(tas->mapMouseCoord(point))){
		tas->secilenKare = tas->mapMouseCoord(point);
		CPoint sec =tas->TblToScrCoord(tas->secilenKare);

		CPen edge;	
		edge.CreatePen(PS_SOLID, 3, RGB(255, 0,0));
		dc.SelectObject(&edge);
		CBrush br;

		br.CreateSolidBrush(RGB(255, 0,0 ));
		dc.FrameRect(CRect(20+72*sec.x,20+72*sec.y,92+72*sec.x,92+72*sec.y), &br);
		dc.FrameRect(CRect(21+72*sec.x,21+72*sec.y,93+72*sec.x,93+72*sec.y), &br);
	}else tas->secilenKare = CPoint(-1,-1);;
	
}


void CSatrancHView::drawBoard(CDC * dc)
{

	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages

	CBrush wbr;   
	wbr.CreateSolidBrush(RGB(255,255,255));
    CBrush bbr;   

	bbr.CreateSolidBrush(RGB(0,0,0));
	CSatrancHDoc *tas =  GetDocument();	

	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++){
			drawSquare(dc, CPoint(i,j));
		}

	dc->SetBkColor(RGB(200,200,200));
	for( int i=0;i<8;i++){
		dc->TextOut(50+i*72, 30+8*72, CString(char('A'+i)));
		if(tas->benKimim == CSatrancHDoc::beyaz)
			dc->TextOut( 5, 50+(7-i)*72, CString(char('1'+i)));
		else
			dc->TextOut( 5, 50+i*72, CString(char('1'+i)));
	}

}

void CSatrancHView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	CFormView::OnUpdate(pSender, lHint, pHint);
}

void CSatrancHView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(!GetDocument()->m_pSocket)return;

	if(GetDocument()->siraKimde==CSatrancHDoc::siyah)
		GetDocument()->siyahTimer++;
	else 
		GetDocument()->beyazTimer++;

	CString wh = GetDocument()->benKimim==CSatrancHDoc::beyaz ? GetDocument()->myName : GetDocument()->rName;
	CString sh = GetDocument()->benKimim==CSatrancHDoc::siyah ? GetDocument()->myName : GetDocument()->rName;



	BlackName= (CStatic *)GetDlgItem(IDC_STATICBLACK);
	WhiteName=(CStatic *)GetDlgItem(IDC_STATICWHITE);
	BlackDisplay= (CEdit *)GetDlgItem(IDC_EDITBLACK);
	WhiteDisplay= (CEdit *)GetDlgItem(IDC_EDITWHITE);
	moveList= (CListBox *)GetDlgItem(IDC_MOVELIST);

	WhiteName->SetWindowText("Beyaz : " + wh );
	BlackName->SetWindowText("Siyah : " + sh);
	
	
	
	CString siyahTimer(CTimeSpan(GetDocument()->siyahTimer).Format("%H:%M:%S")); 
	//siyahTimer.Format("%d",GetDocument()->siyahTimer);
	CString beyazTimer(CTimeSpan(GetDocument()->beyazTimer).Format("%H:%M:%S")); 
	//beyazTimer.Format("%d",GetDocument()->beyazTimer);
	BlackDisplay->SetWindowText(siyahTimer);
	WhiteDisplay->SetWindowText(beyazTimer);

	CFormView::OnTimer(nIDEvent);
}

void CSatrancHView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	//CChatDialog *chat = (CChatDialog *)RUNTIME_CLASS(CChatDialog)->CreateObject();
	//chat->DoModal();
	
	

	CFormView::OnRButtonDown(nFlags, point);
}

void CSatrancHView::DispMoveList()
{
	CString moveItem;
	moveList= (CListBox *)GetDlgItem(IDC_MOVELIST);
	moveList->ResetContent();
	for(int i=0;i<GetDocument()->MoveList.GetSize();i++){
		
		if(i & 1){
			moveItem += " - ";
			moveItem += GetDocument()->MovetoStr(GetDocument()->MoveList[i]);
			moveList->AddString(moveItem);
			moveItem="";
		}else{
			moveItem= GetDocument()->MovetoStr(GetDocument()->MoveList[i]);
		}
	}
	moveList->AddString(moveItem);

}
