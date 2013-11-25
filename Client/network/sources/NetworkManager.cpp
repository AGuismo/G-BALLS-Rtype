#include	<iostream>
#include	"Protocol.hpp"
#include	"NetworkManager.hh"

bool	consume(std::vector<Protocol::Byte> &b, ARequest *&req);
bool	product(std::vector<Protocol::Byte> &b, const ARequest *req);

namespace	network
{
  Manager::Manager() :
    _th(Func::Bind(&Manager::routine, this)), _curState(NONE), _connected(false)
  {
  }

  Manager::~Manager()
  {

  }

  void	Manager::initialize()
  {

  }

  void	Manager::run()
  {
    _th.run();
  }

  void	Manager::stop()
  {
    _th.cancel();
  }

  void	Manager::join()
  {
    _th.join();
  }

  bool	Manager::setTcp(const sf::IpAddress &ip, unsigned short port)
  {
    Thread::MutexGuard	guard(_sock);
    sf::Socket::Status	st;

    std::cout << "network::Manager::setTcp()" << std::endl;
    if (isConnected())
      return (false);
    st = _tcp.mSock.connect(ip, port);
    if (st == sf::Socket::Done)
      _connected = true;
    else
      _connected = false;
    return (_connected);
  }

  void	Manager::setUdp(const sf::IpAddress &ip, unsigned short port)
  {
    Thread::MutexGuard	guard(_sock);

    _udp.gIp = ip;
    _udp.gPort = port;
    _connected = true;
  }

  bool	Manager::isConnected()
  {
    return (_connected);
  }

  void	Manager::closeTcp(void)
  {
    Thread::MutexGuard	guard(_sock);

    _tcp.mSock.disconnect();
  }

  void	Manager::switchTo(Manager::State st)
  {
    Thread::MutexGuard	guard(_state);

    if (_curState == NONE)
      _wake.signal();
    switch (st)
      {
      case TCP:
	if (!_connected)
	  return ;
	break;
      case UDP:
	if (!_connected)
	  return ;
	break;
      case NONE:
	break;
      default:
	break;
      }
    _curState = st;
  }

  void				Manager::sendRequest(const ARequest *req)
  {
    std::vector<Protocol::Byte>	packet;
    Protocol::Byte		bytes[1024];

    if (!product(packet, req))
      return ;
#if defined(DEBUG)
    std::cout << "network::Manager::sendRequest(const ARequest *)"
	      << "Packet Size: " << packet.size() << std::endl;
#endif
    for (std::vector<Protocol::Byte>::size_type it = 0; it != packet.size(); ++it)
      bytes[it] = packet[it];
    _state.lock();
    if (_curState == TCP)
      {
	_state.unlock();
	if (_tcp.mSock.send(bytes, packet.size()) == sf::Socket::Error)
	  switchTo(NONE);
	return ;
      }
    else if (_curState == UDP)
      {
	_state.unlock();
	if (_udp.gSock.send(bytes, packet.size(),
			    _udp.gIp, _udp.gPort) == sf::Socket::Error)
	  switchTo(NONE);
	return ;
      }
    _state.unlock();
  }

  ARequest	*Manager::recvRequest()
  {
    Thread::MutexGuard	guard(_reqlist);
    ARequest		*req;

    if (_requests.empty())
      return (0);
    req = _requests.front();
    _requests.pop_front();
    return (req);
  }

  void				Manager::udpMode()
  {
    ARequest			*req = 0;
    Protocol::Byte		bytes[1024];
    std::size_t			extracted;
    std::vector<Protocol::Byte>	packet;
    sf::SocketSelector		select;
    sf::Socket::Status		st;

    _sock.lock();
    select.add(_udp.gSock);
    select.wait(sf::milliseconds(100));
    if (select.isReady(_udp.gSock))
      {
	st = _udp.gSock.receive(bytes, 1024, extracted, _udp.gIp, _udp.gPort);
	if (st == sf::Socket::Error)
	  {
	    switchTo(NONE);
	    _connected = false;
	    _sock.unlock();
	    return ;
	  }
	else if (st == sf::Socket::Disconnected)
	  {
	    _connected = false;
	    _sock.unlock();
	    return ;
	  }
	_sock.unlock();
      }
    else
      {
	_sock.unlock();
	return ;
      }

    for (std::size_t it = 0; it < extracted; it++)
      packet.insert(packet.end(), bytes[it]);

    while (consume(packet, req))
      {
#if defined(DEBUG)
	std::cout << "network::Manager::tcpMode(const ARequest *) -- "
		  << "Packet Size: " << packet.size() << std::endl;
#endif
	_reqlist.lock();
	_requests.push_back(req);
	_reqlist.unlock();
      }
  }

  void				Manager::tcpMode()
  {
    ARequest			*req = 0;
    Protocol::Byte		bytes[1024];
    std::size_t			received;
    std::vector<Protocol::Byte>	packet;
    sf::Socket::Status		status;
    sf::SocketSelector		select;

    _sock.lock();
    select.add(_tcp.mSock);
    select.wait(sf::milliseconds(100));
    if (select.isReady(_tcp.mSock))
      status = _tcp.mSock.receive(bytes, 1024, received);
    else
      {
	_sock.unlock();
	return ;
      }
    if (status == sf::Socket::Error)
      {
	switchTo(NONE);
	_connected = false;
	_sock.unlock();
	return ;
      }
    else if (status == sf::Socket::Disconnected)
      {
	_tcp.mSock.disconnect();
	_connected = false;
	_sock.unlock();
	return ;
      }
    _sock.unlock();

    packet.insert(packet.begin(), _tcp.notRead.begin(), _tcp.notRead.end());
    for (std::size_t it = 0; it < received; it++)
      packet.insert(packet.end(), bytes[it]);

    while (consume(packet, req))
      {
#if defined(DEBUG)
	std::cout << "network::Manager::tcpMode(const ARequest *) -- "
		  << "Packet Size: " << packet.size() << std::endl;
#endif
	_reqlist.lock();
	_requests.push_back(req);
	_reqlist.unlock();
      }
    _tcp.notRead = packet;
  }

  int		Manager::routine()
  {
    while (true)
      {
	_state.lock();
	switch (_curState)
	  {
	  case SHUTDOWN:
	    _state.unlock();
	    return (0);
	    break;
	  case TCP:
	    _state.unlock();
	    tcpMode();
	    break;
	  case UDP:
	    _state.unlock();
	    udpMode();
	    break;
	  case NONE:
	    _wake.wait(_state);
	    _state.unlock();
	    break;
	  }
      }
    return (0);
  }
}

bool		consume(std::vector<Protocol::Byte> &b, ARequest *&req)
{
  int		extracted;

  try
    {
      req = Protocol::consume(b, extracted);
    }
  catch (Protocol::ConstructRequest &e)
    {
      std::cerr << "Manager::operator>>(sf::Packet &, const ARequest *): " << e.what() << std::endl;
      return (false);
    }
  b.erase(b.begin(), b.begin() + extracted);
  return (true);
}

bool		product(std::vector<Protocol::Byte> &b, const ARequest *req)
{
  std::string			data;

  try
    {
      b = Protocol::product(*req);
    }
  catch (Protocol::ConstructRequest &e)
    {
      std::cerr << "Manager::operator<<(sf::Packet &, const ARequest *): " << e.what() << std::endl;
      b.clear();
      delete req;
      return (false);
    }
  delete req;
  return (true);
}

network::Exception::Exception(const std::string &msg) throw():
  _what(msg)
{

}

network::Exception::~Exception() throw()
{

}

network::Exception::Exception(const network::Exception &src) throw() :
  _what(src._what)
{

}

network::Exception	&network::Exception::operator=(const network::Exception &src) throw()
{
  if (&src != this)
    {
      this->_what = src._what;
    }
  return (*this);
}

const char		*network::Exception::what() const throw()
{
  return (this->_what.c_str());
}
