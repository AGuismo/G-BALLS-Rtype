#include	<iostream>
#include	<iomanip>
#include	<vector>
#include	<typeinfo>
#if defined(WIN32)
# include	<winsock2.h>
#endif
#include	"types.hh"
#include	"AuthRequest.hh"
#include	"PartyRequest.hh"
#include	"SessionRequest.hh"
#include	"ServerRequest.hh"
#include	"ARequest.hh"
#include	"Protocol.hpp"
#include	"TcpClient.h"
#include	"streamManager.h"
#include	"MD5.hh"

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

ARequest			*getReq(net::TcpClient &client)
{
  std::vector<Protocol::Byte>	bytes;
  int				count;
  ARequest			*req;

  client.lookRead(bytes, 512);
  req = Protocol::consume(bytes, count);
  std::cout << "Extracted: " << count << std::endl;
  std::cout << "Received data code: " << req->code() << std::endl;
  client.readFromBuffer(bytes, count);
  return (req);
}

void	network()
{
  net::TcpClient		client;
  Auth::NewUser			new_usr("Ruby", md5("1664"));
  Auth::Connect			authConnect("Ruby", md5("1664"));
  std::vector<Protocol::Byte>	bytes;
  ARequest				*req;
  Party::Start			startGame;
  net::streamManager		m;

  client.init("127.0.0.1", "44201");
  client.monitor(true, false);
  m.setMonitor(client);

  bytes = Protocol::product(new_usr);
  client.writeIntoBuffer(bytes, bytes.size());
  client.send();
  m.run();
  client.recv();
  req = getReq(client);
  std::cout << "Response: " << req->code() << std::endl;

  bytes.clear();
  bytes = Protocol::product(authConnect);
  client.writeIntoBuffer(bytes, bytes.size());
  client.send();
  m.run();
  client.recv();
  req = getReq(client);
  std::cout << "Response: " << req->code() << std::endl;
  req = getReq(client);
  std::cout << "Session: " << (dynamic_cast<SessionRequest *>(req))->SessionID() << std::endl;

  // bytes = Protocol::product(startGame);
  // client.writeIntoBuffer(bytes, bytes.size());
  // client.send();
  // m.run();
  // client.recv();
  // req = getReq(client);
  // std::cout << "Response: " << req->code() << std::endl;
  // req = getReq(client);
  // std::cout << "Launch Game: " << (dynamic_cast<Party::Launch *>(req))->code() << std::endl;

  client.close();
}

int	main()
{
  Auth::Connect			authConnect("Ruby", md5("1664"));
  Auth::ChangePass		authPass("Ruby", md5("1664"), md5("4661"), 5348);
  ServerRequest			servReq(requestCode::server::FORBIDDEN);

  // test(authConnect);
  // test(authPass);
  // test(servReq);
  // std::cout << "Size: " << bytes.size() << std::endl;

  network();
  return (0);
}
