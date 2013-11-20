#include	<map>
#include	<iostream>
#include	<iomanip>
#include	<vector>
#include	<typeinfo>
#if defined(WIN32)
# include	<winsock2.h>
#endif
#include	"types.hh"
#include	"RequestCode.hh"
#include	"AuthRequest.hh"
#include	"PartyRequest.hh"
#include	"SessionRequest.hh"
#include	"ServerRequest.hh"
#include	"ARequest.hh"
#include	"Protocol.hpp"
#include	"TcpClient.h"
#include	"streamManager.h"
#include	"MD5.hh"
#include	"AMonitorable.h"
#include	"AliveRequest.h"
#include	"UdpClient.h"
#include	"RequestInfo.hpp"

struct	stdin : public net::AMonitorable
{
  int	fd;
  int	getSocket() const {return fd;};
};

const char	*detail(const ARequest *req)
{
  return (Info<ServerRequest>::Detail(req->code()));
}

ARequest                        *uget_req(net::UdpClient &client)
{
    std::vector<Protocol::Byte>   bytes;
    int                           count;
    ARequest                      *req;

    client.lookRead(bytes, 512);
  try
  {
      req = Protocol::consume(bytes, count);
  }
  catch (...)
  {
      return (0);
  }
  std::cout << "Extracted: " << count << std::endl;
  std::cout << "Received request code: " << req->code()
            << ". Detail: " << detail(req) << std::endl;
  client.readFromBuffer(bytes, count);
  return (req);
}

void            usend_req(net::UdpClient &client, ARequest *req)
{
    std::vector<Protocol::Byte>   bytes;

    std::cout << "Send request code: " << req->code()
	      << ". Detail: " << detail(req) << std::endl;
    bytes = Protocol::product(*req);
    client.writeIntoBuffer(bytes, bytes.size());
    client.send();
}

ARequest			*get_req(net::TcpClient &client)
{
  std::vector<Protocol::Byte>	bytes;
  int				count;
  ARequest			*req;

  client.lookRead(bytes, 512);
  try
    {
      req = Protocol::consume(bytes, count);
    }
  catch (...)
    {
      std::cout << "Get Req fail" << std::endl;
      return (0);
    }
  std::cout << "Extracted: " << count << std::endl;
  std::cout << "Received request code: " << req->code()
	    << ". Detail: " << detail(req) << std::endl;
  client.readFromBuffer(bytes, count);
  return (req);
}

void		send_req(net::TcpClient &client, ARequest *req)
{
  std::vector<Protocol::Byte>	bytes;

  std::cout << "Send request code: " << req->code()
	    << ". Detail: " << detail(req) << std::endl;
  bytes = Protocol::product(*req);
  client.writeIntoBuffer(bytes, bytes.size());
  client.send();
}

int			main(int ac, char **av)
{
  bool			activated = true;
  net::TcpClient	client;
  net::UdpClient	uclient;
  net::streamManager	m;
  stdin			input;

  input.fd = 0;
  if (ac == 2)
  {
    client.init(av[1], "44201");
    uclient.init(av[1], "44202");
  }
  else
  {
    client.init("127.0.0.1", "44201");
    uclient.init("127.0.0.1", "44202");
  }
  client.monitor(true, false);
  uclient.monitor(true, false);
  input.monitor(true, false);
  m.setMonitor(client);
  m.setMonitor(uclient);
  m.setMonitor(input);
  while (activated)
    {
      m.run();
      if (input.read())
	{
	  char	input;

	  std::cin >> input;
	  // if (std::cin.eof() == 1)
	  //   break;
	  switch (input)
	    {
	    case '\0':
	      activated = false;
	      break;
	    case 'a':
	      send_req(client, new Auth::Connect("Ruby", md5("1664")));
	      break;
	    case 'b':
	      send_req(client, new Auth::NewUser("Ruby", md5("1664")));
	      break;
	    case 'c':
	      send_req(client, new Party::List());
	      break;
	    case 'd':
	      send_req(client, new Party::Create("Toto", 4));
	      break;
	    case 'e':
	      send_req(client, new Party::Start());
	      break;
	    case 'f':
	      send_req(client, new Party::Cancel());
	      break;
	    case 'g':
	      send_req(client, new Party::Join("Toto"));
	      break;
	    case 'h':
	      std::cout << "a: " << "Auth::Connect" << std::endl
			<< "b: " << "Auth::NewUser" << std::endl
			<< "c: " << "Party::List" << std::endl
			<< "d: " << "Party::Create" << std::endl
			<< "e: " << "Party::Start" << std::endl
			<< "f: " << "Party::Cancel" << std::endl
			<< "i: " << "AliveRequest" << std::endl
			<< "g: " << "Party::Join" << std::endl;
	      break;
	    case 'i':
	      usend_req(uclient, new AliveRequest());
	      break;
	    default:
	      break;
	    }
	}
      if (client.isDisconnected())
	{
	  std::cout << "Disconnected" << std::endl;
	  break;
	}
      if (client.read())
	{
	  ARequest	*req;

	  client.recv();
	  while ((req = get_req(client)) != 0);
	}
      if (uclient.read())
	{
	  ARequest	*req;

	  uclient.recv();
	  while ((req = uget_req(uclient)) != 0);
	}
    }
  client.close();
  return (0);
}
