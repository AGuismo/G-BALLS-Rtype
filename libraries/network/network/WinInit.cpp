#if defined(WIN32)
#include	<exception>
#include "WinInit.h"
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")
WinInit* WinInit::m_instance = 0;
int		rc = 0;

WinInit::WinInit(void)
{
	int rc;
	WSADATA wsaData;

	if ((rc = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        /* Could not find a usable Winsock DLL */
		throw std::exception("WSAStartup failed with error: "); //  + rc
    }
}

WinInit::~WinInit(void)
{
	WSACleanup();
	m_instance = NULL;
}

WinInit* WinInit::GetInstance()
{
    if (m_instance == 0)
	{
        m_instance = new WinInit;
		rc = 1;
	}
    return m_instance;
}

void WinInit::DestroyInstance()
{
    delete WinInit::GetInstance();
}

#endif