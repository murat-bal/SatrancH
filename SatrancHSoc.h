#pragma once



// CSatrancHSoc command target
#include "afxsock.h"

class CSatrancHDoc;

class CSatrancHSoc : public CSocket
{
public:
	CSatrancHDoc *pDoc;
	CSatrancHSoc(CSatrancHDoc* doc);
	CSatrancHSoc();
	virtual ~CSatrancHSoc();
//	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


