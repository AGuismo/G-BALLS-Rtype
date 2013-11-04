#include	<iostream>
#include	"ARequest.hh"
#include	"Client.hh"
#include	"ClientAccepted.h"
#include	"cBuffer.h"
#include	"Protocol.hpp"

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

void	Client::recvSock()
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

bool					Client::request()
{
  std::vector<net::cBuffer::Byte>	buf;
  ARequest				*req;

  std::cout << _TcpLayer->lookRead(buf, 512) << std::endl;
  try
    {
      req = Protocol::consume(buf);
      (void)req;
    }
  catch (Protocol::ConstructRequest &e)
    {
      std::cerr << "Failed to create request: " << e.what() << std::endl;
      return (false);
    }
  return (true);
}

void	Client::update()
{
#if defined(DEBUG)
  if (_TcpLayer == 0)
    throw "No TCP socket";
  std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
  if (_TcpLayer->read())
    recvSock();
  while (request());
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
