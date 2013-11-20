#include	"ClientCallback.hh"

ClientCallback::ClientCallback(Client *client, void (Application::*func)(Client *)) :
  _callback(func), _client(client)
{
}

ClientCallback::~ClientCallback()
{

}

void	ClientCallback::operator()(Application *app)
{
  _callback(app, _client);
}
