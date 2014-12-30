//
// Network.cpp for network in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 03:11:10 2013 brigno
// Last update Tue Nov  5 03:40:45 2013 brigno
//

#include	"Network.hh"
#include	<sstream>

Network::Network(const std::string &ip, const std::string &port):
  _ip(ip)
{
  std::stringstream	tmp;
  int			tmpPort;

  tmp << port;
  tmp >> tmpPort;
  this->_port = tmpPort;
}

Network::~Network()
{
}

void	Network::tcpConnect()
{
  this->_tcpSocket.connect(this->_ip, this->_port);
}
