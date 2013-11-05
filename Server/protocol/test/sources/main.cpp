#include	<iostream>
#include	<iomanip>
#include	<vector>
#include	"types.hh"
#include	"AuthRequest.hh"
#include	"ARequest.hh"
#include	"Protocol.hpp"

int	main()
{
  Auth::Connect			c("toto", 1644);
  std::vector<Protocol::Byte>	bytes;

  bytes = Protocol::product(c);
  // std::cout << "Size: " << bytes.size() << std::endl;
  for (std::vector<Protocol::Byte>::iterator it = bytes.begin(); it != bytes.end(); ++it)
    {
      std::cout << std::hex << (char)(*it);
    }
  std::cout << std::endl;

  // Auth::Connect			*output = dynamic_cast<Auth::Connect *>(Protocol::consume(bytes));
  // std::cout << output << std::endl;
  // (void)output;
  return (0);
}
