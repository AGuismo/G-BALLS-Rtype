//
// MenuNetwork.hh for menunetwork in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:35:33 2013 brigno
// Last update Tue Nov  5 03:37:07 2013 brigno
//

#ifndef		__NETWORK_HH__
# define	__NETWORK_HH__

# include	<SFML/Network.hpp>
# include	<SFML/Graphics.hpp>

class		Network
{
public:
  sf::TcpSocket	_tcpSocket;
  sf::IpAddress	_ip;
  int		_port;

public:
  Network(const std::string &ip, const std::string &port);
  ~Network();

private:
  Network(const Network &other);
  Network operator=(const Network &other);

public:
  void	tcpConnect(void);
  void	udpConnect(void);
};

#endif	/* !__NETWORK_HH__ */
