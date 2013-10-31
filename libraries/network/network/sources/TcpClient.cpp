#include "TcpClient.h"
#include "WinInit.h"

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
  hints.ai_family = AF_UNSPEC;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(adress.c_str(), port.c_str(), &hints, &result) != 0)
    {
      throw std::exception("getaddrinfo failed");
    }
  _sock = WSASocket(result->ai_family, result->ai_socktype,
		    result->ai_protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
  size = result->ai_addrlen;
  if (WSAConnect(_sock, result->ai_addr, size, NULL, NULL, NULL, NULL) != 0)
    {
      throw std::exception("WSAConnect failed with error : "+ WSAGetLastError());
    }
  _addr = *(reinterpret_cast<sockaddr_in *>(result->ai_addr));
  freeaddrinfo(result);
}
#elif defined(linux)
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

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
      throw std::exception(); // "getaddrinfo failed"
    }
  _sock = socket(result->ai_family, result->ai_socktype,
		 result->ai_protocol);
  if (connect(_sock, result->ai_addr, result->ai_addrlen) != 0)
    {
      throw std::exception(); // "connect failed with error : "+ strerror(errno)
    }
  _addr = *(reinterpret_cast<sockaddr_in *>(result->ai_addr));
  freeaddrinfo(result);
}
#endif
