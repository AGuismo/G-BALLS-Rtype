#pragma once

#include <vector>
#include "TcpServer.h"
#include "UdpServer.h"
#include "ClientAccepted.h"
#include "streamManager.h"
#include	"abs_sockets.h"

using namespace net;
EXMP template class ABS_SOCKET_API std::vector<ClientAccepted *>;
class ABS_SOCKET_API ServerTcp
{
public:
	ServerTcp(int port);
	~ServerTcp();

private:
	TcpServer				*_TcpServ;
	//UdpServer				*_UdpServ;
	std::vector<ClientAccepted *> _clients;
	streamManager 			*_stream;
};