#include	<iostream>
#include	<iomanip>
#include	<vector>
#include	"types.hh"
#include	"AuthRequest.hh"
#include	"ARequest.hh"
#include	"Protocol.hpp"
#include	"TcpClient.h"

int	main()
{
  net::TcpClient		client;
  Auth::Connect			c("Ruby", 1664);
  std::vector<Protocol::Byte>	bytes;

  bytes = Protocol::product(c);
  // std::cout << "Size: " << bytes.size() << std::endl;
  for (std::vector<Protocol::Byte>::iterator it = bytes.begin(); it != bytes.end(); ++it)
    {
      std::cout << std::hex << (char)(*it);
    }
  std::cout << std::endl;

  client.init("127.0.0.1", "44201");
  client.writeIntoBuffer(bytes, bytes.size());
  client.send();
  client.close();
  // Auth::Connect			*output = dynamic_cast<Auth::Connect *>(Protocol::consume(bytes));
  // std::cout << output << std::endl;
  // (void)output;
  return (0);
}
