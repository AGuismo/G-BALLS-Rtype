#ifndef NETWORKMANAGER_H_
# define NETWORKMANAGER_H_

#include	<SFML/Network.hpp>
#include	<deque>
#include	"Threads.hpp"
#include	"ThreadMutex.hh"
#include	"ThreadCond.hh"
#include	"Protocol.hpp"

class	ARequest;

namespace	network
{
  class Manager
  {
    typedef Threads<int (Manager::*)()>		thread_type;
    typedef std::deque<ARequest *>		request_list;
  public:
    enum	State
      {
	NONE,
	TCP,
	UDP,
	SHUTDOWN
      };
  public:
    Manager();
    virtual ~Manager();

  public:
    void	stop(void);
    void	join(void);

  public:
    void	initialize(void);
    void	setTcp(const sf::IpAddress &ip, unsigned short port);
    void	setUdp(const sf::IpAddress &ip, unsigned short port);
    bool	isConnected();
    void	closeTcp();
    void	run(void);
    void	switchTo(State s);
    ARequest	*recvRequest(void);
    void	sendRequest(const ARequest *);

  private:
    int		routine(void);
    void	tcpMode(void);
    void	udpMode(void);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);

  private:
    thread_type		_th;
    request_list	_requests;
    Thread::Mutex	_state;
    Thread::Mutex	_reqlist;
    Thread::Mutex	_sock;
    Thread::Cond	_wake;
    struct
    {
      std::vector<Protocol::Byte>	notRead;
      sf::TcpSocket			mSock;
    }			_tcp;

    struct
    {
      sf::UdpSocket	gSock;
      sf::IpAddress	gIp;
      unsigned short	gPort;
    }			_udp;
    State		_curState;
    bool		_connected;
  };

  class Exception
  {
  public:
    Exception(const std::string &msg) throw();
    virtual ~Exception() throw();

  public:
    Exception(Exception const&) throw();
    Exception& operator=(Exception const&) throw();

  public:
    virtual const char	*what() const throw();

  private:
    std::string		_what;
  };
}

#endif /* NETWORKMANAGER_H_ */
