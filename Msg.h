#pragma once


// CMsg
#include "satranchdoc.h"


//class CSatrancHDoc ;

class CMsg : public CObject
{
	DECLARE_DYNAMIC(CMsg)

public:
	CMsg(CSatrancHDoc *doc);
	enum msgType{moveMsg, chatMsg};
	msgType m_Type;
	CString msg;
	CString myName;
	int siraKimde;
	int benKimim;
	int table[8][8];
//	CMoveInfo lastMove;
	CArray<CMoveInfo*, CMoveInfo*> MoveList;
	CMsg();
	virtual ~CMsg();

protected:
	//DECLARE_MESSAGE_MAP()
public:
	virtual void Serialize(CArchive& ar);
};


