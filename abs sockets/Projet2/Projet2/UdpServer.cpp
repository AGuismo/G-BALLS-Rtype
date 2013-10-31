#include "UdpServer.h"

using namespace net;

#if defined(WIN32)
UdpServer::UdpServer(void)
{
	WinInit::GetInstance();
}


UdpServer::~UdpServer(void)
{
}

SOCKET UdpServer::getSocket() const
{
	return _sock;
}

void UdpServer::initialize(int port, int nbClients)
{
	if((_sock = WSASocket(AF_INET , SOCK_DGRAM , IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
        throw std::exception("WSASocket failed with error : " + WSAGetLastError());
    }
    
    //Prepare the sockaddr_in structure
    _addr.sin_family = AF_INET;
	if (WSAHtonl(_sock, INADDR_ANY, &_addr.sin_addr.s_addr) != 0)
		throw std::exception("WSAHtonll failed with error : " + WSAGetLastError());
	WSAHtons(_sock, port, &_addr.sin_port);
     
    //Bind
    if( bind(_sock ,(struct sockaddr *)&_addr , sizeof(_addr)) == SOCKET_ERROR)
    {
        throw std::exception("Bind failed with error : " + WSAGetLastError());
    }
}

ClientAccepted *UdpServer::recv()
{
	DWORD						count = 0, flags = 0;
	WSABUF						wbuff;
	char						buff[512];
	std::vector<cBuffer::Byte>	tmp;
	int  size = sizeof(_addr);
	ClientAccepted *client;

	wbuff.buf = buff;
	wbuff.len = 512;
	WSARecvFrom(_sock, &wbuff, 1, &count, &flags, reinterpret_cast<sockaddr *>(&_addr), &size, NULL, NULL);
	for (unsigned int i = 0; i < wbuff.len ; i++)
		tmp.insert(tmp.end(), wbuff.buf[i]);
	_read.write(tmp, size);
	client = new ClientAccepted(_sock, _addr);
	return client;
}

void UdpServer::send()
{
	SSIZE_T				count, n;
	std::vector<cBuffer::Byte>		tmp;
	char	buf[512];
	WSABUF	wbuff;
	DWORD		size;
	int i;

	count = _write.look(tmp, 512);
	for (i = 0; i < count ; i++)
		buf[i] = tmp[i];
	wbuff.buf = buf;
	wbuff.len = i;
	n = WSASendTo(_sock, &wbuff, 1, &size, MSG_OOB, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr), NULL, NULL);
	if (n == -1)
    {
      _state = STATEERROR;
      throw std::exception("Recv Failure");
    }
	if (size == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
	_write.read(tmp, size);
}

void UdpServer::close()
{
	if (closesocket(_sock) == -1)
    {
      _state = STATEERROR;
      throw std::exception("Close Failure");
    }
  _state = DISCONNECTED;
  _sock = 0;
}

#elif defined(linux)
UdpServer::UdpServer(void)
{
}


UdpServer::~UdpServer(void)
{
}

SOCKET UdpServer::getSocket() const
{
	return _sock;
}

void UdpServer::initialize(int port, int nbClients)
{
	if((_sock = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP)) == INVALID_SOCKET)
    {
        throw std::exception("WSASocket failed with error : " + WSAGetLastError());
    }
    
    //Prepare the sockaddr_in structure
    _addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//		throw std::exception("WSAHtonll failed with error : " + WSAGetLastError());
    _addr.sin_port = htons(port);
    //Bind
    if( bind(_sock ,(struct sockaddr *)&_addr , sizeof(_addr)) == SOCKET_ERROR)
    {
        throw std::exception("Bind failed with error : " + WSAGetLastError());
    }
}

ClientAccepted *UdpServer::recv()
{
	int							count = 0, flags = 0;
	char						buff[512];
	std::vector<cBuffer::Byte>	tmp;
	int  size = sizeof(_addr);
	ClientAccepted *client;

	recvfrom(_sock, buff, &count, &flags, reinterpret_cast<sockaddr *>(&_addr), &size);
	for (unsigned int i = 0; i < wbuff.len ; i++)
		tmp.insert(tmp.end(), buff[i]);
	_read.write(tmp, size);
	client = new ClientAccepted(_sock, _addr);
	return client;
}

void UdpServer::send()
{
	SSIZE_T				count, n;
	std::vector<cBuffer::Byte>		tmp;
	char	buf[512];
	int i;

	count = _write.look(tmp, 512);
	for (i = 0; i < count ; i++)
		buf[i] = tmp[i];
	n = sendto(_sock, buf, &i, MSG_OOB, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
	if (n == -1)
    {
      _state = STATEERROR;
      throw std::exception("Recv Failure");
    }
	if (size == 0)
    {
      _state = DISCONNECTED;
      return ;
    }
	_write.read(tmp, size);
}

void UdpServer::close()
{
	if (closesocket(_sock) == -1)
    {
      _state = STATEERROR;
      throw std::exception("Close Failure");
    }
  _state = DISCONNECTED;
  _sock = 0;
}
#endif

void UdpServer::readFromBuffer(std::string &str)
{
	std::vector<cBuffer::Byte>		tmp;
	char	buf[512];
	int count;

	count = _read.read(tmp, 512);
	for (int i = 0; i < count ; i++)
		buf[i] = tmp[i];
	str = buf;
	if (_type != WRITE && _type != BOTH)
		_type = READ;
	else
		_type = BOTH;
}

void UdpServer::writeIntoBuffer(const std::string &str)
{
	std::vector<cBuffer::Byte>		tmp;

	for (unsigned int i = 0; i < str.length() ; i++)
		tmp.insert(tmp.end(), str.c_str()[i]);
	_read.write(tmp, str.length());
	if (_type != READ && _type != BOTH)
		_type = WRITE;
	else
		_type = BOTH;
}

cBuffer::size_type UdpServer::lookRead(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count)
{
	return _read.look(buf, count);
}

cBuffer::size_type UdpServer::lookWrite(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count)
{
	return _write.look(buf, count);
}