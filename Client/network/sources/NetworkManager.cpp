#include	"NetworkManager.hh"

namespace	network
{
  Manager::Manager() :
    _th(Func::Bind(&Manager::routine, this)), _curState(NONE)
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

  void	Manager::switchTo(Manager::State st)
  {
    Thread::MutexGuard	guard(_state);

    if (_curState == NONE)
      _wake.signal();
    _curState = st;
  }

  void		Manager::sendRequest(const ARequest *req)
  {
    Thread::MutexGuard	guard(_sock);

    (void)req;
    _state.lock();
    if (_curState == TCP)
      {
	_state.unlock();
	_mSock.send("coucou", 6);
      }
    else if (_curState == UDP)
      {
	_state.unlock();
	_gSock.send("coucou", 6, _gIp, _gPort);
      }
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

  void		Manager::udpMode()
  {
    ARequest	*req = 0;
    sf::Packet	packet;

    _sock.lock();
    _gSock.receive(packet, _gIp, _gPort);
    _sock.unlock();

    // Protocol Job
    if (req == 0)
      return ;
    _reqlist.lock();
    _requests.push_back(req);
    _reqlist.unlock();
  }

  void		Manager::tcpMode()
  {
    ARequest	*req = 0;
    sf::Packet	packet;

    _sock.lock();
    _mSock.receive(packet);
    _sock.unlock();

    // Protocol Job
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
	    break;
	  }
      }
    return (0);
  }
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
