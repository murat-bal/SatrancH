// SatrancHSoc.cpp : implementation file
//

#include "stdafx.h"
#include "SatrancH.h"
#include "SatrancHSoc.h"

#include "SatrancHDoc.h"


// CSatrancHSoc

CSatrancHSoc::CSatrancHSoc()
{
}

CSatrancHSoc::CSatrancHSoc(CSatrancHDoc *doc)
{
	pDoc = doc;
}

CSatrancHSoc::~CSatrancHSoc()
{
}


// CSatrancHSoc member functions

//int CSatrancHSoc::Receive(void* lpBuf, int nBufLen, int nFlags)
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//	return CSocket::Receive(lpBuf, nBufLen, nFlags);
//}

void CSatrancHSoc::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnReceive(nErrorCode);
	if(pDoc) pDoc->receiveMsg();
}

void CSatrancHSoc::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnAccept(nErrorCode);
	if(pDoc) pDoc->processAccept();
}

void CSatrancHSoc::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnClose(nErrorCode);
	if(pDoc) 
		pDoc->closeConnection(); 
}
