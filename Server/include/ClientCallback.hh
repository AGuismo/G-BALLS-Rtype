#ifndef CLIENTCALLBACK_H_
# define CLIENTCALLBACK_H_

# include	"ICallbacks.hh"
# include	"Bind.hpp"

class	Client;
class	Application;

class ClientCallback : public ICallbacks
{
public:
  ClientCallback(Client *client, void (Application::*)(Client *));
  virtual ~ClientCallback();

public:
  void	operator()(Application *);

private:
  ClientCallback(ClientCallback const&);
  ClientCallback& operator=(ClientCallback const&);

protected:
  Function<void, Application, Client *>	_callback;
  Client					*_client;
};


#endif /* CLIENTCALLBACK_H_ */
