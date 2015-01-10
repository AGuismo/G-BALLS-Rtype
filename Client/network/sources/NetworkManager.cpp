#include	<iostream>
#include	<algorithm>
#include	"Protocol.hpp"
#include	"NetworkManager.hh"

bool	consume(std::vector<Protocol::Byte> &b, ARequest *&req);
bool	product(std::vector<Protocol::Byte> &b, const ARequest *req);

namespace	network
{
	Manager	&Manager::getInstance()
	{
		static Manager	singleton;

		return (singleton);
	}

	Manager::Manager() :
		_th(Func::Bind(&Manager::routine, this))
	{
		_tcp.active = false;
		_udp.active = false;
		_active = false;
	}

	Manager::~Manager()
	{
		stop();
		join();
		_active = false;
	}

	void	Manager::run()
	{
		_th.run();
		_active = true;
	}

	void	Manager::stop()
	{
		Thread::MutexGuard	guard(_threadLock);

		_active = false;
	}

	void	Manager::join()
	{
		_th.join();
	}

	bool	Manager::setTcp(const sf::IpAddress &ip, unsigned short port)
	{
		Thread::MutexGuard	guard(_socketLock);
		sf::Socket::Status	st;

		if (_tcp.active)
			return (false);
		st = _tcp.mSock.connect(ip, port);
		if (st == sf::Socket::Done)
		{
			_tcp.active = true;
			_select.add(_tcp.mSock);
			_condSocketChanged.signal();
		}
		else
			_tcp.active = false;
		return (_tcp.active);
	}

	void	Manager::setUdp(const sf::IpAddress &ip, unsigned short port)
	{
		Thread::MutexGuard	guard(_socketLock);

		_udp.gIp = ip;
		_udp.gPort = port;
		_udp.active = true;
		_select.add(_udp.gSock);
		_condSocketChanged.signal();
	}

	void	Manager::closeTcp(void)
	{
		Thread::MutexGuard	guard(_socketLock);

		if (_tcp.active == true)
		{
			_select.remove(_tcp.mSock);
			_tcp.mSock.disconnect();
			_tcp.active = false;
			_condSocketChanged.signal();
		}
	}

	bool				Manager::isConnected(SendType type) const
	{
		if (type == TCP)
			return (_tcp.active);
		else if (type == UDP)
			return (_udp.active);
		return (false);
	}

	ARequest	*Manager::recvRequest()
	{
		return (recvRequestType().second);
	}

	std::pair<Manager::SendType, ARequest *>	Manager::recvRequestType()
	{
		Thread::MutexGuard				guard(_requests.lock);
		std::pair<SendType, ARequest *>	req;

		if (_requests.output.empty())
			return (std::make_pair(NONE, (ARequest *)0));
		req = _requests.output.front();
		_requests.output.pop_front();
		return (req);
	}

	void				Manager::udpMode()
	{
		ARequest			*req = 0;
		Protocol::Byte		bytes[1024];
		std::size_t			extracted;
		std::vector<Protocol::Byte>	packet;
		sf::Socket::Status		st;
		st = _udp.gSock.receive(bytes, 1024, extracted, _udp.gIp, _udp.gPort);
		if (st == sf::Socket::Error)
		{
			_udp.active = false;
			return;
		}
		else if (st == sf::Socket::Disconnected)
		{
			_udp.active = false;
			return;
		}
		packet.insert(packet.begin(), bytes, bytes + extracted);
		while (consume(packet, req))
		{
#if defined(DEBUG)
			std::cout << "network::Manager::udpMode(const ARequest *) -- "
				<< "Last Packet Size: " << packet.size() << std::endl;
#endif
			_requests.lock.lock();
			_requests.output.push_back(std::make_pair(UDP, req));
			_requests.lock.unlock();
		}
	}
	//
	void					Manager::tcpMode()
	{
		ARequest			*req = 0;
		std::vector<Protocol::Byte>	packet;
		Protocol::Byte		bytes[1024];
		std::size_t			received;
		sf::Socket::Status	status;

		status = _tcp.mSock.receive(bytes, 1024, received);
		if (status == sf::Socket::Error)
		{
			_tcp.active = false;
			return;
		}
		else if (status == sf::Socket::Disconnected)
		{
			_tcp.mSock.disconnect();
			_tcp.active = false;
			return;
		}

		packet.insert(packet.begin(), _tcp.notRead.begin(), _tcp.notRead.end());
		packet.insert(packet.end(), bytes, bytes + received);

		while (consume(packet, req))
		{
#if defined(DEBUG)
			std::cout << "network::Manager::tcpMode(const ARequest *) -- "
				<< "Packet Size: " << packet.size() << std::endl;
#endif
			_requests.lock.lock();
			_requests.output.push_back(std::make_pair(TCP, req));
			_requests.lock.unlock();
		}
		_tcp.notRead = packet;
	}

	int		Manager::routine()
	{
		while (_active)
		{
			if (!_tcp.active && !_udp.active)
			{
				_socketLock.lock();
				_condSocketChanged.wait(_socketLock);
			}
			else
			{
				_select.wait(sf::milliseconds(100));
				_socketLock.lock();
				if (_tcp.active && _select.isReady(_tcp.mSock))
					tcpMode();
				if (_udp.active && _select.isReady(_udp.gSock))
					udpMode();

				while (!_requests.input.empty())
				{
					std::pair<SendType, ARequest *>	req = _requests.input.front();
					std::vector<Protocol::Byte>		data;

					_requests.lock.lock();
					_requests.input.pop_front();
					_requests.lock.unlock();
					if (!product(data, req.second))
					{
						_socketLock.unlock();
						continue; // Error - Request Lost. Not gonna happend theoricaly
					}
					if (req.first == TCP && _tcp.active)
					{
						Protocol::Byte					buff[1024];

						std::copy(data.begin(), data.end(), buff);
						_tcp.mSock.send(buff, data.size());
					}
					else if (req.first == UDP && _udp.active)
					{
						Protocol::Byte					buff[1024];

						std::copy(data.begin(), data.end(), buff);
						_udp.gSock.send(buff, data.size(), _udp.gIp, _udp.gPort);
					}
					else // Error - Request Lost. Not gonna happend with good usage.
						0 == 0;
				}
			}
			_socketLock.unlock();
		}
		return (0);
	}
}

bool		consume(std::vector<Protocol::Byte> &b, ARequest *&req)
{
	int		extracted;

	if (b.empty())
		return (false);
	try
	{
		req = Protocol::consume(b, extracted);
	}
	catch (Protocol::ConstructRequest &e)
	{
#if defined(DEBUG)
		std::cerr << "Manager::operator>>(sf::Packet &, const ARequest *): " << e.what() << std::endl;
#endif
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
#if defined(DEBUG)
		std::cerr << "Manager::operator<<(sf::Packet &, const ARequest *): " << e.what() << std::endl;
#endif
		b.clear();
		delete req;
		return (false);
	}
	delete req;
	return (true);
}

network::Exception::Exception(const std::string &msg) throw() :
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
