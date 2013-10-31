#include "server.h"

Server::Server(int port)
{
	_TcpServ = new TcpServer();
	_TcpServ->initialize(port);
	_UdpServ = new UdpServer();
	_UdpServ->initialize(port);
	_stream = new streamManager();
}

Server::~Server()
{
	delete _TcpServ;
	delete _UdpServ;
	delete _stream;
	/*call deconstructors for each clients connected*/
}