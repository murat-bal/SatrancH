// SatrancHDoc.h : interface of the CSatrancHDoc class
//


#pragma once

#include "afxtempl.h"
#include "afxsock.h"

class CSatrancHSoc;
class CMsg;
class CChatDialog;

struct CMoveInfo{
	CPoint src;
	CPoint dst;
	int undoTas;
	CPoint roksrc;
	CPoint rokdst;
};

class CSatrancHDoc : public CDocument
{
protected: // create from serialization only
	CSatrancHDoc();
	DECLARE_DYNCREATE(CSatrancHDoc)

// Attributes
public:
	int akilliTahta[8][8];
	enum taslar  {bos,piyon,fil,at,kale,vezir,sah};
	enum tasType {siyah,beyaz}; 
	tasType siraKimde;
	tasType benKimim;
	CPoint secilenKare;
	
/*
	CPoint undosrc;
	CPoint undodst;
	tasType undotas;

	CPoint undoroksrc;
	CPoint undorokdst;
*/

	CArray<CMoveInfo*, CMoveInfo*> MoveList;

	CString myName;
	CString rName;
	
	unsigned long siyahTimer;
	unsigned long beyazTimer;

	CSatrancHSoc *m_Listener;
	CSatrancHSoc *m_pSocket;
	CSocketFile *m_pFile;
	CArchive *m_pArchiveIn;
	CArchive *m_pArchiveOut;
	CChatDialog *chat;


// Operations
public:
	void initTable();
	int checkIfOnTable(CPoint);
	CPoint mapMouseCoord(CPoint);
	CPoint TblToScrCoord(CPoint);
	int validMove(CPoint, CPoint);
	void doMove(CPoint, CPoint);
	void redraw();
// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void initServer();
	BOOL ConnectSocket(LPCTSTR lpszAddress, UINT nPort);
	BOOL ListenSocket(UINT nPort);

// Implementation
public:
	virtual ~CSatrancHDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DispMoveList();
	CString MovetoStr(CMoveInfo *inf);
	void clearMoveList();
	afx_msg void OnFileNew();
	afx_msg void OnFileConnect();
	void receiveMsg(void);
	void processPendingReads(void);
	int DisplayMsg(CMsg *msg);
	void doMoveMsg(CMsg *msg);
	void processAccept(void);
	afx_msg void OnEditUndo();
	void closeConnection(void);
	BOOL sendMessage(CString str);
};


