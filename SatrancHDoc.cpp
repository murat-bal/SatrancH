// SatrancHDoc.cpp : implementation of the CSatrancHDoc class
//

#include "stdafx.h"
#include "SatrancH.h"
#include "ConnectDlg.h"
#include "SatrancHSoc.h"
#include "chatdialog.h"
#include "satrancHview.h"
#include "msg.h"

#include "stddef.h"

#include "SatrancHDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSatrancHDoc

IMPLEMENT_DYNCREATE(CSatrancHDoc, CDocument)

BEGIN_MESSAGE_MAP(CSatrancHDoc, CDocument)
	ON_COMMAND(ID_FILE_CONNECT, OnFileConnect)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
END_MESSAGE_MAP()


// CSatrancHDoc construction/destruction

CSatrancHDoc::CSatrancHDoc()
{
	// TODO: add one-time construction code here
	//initTable();
//	m_bAutoChat = FALSE;
	m_pSocket = NULL;
	m_Listener = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
	chat = NULL;

}

CSatrancHDoc::~CSatrancHDoc()
{
}

BOOL CSatrancHDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	/*
 if(m_Listener) delete m_Listener;
	m_Listener = NULL;

	if(m_pSocket){
		delete m_pArchiveOut;
		delete m_pArchiveIn;
		delete m_pFile;
		delete m_pSocket;
		m_pSocket = NULL;
	}
*/

    initTable();
	siyahTimer=0;
	beyazTimer=0;

	clearMoveList();

	if(m_pSocket){
		CMsg msg(this);
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}


	redraw();

	return TRUE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

}




// CSatrancHDoc serialization

void CSatrancHDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++){
				ar <<  akilliTahta[i][j];
			}
		ar << (int)benKimim;
		ar << (int)siraKimde;
		secilenKare = CPoint(-1,-1);
		ar << MoveList.GetSize();
		for(int i=0;i<MoveList.GetSize();i++){
			ar.Write(MoveList[i], sizeof(CMoveInfo));
		}

	}
	else
	{
		// TODO: add loading code here
		clearMoveList();
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++){
				ar >>  akilliTahta[i][j];
			}
        int x;
		ar >> x;
		benKimim = (tasType) x;
		ar >> x;
		siraKimde = (tasType)x;

		secilenKare = CPoint(-1,-1);

		int nMove;
		ar >> nMove;
		for(int i=0;i<nMove;i++){
			CMoveInfo *inf = new CMoveInfo;
			ar.Read(inf, sizeof(CMoveInfo));
			MoveList.Add(inf);
		}
	}
}


// CSatrancHDoc diagnostics

#ifdef _DEBUG
void CSatrancHDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSatrancHDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSatrancHDoc commands
void CSatrancHDoc::initTable() 
{
	for (short i=0;i<8;i++)	
		for (short j=0;j<8;j++)	
		{
		akilliTahta[i][j]=bos;
		}
	akilliTahta[0][0]=piyon;
	for (int i=0;i<8;i++)
		{
		akilliTahta[i][1]=piyon;
		akilliTahta[i][6]=-piyon;
		}
	akilliTahta[0][0]=kale;
	akilliTahta[7][0]=kale;
	akilliTahta[0][7]=-kale;
	akilliTahta[7][7]=-kale;
	akilliTahta[1][0]=at;
	akilliTahta[6][0]=at;
	akilliTahta[1][7]=-at;
	akilliTahta[6][7]=-at;
	akilliTahta[2][0]=fil;
	akilliTahta[5][0]=fil;
	akilliTahta[2][7]=-fil;
	akilliTahta[5][7]=-fil;
	akilliTahta[4][0]=sah;
	akilliTahta[4][7]=-sah;
	akilliTahta[3][0]=vezir;
	akilliTahta[3][7]=-vezir;
	
	benKimim = beyaz; 
	siraKimde = beyaz;

	secilenKare=CPoint(-1,-1);
}

CPoint CSatrancHDoc::mapMouseCoord(CPoint mouseCoord)
{
	if (benKimim == CSatrancHDoc::beyaz)
		return CPoint( (mouseCoord.x-21)/72,7-(mouseCoord.y-21)/72);
	else
		return CPoint( (mouseCoord.x-21)/72,(mouseCoord.y-21)/72);
		
}
CPoint CSatrancHDoc::TblToScrCoord(CPoint coord)
{
	if (benKimim == CSatrancHDoc::beyaz)
		return CPoint( coord.x, 7-coord.y);
	else
		return CPoint( coord.x, coord.y);
};

int CSatrancHDoc::checkIfOnTable(CPoint p)
{
	return(p.x >= 0 && p.x<=7 && p.y>=0 && p.y <=7);
}

void CSatrancHDoc::doMove(CPoint src, CPoint dst)
{	
	if(checkIfOnTable(src) && checkIfOnTable(dst)){
	
	//þahla rok mu yapýlýyor..
	CPoint kaleYer(-1,-1);
	CPoint kaleDst(-1,-1);
    
	//rok mu?
	if(abs(akilliTahta[src.x][src.y]) == sah && abs(dst.x-src.x) == 2 )
		{
		
			//kucuk rok mu?
			//saða doðru mu rok yapýyor(Beyaza göre)
			if (dst.x-src.x == -2) 
			{
			  if (akilliTahta[src.x][src.y] == sah){
				 kaleYer = CPoint (0,0);
				 kaleDst = CPoint (3,0);
			  }else {
				 kaleYer = CPoint (0,7);
				 kaleDst = CPoint (3,7);
			  }  
			}else{
				
			  if (akilliTahta[src.x][src.y] == sah){
				 kaleYer = CPoint (7,0);
				 kaleDst = CPoint (5,0);
			  }else {
				 kaleYer = CPoint (7,7);
				 kaleDst = CPoint (5,7);
			  } 
			  if(abs(akilliTahta[kaleYer.x][kaleYer.y])!=kale) kaleYer=CPoint(-1,-1);
			  if((akilliTahta[kaleDst.x][kaleDst.y])!=bos) kaleYer=CPoint(-1,-1);
			}    
		}
				
 	
/*		undotas = (CSatrancHDoc::tasType)akilliTahta[dst.x][dst.y];
		undosrc = src;
		undodst = dst;

		undoroksrc=kaleYer;
		undorokdst=kaleDst;
*/

		CMoveInfo *inf= new CMoveInfo;
		inf->dst = dst;
		inf->src = src;
		inf->undoTas = akilliTahta[dst.x][dst.y];
		inf->roksrc = kaleYer;
		inf->rokdst = kaleDst;
		MoveList.Add(inf);


		akilliTahta[dst.x][dst.y] =  akilliTahta[src.x][src.y];
		akilliTahta[src.x][src.y] = bos;
	
		if(checkIfOnTable(kaleYer)){
			akilliTahta[kaleDst.x][kaleDst.y] =  akilliTahta[kaleYer.x][kaleYer.y];
			akilliTahta[kaleYer.x][kaleYer.y] = bos;

		}
	
	
	}
	if(siraKimde==siyah)siraKimde=beyaz; 
		               else siraKimde=siyah;

	if(m_pSocket){
		CMsg msg(this);
		msg.m_Type = CMsg::moveMsg;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}

int CSatrancHDoc::validMove(CPoint src, CPoint dst)
{
	if (akilliTahta[src.x][src.y]== bos) return 0; //Kurallar ... 
	if ((akilliTahta[src.x][src.y]*akilliTahta[dst.x][dst.y])> 0 ) return 0; //kendi tasini yeme
	if ((akilliTahta[src.x][src.y] > 0 && benKimim == siyah) ||
        (akilliTahta[src.x][src.y] < 0 && benKimim == beyaz))return 0;		
	if (!m_pSocket)return 0;
	if (siraKimde!=benKimim)return(0);
	
	return 1;
}
void CSatrancHDoc::OnFileNew()
{
	// TODO: Add your command handler code here
	initTable();
}

void CSatrancHDoc::OnFileConnect()
{
	// TODO: Add your command handler code here
	CConnectDlg *dlg = new CConnectDlg();
	if(dlg->DoModal()==IDOK){
		//ConnectSocket("localhost", 1973);
		myName = dlg->myName;
		if(dlg->isServer)ListenSocket(1973);
		else ConnectSocket(dlg->svr, 1973);		
	};	
}


void CSatrancHDoc::receiveMsg(void)
{
	CMsg msg(this);

	TRY
	{
		msg.Serialize(*m_pArchiveIn);

/*		while(!msg.m_msgList.IsEmpty())
		{
			CString temp = msg.m_msgList.RemoveHead();
			DisplayMsg(temp);
		}
*/
		if(msg.m_Type == CMsg::chatMsg){
			DisplayMsg(&msg);
		}else{
			doMoveMsg(&msg);
		}

	}
	CATCH(CFileException, e)
	{
//		m_bAutoChat = FALSE;
		m_pArchiveOut->Abort();

		CString strTemp;
		/*
		if (strTemp.LoadString(IDS_SERVERRESET))
			DisplayMsg(strTemp);
		if (strTemp.LoadString(IDS_CONNECTIONCLOSED))
			DisplayMsg(strTemp);
		*/
	}
	END_CATCH

	/*
	if (msg.m_bClose)
	{
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
		delete m_pFile;
		m_pFile = NULL;
		delete m_pSocket;
		m_pSocket = NULL;
	}
	*/

}

void CSatrancHDoc::processPendingReads(void)
{
	do
	{
		receiveMsg();

		if (m_pSocket == NULL)
			return;
	}
	while(!m_pArchiveIn->IsBufferEmpty());
}

int CSatrancHDoc::DisplayMsg(CMsg *msg)
{
	rName = msg->myName;
	if(msg->msg.GetLength()){
	   //TODO display the incoming message	
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CSatrancHView* pView = (CSatrancHView* )GetNextView(pos);
			CString fMsg;
			fMsg += msg->myName;
			fMsg += " : ";
			fMsg += msg->msg;
			chat->displayMsg(fMsg);
			break;
		}   
	}
	return 0;
}

void CSatrancHDoc::doMoveMsg(CMsg *msg)
{
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			akilliTahta[i][j] = msg->table[i][j];

	/*
	if(checkIfOnTable(msg->lastMove.src)){
		CMoveInfo *inf= new CMoveInfo;
		*inf = msg->lastMove;
		MoveList.Add(inf);
	}
	*/
	clearMoveList();
	for(int i=0;i<msg->MoveList.GetSize();i++){
		MoveList.Add(msg->MoveList[i]);
	}

    //siraKimde=benKimim;
	rName = msg->myName;
	siraKimde = (CSatrancHDoc::tasType)msg->siraKimde;
	benKimim = (msg->benKimim == CSatrancHDoc::siyah) ? CSatrancHDoc::beyaz : CSatrancHDoc::siyah;
	/*
	if(msg->benKimim==siyah)
	benKimim = msg->benKimim;
	*/

//repaint window
   redraw();
}


BOOL CSatrancHDoc::ConnectSocket(LPCTSTR lpszAddress, UINT nPort)
{
//	m_strHandle = lpszHandle;

	if(m_Listener) delete m_Listener;
	m_Listener = NULL;

	if(m_pSocket){
		delete m_pArchiveOut;
		delete m_pArchiveIn;
		delete m_pFile;
		delete m_pSocket;
		m_pSocket = NULL;
	}

	if(chat)delete chat;
	chat = NULL;

	chat = new CChatDialog(NULL, this);
	if(!chat->Create(IDD_CHATDIALOG, NULL))
		return FALSE;

	chat->ShowWindow(SW_SHOW);



	m_pSocket = new CSatrancHSoc(this);

	if (!m_pSocket->Create())
	{
		delete m_pSocket;
		m_pSocket = NULL;
		AfxMessageBox(IDS_CREATEFAILED);
		return FALSE;
	}

	while (!m_pSocket->Connect(lpszAddress, nPort))
	{
		if (AfxMessageBox(IDS_RETRYCONNECT,MB_YESNO) == IDNO)
		{
			delete m_pSocket;
			m_pSocket = NULL;
			return FALSE;
		}
	}

	m_pFile = new CSocketFile(m_pSocket);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);

/*
if (strTemp.LoadString(IDS_CONNECT))
		SendMsg(strTemp);
*/
	// TODO: add connection initialization code here
    benKimim = siyah;


	CMsg msg(this);
	msg.m_Type = CMsg::chatMsg;
	msg.Serialize(*m_pArchiveOut);
	m_pArchiveOut->Flush();

	return TRUE;
}

void CSatrancHDoc::processAccept(void)
{
	//OnNewDocument();

	if(m_pSocket){
		delete m_pArchiveOut;
		delete m_pArchiveIn;
		delete m_pFile;
		delete m_pSocket;
		m_pSocket = NULL;
	}

	if(chat)delete chat;
	chat = NULL;

	chat = new CChatDialog(NULL, this);
	if(!chat->Create(IDD_CHATDIALOG, NULL))
		return;

	chat->ShowWindow(SW_SHOW);

	CSatrancHSoc* pSocket = new CSatrancHSoc(this);

	if (m_Listener->Accept(*pSocket))
	{
		m_pSocket = pSocket;
		m_pFile = new CSocketFile(pSocket);
		m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
		m_pArchiveOut = new CArchive(m_pFile,CArchive::store);		
	}
	else
		delete pSocket;
	delete m_Listener;
	m_Listener = NULL;
/*
	CString c("this is a test msg");
	*m_pArchiveOut << c;
*/
	//benKimim = siyah;
	CMsg c(this);
	c.Serialize(*m_pArchiveOut);
	m_pArchiveOut->Flush();
	//m_pArchiveOut;
}

void CSatrancHDoc::OnEditUndo()
{
	// Undo last move
	CMoveInfo inf;
	if(!MoveList.GetSize())return;
	inf = *MoveList[MoveList.GetSize()-1];
	delete MoveList[MoveList.GetSize()-1];
	MoveList.RemoveAt(MoveList.GetSize()-1);
	
	if(checkIfOnTable(inf.src)/* && siraKimde != benKimim*/)
	{
		akilliTahta[inf.src.x][inf.src.y] =  akilliTahta[inf.dst.x][inf.dst.y];
		akilliTahta[inf.dst.x][inf.dst.y] = inf.undoTas;

		if(checkIfOnTable(inf.roksrc)){
			akilliTahta[inf.roksrc.x][inf.roksrc.y] =  akilliTahta[inf.rokdst.x][inf.rokdst.y];
			akilliTahta[inf.rokdst.x][inf.rokdst.y] = bos;
		}

		if(siraKimde==siyah)siraKimde=beyaz; 
		               else siraKimde=siyah;

		if(m_pSocket){
			CMsg msg(this);
			msg.m_Type = CMsg::moveMsg;
			msg.Serialize(*m_pArchiveOut);
			m_pArchiveOut->Flush();
		}
   	
		inf.src = CPoint(-1,-1);
		inf.roksrc = CPoint(-1,-1);
		redraw();
	}

}

void CSatrancHDoc::redraw()
{   
	POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
      CSatrancHView* pView = (CSatrancHView* )GetNextView(pos);
	  pView->DispMoveList();
	  pView->Invalidate(FALSE);
   }   
}

BOOL CSatrancHDoc::ListenSocket(UINT nPort)
{
	if(m_pSocket){
		delete m_pArchiveOut;
		delete m_pArchiveIn;
		delete m_pFile;
		delete m_pSocket;
		m_pSocket = NULL;
	}

	if(m_Listener) delete m_Listener;
	m_Listener = NULL;

	m_Listener = new CSatrancHSoc(this);
	if (m_Listener->Create(nPort))
	{
		if (m_Listener->Listen()){
			return TRUE;
		}
	};

	delete m_Listener;
	m_Listener = NULL;
//	MessageBox(0, "TEST", "", 0);	

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return FALSE;
}
void CSatrancHDoc::closeConnection(void)
{
	//return;
	if(m_pSocket){
		delete m_pArchiveOut;
		delete m_pArchiveIn;
		delete m_pFile;
		delete m_pSocket;
		m_pSocket = NULL;
	}
	if(chat)delete chat;
	chat = NULL;
}

BOOL CSatrancHDoc::sendMessage(CString str)
{
	if(m_pSocket){
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CSatrancHView* pView = (CSatrancHView* )GetNextView(pos);
			CString fMsg;
			fMsg += myName;
			fMsg += " : ";
			fMsg += str;
			chat->displayMsg(fMsg);
			break;
		}   

		CMsg msg(this);
		msg.m_Type = CMsg::chatMsg;
		msg.msg = str;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
		return TRUE;
	}
	return FALSE;
}

void CSatrancHDoc::clearMoveList()
{
	for(int i=0;i<MoveList.GetSize();i++)
		delete MoveList[i];
	MoveList.RemoveAll();

}

CString CSatrancHDoc::MovetoStr(CMoveInfo *inf)
{
	CString s;
	s = (char)('a' + inf->src.x);
	s += (char)('1' + inf->src.y);
	s += (char)('a' + inf->dst.x);
	s += (char)('1' + inf->dst.y);
	return s;
}

