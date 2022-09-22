#pragma once
#include <afxsock.h>
class CClientSocket :
	public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	void SetListenSocket(CAsyncSocket * pSocket);

	CAsyncSocket* m_pListenSocket;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

