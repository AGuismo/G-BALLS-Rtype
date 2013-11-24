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
#include	"NetException.h"
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
  std::cout << "Received request code: " << req->code()
	    << ". Detail: " << detail(req) << std::endl;
  client.readFromBuffer(bytes, count);
  return (req);
}

void		send_req(net::TcpClient &client, ARequest *req)
{
  std::vector<Protocol::Byte>	bytes;

  bytes = Protocol::product(*req);
  client.writeIntoBuffer(bytes, bytes.size());
  client.send();
}

int			main()
{
  net::TcpClient	client;
  net::streamManager	m;
  stdin			input;
  std::string		IpAdress;
  std::string		port;
  bool			connected = false;

  input.fd = 0;
  std::cout << "R-Type Root access" << std::endl;
  std::cout << "IpAdress: ";
  std::cin >> IpAdress;
  std::cout << "Port: ";
  std::cin >> port;
  try
    {
      client.init(IpAdress.c_str(), port.c_str());
    }
  catch (net::Exception &e)
    {
      std::cerr << "Error: Can't reach the server (" << e.what() << ")" << std::endl;
      return (0);
    }
  std::cout << "Connection succeed" << std::endl;
  client.monitor(true, false);
  input.monitor(true, false);
  m.setMonitor(client);
  m.setMonitor(input);
  while (true)
    {
      m.run();
      if (input.read())
	{
	  std::string	input;

	  std::cin >> input;
	  if (input == "/connect")
	    {
	      std::string	Login;
	      std::string	Password;

	      std::cout << "Authentification to the server" << std::endl;
	      std::cout << "Login: ";
	      std::cin >> Login;
	      std::cout << "Password: ";
	      std::cin >> Password;
	      send_req(client, new Auth::Connect(Login.c_str(), md5(Password.c_str())));
	      connected = true;
	    }
	  else if (input == "/user")
	    {
	      std::string	Login;
	      std::string	Password;

	      if (connected == false)
		{
		  std::cerr << "Error: You're not connected" << std::endl;
		  continue;
		}
	      std::cout << "Create new user" << std::endl;
	      std::cout << "Login: ";
	      std::cin >> Login;
	      std::cout << "Password: ";
	      std::cin >> Password;
	      send_req(client, new Auth::NewUser(Login.c_str(), md5(Password.c_str())));
	    }
	  else if (input == "/shutdown")
	    {
	      if (connected == false)
		{
		  std::cerr << "Error: You're not connected" << std::endl;
		  continue;
		}
	      send_req(client, new root::Shutdown());
	    }
	  else if (input == "/help")
	    {
	      std::cout << "Commands:" << std::endl
			<< "/connect : Authentification" << std::endl
			<< "/user : Create new user" << std::endl
			<< "/help : Display the help" << std::endl
			<< "/shutdown : Close the server" << std::endl;
	    }
	  else
	    {
	      std::cerr << "Invalid command" << std::endl;
	      std::cout << "Commands:" << std::endl
			<< "/connect : Authentification" << std::endl
			<< "/user : Create new user" << std::endl
			<< "/help : Display the help" << std::endl
			<< "/shutdown : Close the server" << std::endl;
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
    }
  client.close();
  return (0);
}
