// SatrancHView.h : interface of the CSatrancHView class
//


#pragma once


class CChatDialog;
class CSatrancHView : public CFormView
{
protected: // create from serialization only
	CSatrancHView();
	DECLARE_DYNCREATE(CSatrancHView)

public:
	enum{ 
IDD = IDD_SATRANCH_FORM };

// Attributes
public:
	CSatrancHDoc* GetDocument() const;
	CBitmap tasResim;
	CBitmap tasResimMaske;

	CStatic *BlackName;
	CStatic *WhiteName;
	CEdit *BlackDisplay;
	CEdit *WhiteDisplay;
	CListBox *moveList;

    // Load a resource bitmap.
	
// Operations
public:
	void drawSquare(CDC *,CPoint);
// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CSatrancHView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void drawBoard(CDC * dc);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
		void DispMoveList();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in SatrancHView.cpp
inline CSatrancHDoc* CSatrancHView::GetDocument() const
   { return reinterpret_cast<CSatrancHDoc*>(m_pDocument); }
#endif


