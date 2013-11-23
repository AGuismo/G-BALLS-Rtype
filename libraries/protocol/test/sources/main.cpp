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
#include	"EventRequest.hh"
#include	"LeaveRequest.h"
#include	"ElemRequest.hh"

struct	stdin : public net::AMonitorable
{
  int	fd;
  int	getSocket() const {return fd;};
};

const char	*detail(const ARequest *req)
{
  if (typeid(*req) == typeid(ServerRequest))
    return (Info<ServerRequest>::Detail(req->code()));
  return ("None");
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

void            usend_req(net::UdpClient &client, AGameRequest *req, requestCode::SessionID id)
{
    std::vector<Protocol::Byte>   bytes;

    req->SessionID(id);
    std::cout << "Send request code: " << req->code()
	      << ". Detail: " << detail(req) << std::endl;
    bytes = Protocol::product(*req);
    std::cout << "nb bytes = " << bytes.size() << std::endl;
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
  requestCode::SessionID id = 0;

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
			<< "j: " << "moveRequest" << std::endl
			<< "k: " << "fireRequest" << std::endl
			<< "l: " << "LeaveRequest" << std::endl
			<< "g: " << "Party::Join" << std::endl;
	      break;
	    case 'i':
		usend_req(uclient, new AliveRequest(), id);
	      break;
	    case 'j':
		usend_req(uclient, new EventRequest(0, 2), id);
	      break;
	    case 'k':
		usend_req(uclient, new EventRequest(1, 1), id);
	      break;
	    case 'l':
		usend_req(uclient, new LeaveRequest(), id);
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
	  while ((req = get_req(client)) != 0)
	  {
	      if (SessionRequest *session = dynamic_cast<SessionRequest *>(req))
	      {
		  id = session->SessionID();
		  std::cout << "ID client is " << id;
	      }
	  }
	}
      if (uclient.read())
	{
	  ARequest	*req;

	  uclient.recv();
	  while ((req = uget_req(uclient)) != 0)
	  {
	      if (ElemRequest *elem = dynamic_cast<ElemRequest *>(req))
	      {
		  (void)elem;
		  //id = elem->SessionID();
		  //std::cout << "ELEM REQUEST :: ID client is " << id;
		  //std::cout << " : " << elem->pos() << std::endl;
	      }
	      else if (DeathRequest *elem = dynamic_cast<DeathRequest *>(req))
	      {
		  (void)elem;
		  std::cout << "YOU ARE DEAD" << std::endl;
	      }
	      else if (LooseRequest *elem = dynamic_cast<LooseRequest *>(req))
	      {
		  (void)elem;
		  std::cout << "YOU LOOSE" << std::endl;
	      }
	  }
	}
    }
  client.close();
  return (0);
}
