#include	<iostream>
#include	"Client.hh"
#include	"ClientAccepted.h"
#include	"cBuffer.h"

Client::Client():
  _TcpLayer(0)
{

}

Client::Client(net::ClientAccepted *clientTcp):
  _TcpLayer(clientTcp)
{

}

Client::~Client()
{
  delete _TcpLayer;
}

void	Client::TcpLayer(net::ClientAccepted *link)
{
  _TcpLayer = link;
}

net::ClientAccepted	*Client::TcpLayer() const
{
  return (_TcpLayer);
}

void	Client::update()
{
  std::vector<net::cBuffer::Byte> buf;

#if defined(DEBUG)
  if (_TcpLayer == 0)
    throw std::Exception();
#endif
  _TcpLayer->recv();
  std::cout << "The client have data to read" << std::endl;
  std::cout << _TcpLayer->readFromBuffer(buf, 512) << std::endl;
}

bool		Client::isTCP() const
{
  return (_TcpLayer != 0);
}

bool		Client::isTCPDisconnected() const
{
  return (_TcpLayer != 0 && _TcpLayer->isClosed() == net::DISCONNECTED);
}

void		Client::closeTCP()
{
  delete _TcpLayer;
  _TcpLayer = 0;
}
