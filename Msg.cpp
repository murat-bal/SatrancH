// Msg.cpp : implementation file
//

#include "stdafx.h"
#include "SatrancH.h"
#include "SatrancHDoc.h"
#include "Msg.h"


// CMsg

IMPLEMENT_DYNAMIC(CMsg, CObject)

CMsg::CMsg()
{
	m_Type = chatMsg;
}

CMsg::CMsg(CSatrancHDoc *doc)
{
	for(int i = 0;i<8;i++)
		for(int j=0;j<8;j++)
			table[i][j]=doc->akilliTahta[i][j];
	m_Type = moveMsg;
	siraKimde = doc->siraKimde;
	benKimim = doc->benKimim;
	myName = doc->myName;
	msg = "";
	/*
	if(doc->MoveList.GetSize()>0){
		lastMove =  * (doc->MoveList[doc->MoveList.GetSize() -1 ]);			
	}else{
		lastMove.src = CPoint(-1,-1);
		lastMove.dst = CPoint(-1,-1);
		lastMove.undoTas = 0;
		lastMove.roksrc = CPoint(-1,-1);
		lastMove.rokdst = CPoint(-1,-1);
	}
	*/
	MoveList.RemoveAll();
	for(int i=0;i<doc->MoveList.GetSize();i++){
		MoveList.Add(doc->MoveList[i]);
	}

};



CMsg::~CMsg()
{

}


//BEGIN_MESSAGE_MAP(CMsg, CWnd)
//END_MESSAGE_MAP()



// CMsg message handlers


void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << (int) m_Type;
		if(m_Type == moveMsg){
			ar << siraKimde;
			ar << benKimim;
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)ar << table[i][j];

			ar << (int)MoveList.GetSize();
			for(int i=0;i<MoveList.GetSize();i++){
				ar.Write(MoveList[i], sizeof(CMoveInfo));
			}
		}
		ar << myName;
		ar << msg;
	}
	else
	{	// loading code
		int t;
		ar >> t;
		m_Type = (CMsg::msgType)t;
		if(m_Type == moveMsg){
			ar >> siraKimde;
			ar >> benKimim;
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)ar >> table[i][j];

			int nMove;
			ar >> nMove;
			MoveList.RemoveAll();
			for(int i=0;i<nMove;i++){
				CMoveInfo *inf = new CMoveInfo;
				ar.Read(inf, sizeof(CMoveInfo));
				MoveList.Add(inf);
			}
		}
		ar >> myName;
		ar >> msg;
	}
}
