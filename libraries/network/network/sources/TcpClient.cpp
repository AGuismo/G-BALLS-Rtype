#include "TcpClient.h"
#include "WinInit.h"
#include "NetException.h"

using namespace net;
#if defined(WIN32)
TcpClient::TcpClient()
{
  WinInit::GetInstance();
}


TcpClient::~TcpClient(void)
{
}

void TcpClient::init(std::string adress, std::string port)
{
  struct addrinfo *result;
  struct addrinfo hints;
  int size;

  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(adress.c_str(), port.c_str(), &hints, &result) != 0)
    {
      throw net::Exception("getaddrinfo failed" + WSAGetLastError());
    }
  _sock = WSASocket(result->ai_family, result->ai_socktype,
		    result->ai_protocol, NULL, 0, 0); // WSA_FLAG_OVERLAPPED
  size = result->ai_addrlen;
  if (WSAConnect(_sock, result->ai_addr, size, NULL, NULL, NULL, NULL) != 0)
    {
      throw net::Exception("WSAConnect failed with error : " + WSAGetLastError());
    }
  _addr = *(reinterpret_cast<sockaddr_in *>(result->ai_addr));
  freeaddrinfo(result);
}
#elif defined(linux)
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <errno.h>
# include <cstring>

TcpClient::TcpClient() : ClientAccepted()
{
}


TcpClient::~TcpClient(void)
{
}

void TcpClient::init(std::string adress, std::string port)
{
  struct addrinfo *result;
  struct addrinfo hints;

  bzero(&hints, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(adress.c_str(), port.c_str(), &hints, &result) != 0)
    {
      throw net::Exception("getaddrinfo failed:" + std::string(strerror(errno)));
    }
  _sock = socket(result->ai_family, result->ai_socktype,
		 result->ai_protocol);
  if (connect(_sock, result->ai_addr, result->ai_addrlen) != 0)
    {
      throw net::Exception("connect failed with error: " + std::string(strerror(errno)));
    }
  _addr = *(reinterpret_cast<sockaddr_in *>(result->ai_addr));
  freeaddrinfo(result);
}
#endif
