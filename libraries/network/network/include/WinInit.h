#pragma once

class  WinInit
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