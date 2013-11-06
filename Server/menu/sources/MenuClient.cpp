#include	<iostream>
#include	"ClientAccepted.h"
#include	"MenuClient.hh"
#include	"RequestQueue.hh"
#include	"cBuffer.h"
#include	"Protocol.hpp"

namespace	menu
{
  Client::Client(RequestQueue &input, RequestQueue &output,
		 net::ClientAccepted *clientTcp):
    _used(false), _input(input), _output(output), _TcpLayer(clientTcp)
  {
    _auth._authenticated = false;
  }

  Client::~Client()
  {
    delete _TcpLayer;
  }

  void	Client::update()
  {
  while (inputRequest());
#if defined(DEBUG)
    if (_TcpLayer == 0)
      throw "No TCP socket";
    //  std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    if (_TcpLayer->read())
      recvSock();
    while (outputRequest());
    if (_TcpLayer->write())
      sendSock();
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

  void	Client::TcpLayer(net::ClientAccepted *link)
  {
    _TcpLayer = link;
  }

  net::ClientAccepted	*Client::TcpLayer() const
  {
    return (_TcpLayer);
  }

  void		Client::recvSock()
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
  }

  void				Client::sendSock()
  {
#if defined(DEBUG)
    std::cerr << "The client have data to send" << std::endl;
#endif
#if defined(DEBUG)
    std::vector<net::cBuffer::Byte> buf;

    std::cout << _TcpLayer->lookWrite(buf, 512) << std::endl;
    for (std::vector<net::cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); ++it)
      std::cerr << *it;
    std::cerr << std::endl;
#endif
    if (_TcpLayer->send() <= 0)
      return ;
  }

  bool					Client::inputRequest()
  {
    std::vector<net::cBuffer::Byte>	buf;
    ARequest				*req;
    int					extracted;

    if (_TcpLayer->lookRead(buf, 512) == 0)
      return (false);
    try
      {
	req = Protocol::consume(buf, extracted);
      }
    catch (Protocol::ConstructRequest &e)
      {
#if defined(DEBUG)
	std::cerr << "Failed to create request: " << e.what() << std::endl;
#endif
	return (false);
      }
    _TcpLayer->readFromBuffer(buf, extracted);
    _input.requestPush(req);
    return (true);
  }

  bool					Client::outputRequest()
  {
    std::vector<net::cBuffer::Byte>	buf;
    ARequest				*req;

    if (_output.empty())
      return (false);
    req = _output.requestPop();
    try
      {
	buf = Protocol::product(*req);
	delete req;
      }
    catch (Protocol::ConstructRequest &e)
      {
#if defined(DEBUG)
	std::cerr << "Failed to serialize request: " << e.what() << std::endl;
#endif
	return (false);
      }
    return (_TcpLayer->writeIntoBuffer(buf, buf.size()) > 0);
  }

  void					Client::username(const std::string &username)
  {
    _auth._username = username;
  }

  const std::string			&Client::username(void) const
  {
    return (_auth._username);
  }

  void					Client::password(const requestCode::PasswordType &password)
  {
    _auth._password = password;
  }

  const requestCode::PasswordType	&Client::password(void) const
  {
    return (_auth._password);
  }

  void					Client::sessionID(const requestCode::SessionID &sessionID)
  {
    _auth._sessionID = sessionID;
  }

  const requestCode::SessionID		&Client::sessionID(void) const
  {
    return (_auth._sessionID);
  }

  bool					Client::authenticated(void) const
  {
    return (_auth._authenticated);
  }

  void					Client::authenticated(bool authenticated)
  {
    _auth._authenticated = authenticated;
  }

}
