#if defined(DEBUG)
#include	<stdio.h>
#endif
#include	<iostream>
#include	<ctype.h>
#include	"ClientAccepted.h"
#include	"MenuClient.hh"
#include	"Client.hh"
#include	"cBuffer.h"
#include	"Protocol.hpp"
#include	"NetException.h"
#include	"Application.hh"

using namespace loglib;

namespace	menu
{
  Client::Client(net::ClientAccepted *clientTcp):
    _TcpLayer(clientTcp), _id(::Client::generateUniqueID()), _game(0)
  {
    _auth._authenticated = false;
  }

  Client::~Client()
  {
#if defined(DEBUG)
    Application::log << "Client " << this << " : Deleted" << std::endl;
#endif
    delete _TcpLayer;
  }

  void	Client::update()
  {
#if defined(DEBUG)
    if (_TcpLayer == 0)
      throw "No TCP socket";
#endif
    if (_TcpLayer->read())
    {
      recvSock();
      while (inputRequest());
    }
    if (_TcpLayer->write())
    {
      sendSock();
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
    Application::log << "menu::Client::recvSock(): " << "The client have data to read" << std::endl;
#endif
    try
    {
      if (_TcpLayer->recv() <= 0)
	return ;
    }
    catch (const net::Exception &e)
    {
      Application::log << "Error : " << e.what() << " in menu::client" << std::endl;
      return ;
    }
#if defined(DEBUG)
    std::vector<net::cBuffer::Byte> buf;
    _TcpLayer->lookRead(buf, 512);
    Application::log << "menu::Client::recvSock(): " << buf.size()
		     << Log::hexDump(buf) << std::endl;
#endif
  }

  void				Client::sendSock()
  {
#if defined(DEBUG)
    std::vector<net::cBuffer::Byte> buf;
    _TcpLayer->lookWrite(buf, 512);
    Application::log << "The client have data to send" << "menu::Client::sendSock(): "
		     << buf.size() << Log::hexDump(buf) << std::endl;
    // for (std::vector<net::cBuffer::Byte>::iterator it = buf.begin(); it != buf.end(); ++it)
    //   {
    // 	if (!isprint(*it))
    // 	  printf("\\%.2X", *it);
    // 	else
    // 	  printf("%c", *it);
    //   }
#endif
    try
    {
      if (_TcpLayer->send() < 0)
	return ;
    }
    catch (const net::Exception &e)
    {
      Application::log << "Error : " << e.what() << " in menu::client" << std::endl;
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
      Application::log << "Client::inputRequest()" << "Failed to create request: " << e.what() << std::endl;
#endif
      return (false);
    }
#if defined(DEBUG)
    Application::log << "Client::inputRequest(): Request successfully unserialized. "
		     << "Extracted " << extracted << " Bytes" << std::endl;
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
      Application::log << "Client::outputRequest(): " << "Failed to serialize request: "
		       << e.what() << std::endl;
#endif
      return (false);
    }
    _TcpLayer->writeIntoBuffer(buf, buf.size());
#if defined(DEBUG)
    Application::log << "Client::outputRequest(): Request successfully serialized" << std::endl;
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

  bool					Client::inLobby() const
  {
    return (_game != 0);
  }

  Game					*Client::currentGame() const
  {
    return (_game);
  }

  void					Client::currentGame(Game *game)
  {
    _game = game;
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
    _id = sessionID;
  }

  const requestCode::SessionID		&Client::sessionID(void) const
  {
    return (_id);
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
