#pragma once
#include	"abs_sockets.h"

class  ABS_SOCKET_API WinInit
{
public:
	static WinInit* GetInstance();
	static void DestroyInstance();

protected:
	WinInit();
	~WinInit();
	static WinInit *m_instance;

private:
	WinInit(const WinInit & wi);
	WinInit & operator=(const WinInit &wi);
};