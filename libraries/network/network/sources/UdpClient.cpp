#include "UdpClient.h"

using namespace net;

#if defined(WIN32)
#include "WinInit.h"
UdpClient::UdpClient(void) : ClientAccepted()
{
  WinInit::GetInstance();
}


UdpClient::~UdpClient(void)
{
}

void UdpClient::init(std::string adress, std::string port)
{
  struct sockaddr_in	addr;
  u_short				num;

  std::stringstream ss(port.c_str());
  ss >> num;
  if ( (_sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, NULL, NULL))
       == SOCKET_ERROR)
    {
      throw std::exception("WSASocket failed with error : " + WSAGetLastError());
    }
  ZeroMemory(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  WSAHtons(_sock, num, &addr.sin_port);
  addr.sin_addr.S_un.S_addr = inet_addr(adress.c_str());
}
#elif defined(linux)
UdpClient::UdpClient(void) : ClientAccepted()
{
}


UdpClient::~UdpClient(void)
{
}

void UdpClient::init(std::string adress, std::string port)
{
  struct sockaddr_in	addr;
  u_short				num;

  std::stringstream ss(port.c_str());
  ss >> num;
  if ((_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      throw std::exception(); //"socket failed with error : " + WSAGetLastError()
    }
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(num);
  addr.sin_addr.s_addr = inet_addr(adress.c_str());
}
#endif
