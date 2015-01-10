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
		typedef Threads<int (Manager::*)()>	thread_type;
	public:
		enum SendType
		{
			NONE,
			TCP,
			UDP
		};

	private:
		typedef std::deque<std::pair<SendType, ARequest *> >	request_list;

	private:
		Manager();
		virtual ~Manager();

	public:
		static Manager	&getInstance();

	public:
		void	stop(void);
		void	join(void);
		void	run(void);

	public:
		// TCP
		bool	setTcp(const sf::IpAddress &ip, unsigned short port);
		void	closeTcp();

		// UDP
		void	setUdp(const sf::IpAddress &ip, unsigned short port);

		// BOTH
		bool	isConnected(SendType) const;

	public:
		ARequest						*recvRequest(void);
		std::pair<SendType, ARequest *>	recvRequestType(void);

		template <typename Req>
		void							sendRequest(const Req &toSend, SendType type)
		{
			Thread::MutexGuard	guard(_requests.lock);

			_requests.input.push_back(std::make_pair(type, new Req(toSend)));
		}

	private:
		int		routine(void);
		void	tcpMode(void);
		void	udpMode(void);

	private:
		Manager(Manager const&);
		Manager& operator=(Manager const&);

	private:
		thread_type		_th;
		bool			_active;
		Thread::Mutex	_threadLock;
		Thread::Mutex	_socketLock;
		Thread::Cond	_condSocketChanged;

		struct
		{
			request_list	input;
			request_list	output;
			Thread::Mutex	lock;
		}					_requests;

		struct
		{
			std::vector<Protocol::Byte>	notRead;
			sf::TcpSocket					mSock;
			bool							active;
		}								_tcp;

		struct
		{
			sf::UdpSocket		gSock;
			sf::IpAddress		gIp;
			unsigned short	gPort;
			bool				active;
		}					_udp;

		sf::SocketSelector	_select;
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
