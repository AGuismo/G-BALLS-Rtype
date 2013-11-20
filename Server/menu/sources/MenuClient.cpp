#if defined(DEBUG)
#include	<stdio.h>
#endif
#include	<iostream>
#include	"ClientAccepted.h"
#include	"MenuClient.hh"
#include	"cBuffer.h"
#include	"Protocol.hpp"
#include	"NetException.h"

namespace	menu
{
  Client::Client(requestCode::SessionID &id, net::ClientAccepted *clientTcp):
    _used(false), _TcpLayer(clientTcp), _id(id)
  {
    _auth._authenticated = false;
  }

  Client::~Client()
  {
    delete _TcpLayer;
  }

  void	Client::update()
  {
#if defined(DEBUG)
    if (_TcpLayer == 0)
      throw "No TCP socket";
    //  std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    if (_TcpLayer->read())
      {
	try
	  {
	    recvSock();
	  }
	catch (net::Exception &e)
	  {
	    std::cerr << "Error : " << e.what() << " in menu::client" << std::endl;
	  }
	while (inputRequest());
      }
    if (_TcpLayer->write())
      {
	try
	  {
	    sendSock();
	  }
	catch (net::Exception &e)
	  {
	    std::cerr << "Error : " << e.what() << " in menu::client" << std::endl;
	  }
      }
  }

  void		Client::finalize()
  {
    while (outputRequest());
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
    std::cout << "menu::Client::recvSock(): " << "The client have data to read" << std::endl;
#endif
    try
      {
	if (_TcpLayer->recv() <= 0)
	  return ;
      }
    catch (const net::Exception &e)
      {
	std::cerr << "Error : " << e.what() << " in menu::client" << std::endl;
	return ;
      }
#if defined(DEBUG)
    std::vector<net::cBuffer::Byte> buf;

    std::cout << "menu::Client::recvSock(): " << _TcpLayer->lookRead(buf, 512) << std::endl;
    std::cout << "menu::Client::recvSock(): ";
    for (std::vector<net::cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); ++it)
      printf("%.2X", *it);
    printf("\n");
#endif
  }

  void				Client::sendSock()
  {
#if defined(DEBUG)
    std::cout << "menu::Client::sendSock(): " << "The client have data to send" << std::endl;
    std::vector<net::cBuffer::Byte> buf;

    std::cout << "menu::Client::sendSock(): " << _TcpLayer->lookWrite(buf, 512) << std::endl;
    std::cout << "menu::Client::sendSock(): ";
    for (std::vector<net::cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); ++it)
      printf("%.2X", *it);
    printf("\n");
#endif
    try
      {
	if (_TcpLayer->send() <= 0)
	  return ;
      }
    catch (const net::Exception &e)
      {
	std::cerr << "Error : " << e.what() << " in menu::client" << std::endl;
	return ;
      }
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
	std::cerr << "Client::inputRequest()" << "Failed to create request: " << e.what() << std::endl;
#endif
	return (false);
      }
#if defined(DEBUG)
    std::cerr << "Client::inputRequest(): Request successfully unserialized" << std::endl;
    std::cerr << "Extracted " << extracted << std::endl;
#endif
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
	std::cerr << "Client::outputRequest(): " << "Failed to serialize request: "
		  << e.what() << std::endl;
#endif
	return (false);
      }
    _TcpLayer->writeIntoBuffer(buf, buf.size());
#if defined(DEBUG)
    std::cout << "Client::outputRequest(): Request successfully serialized" << std::endl;
#endif
    return (true);
  }

  ARequest	*Client::requestPop()
  {
    return (_input.requestPop());
  }

  void		Client::requestPush(ARequest *req)
  {
    _output.requestPush(req);
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

  void					Client::permissions(database::Rights perm)
  {
    _auth._permissions = perm;
  }

  database::Rights			Client::permissions(void) const
  {
    return (_auth._permissions);
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
