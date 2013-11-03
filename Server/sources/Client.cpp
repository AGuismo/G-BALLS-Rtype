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
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  if (_TcpLayer->read())
    {
      std::cout << "The client have data to read" << std::endl;
      std::cout << _TcpLayer->recv() << std::endl;
      std::cout << _TcpLayer->readFromBuffer(buf, 512) << std::endl;
    }
  // _TcpLayer->recv();
  // _TcpLayer->readFromBuffer(buf, 512);
}

bool		Client::isTCP() const
{
  return (_TcpLayer != 0);
}

bool		Client::isTCPDisconnected() const
{
  return (_TcpLayer != 0 && _TcpLayer->isDisconnected());
}

void		Client::closeTCP()
{
  delete _TcpLayer;
  _TcpLayer = 0;
}
