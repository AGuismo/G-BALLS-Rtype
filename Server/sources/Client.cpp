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
#if defined(DEBUG)
  if (_TcpLayer == 0)
    throw std::Exception();
  std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
  if (_TcpLayer->read())
    {
#if defined(DEBUG)
      std::cerr << "The client have data to read" << std::endl;
#endif
      if (_TcpLayer->recv() <= 0)
	return ;
#if defined(DEBUG)
      std::vector<net::cBuffer::Byte> buf;

      std::cout << _TcpLayer->lookRead(buf, 512) << std::endl;
      for (std::vector<net::cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); ++it)
	std::cerr << *it;
      std::cerr << std::endl;
#endif
      // std::cout << buf.size() << std::endl;
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
