#include	<iostream>
#include	<iomanip>
#include	<vector>
#include	<typeinfo>
#include	"types.hh"
#include	"AuthRequest.hh"
#include	"ServerRequest.hh"
#include	"ARequest.hh"
#include	"Protocol.hpp"
#include	"TcpClient.h"

template <typename T>
void	test(T &req)
{
  std::vector<Protocol::Byte>	bytes;

  std::cout << "Testing: " << typeid(req).name() << std::endl;
  bytes = Protocol::product(req);
  for (std::vector<Protocol::Byte>::iterator it = bytes.begin(); it != bytes.end(); ++it)
    {
      std::cout << std::hex << (char)(*it);
    }
  std::cout << std::dec << std::endl;

  int			count;
  T			*output = dynamic_cast<T *>(Protocol::consume(bytes, count));
  if (output != 0)
    std::cout << typeid(req).name() << ": Correct formatting" << std::endl;
  else
    std::cout << typeid(req).name() << ": Incorrect formatting" << std::endl;
}

void	network()
{
  net::TcpClient		client;
  Auth::Connect			authConnect("Ruby", 1664);
  std::vector<Protocol::Byte>	bytes;
  int				count;

  bytes = Protocol::product(authConnect);
  client.init("127.0.0.1", "44201");
  client.writeIntoBuffer(bytes, bytes.size());
  client.send();
  client.recv();
  std::cout << "Received data" << std::endl;
  client.readFromBuffer(bytes, 512);
  ARequest	*req = Protocol::consume(bytes, count);
  std::cout << "Received data code: " << req->code() << std::endl;
  client.close();
}

int	main()
{
  Auth::Connect			authConnect("Ruby", 1664);
  Auth::ChangePass		authPass("Ruby", 1664, 4661, 5348);
  ServerRequest			servReq(requestCode::server::FORBIDDEN);

  test(authConnect);
  test(authPass);
  test(servReq);
  // std::cout << "Size: " << bytes.size() << std::endl;

  network();
  return (0);
}
