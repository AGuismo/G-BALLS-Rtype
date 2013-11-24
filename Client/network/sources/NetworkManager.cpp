#include	<iostream>
#include	"Protocol.hpp"
#include	"NetworkManager.hh"

sf::Packet	&operator>>(sf::Packet &packet, ARequest *&);
sf::Packet	&operator<<(sf::Packet &packet, const ARequest *req);

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

  void	Manager::setTcp(const sf::IpAddress &ip, unsigned short port)
  {
    if (isConnected())
      return ;
    Thread::MutexGuard	guard(_sock);

    if (_tcp.mSock.connect(ip, port) == sf::Socket::Error)
      _connected = false;
    else
      _connected = true;
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

  void		Manager::sendRequest(const ARequest *req)
  {
    sf::Packet		packet;

    packet << req;
#if defined(DEBUG)
    std::cout << "network::Manager::sendRequest(const ARequest *)"
	      << "Packet Size: " << packet.getDataSize() << std::endl;
#endif
    _state.lock();
    if (_curState == TCP)
      {
	_state.unlock();
	if (_tcp.mSock.send(packet.getData(), packet.getDataSize()) == sf::Socket::Error)
	  switchTo(NONE);
	return ;
      }
    else if (_curState == UDP)
      {
	_state.unlock();
	if (_udp.gSock.send(packet.getData(), packet.getDataSize(),
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
    sf::Packet			packet;
    std::vector<Protocol::Byte>	data;

    _sock.lock();
    if (_udp.gSock.receive(packet, _udp.gIp, _udp.gPort) == sf::Socket::Error)
      {
	switchTo(NONE);
	_sock.unlock();
	return ;
      }
    _sock.unlock();

    packet >> req;
#if defined(DEBUG)
    std::cout << "network::Manager::udpMode(const ARequest *)"
	      << "Packet Size: " << packet.getDataSize() << std::endl;
#endif

    if (req == 0)
      return ;
    _reqlist.lock();
    _requests.push_back(req);
    _reqlist.unlock();
  }

  void				Manager::tcpMode()
  {
    ARequest			*req = 0;
    Protocol::Byte		bytes[1024];
    std::size_t			received;
    sf::Packet			packet;
    sf::Socket::Status		status;


    _sock.lock();
    status = _tcp.mSock.receive(bytes, 1024, received);
    if (status == sf::Socket::Error)
      {
	switchTo(NONE);
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

    packet.append(_tcp.notRead.getData(), _tcp.notRead.getDataSize());
    packet.append(bytes, received);
    packet >> req;
#if defined(DEBUG)
    std::cout << "network::Manager::tcpMode(const ARequest *)"
	      << "Packet Size: " << packet.getDataSize() << std::endl;
#endif
    _tcp.notRead.clear();
    _tcp.notRead.append(packet.getData(), packet.getDataSize());

    if (req == 0)
      return ;
    _reqlist.lock();
    _requests.push_back(req);
    _reqlist.unlock();
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

sf::Packet			&operator>>(sf::Packet &packet, ARequest *&req)
{
  std::vector<Protocol::Byte>	b;
  int				extracted;

  while (!packet.endOfPacket())
    {
      Ruint8	c;

      packet >> c;
      b.push_back(c);
    }
  try
    {
      req = Protocol::consume(b, extracted);
    }
  catch (Protocol::ConstructRequest &e)
    {
      std::cerr << "Manager::operator>>(sf::Packet &, const ARequest *): " << e.what() << std::endl;
      for (std::vector<Protocol::Byte>::iterator it = b.begin(); it != b.end(); ++it)
	packet << *it;
      return (packet);
    }
  return (packet);
}

sf::Packet			&operator<<(sf::Packet &packet, const ARequest *req)
{
  std::string			data;
  std::vector<Protocol::Byte>	b;

  try
    {
      b = Protocol::product(*req);
    }
  catch (Protocol::ConstructRequest &e)
    {
      std::cerr << "Manager::operator<<(sf::Packet &, const ARequest *): " << e.what() << std::endl;
      return (packet);
    }

  for (std::vector<Protocol::Byte>::iterator it = b.begin(); it != b.end(); ++it)
    packet << *it;
  return (packet);
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
