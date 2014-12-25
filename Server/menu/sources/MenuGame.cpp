#include	<algorithm>
// #include	"Game.h"
#include	"MenuGame.hh"
#include	"Client.hh"

namespace	menu
{
  Game::Game(Client *client) :
    _owner(client), _ispassword(false), _status(requestCode::party::OUT_GAME) //, _game(0)
  {
    _clients.push_back(client);
    client->currentGame(this);
  }

  Game::~Game()
  {
    for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
      (*it)->currentGame(0);
  }

  bool				Game::newPlayer(Client *client)
  {
    if (availableSlots() == 0 || status() == requestCode::party::IN_GAME)
      return (false);
    _clients.push_back(client);
    client->currentGame(this);
    return (true);
  }

  bool				Game::delPlayer(const std::string &name)
  {
    client_list::iterator	it = std::find_if(_clients.begin(), _clients.end(), Predicate(name));

    if (it == _clients.end())
      return (false);
    (*it)->currentGame(0);
    _clients.erase(it);
    return (true);
  }

  const Game::client_list	&Game::clients() const
  {
    return (_clients);
  }

    bool				Game::ispassword() const
  {
    return (_ispassword);
  }

  const requestCode::PasswordType	&Game::password() const // Undef behaviour if no password
  {
    return (_password);
  }

  void				Game::password(const requestCode::PasswordType &password)
  {
    _password = password;
    _ispassword = true;
  }

  const std::string		&Game::partyName() const
  {
    return (_partyName);
  }

  void				Game::partyName(const std::string &partyname)
  {
    _partyName = partyname;
  }

  Ruint8		Game::availableSlots(void) const
  {
    return (_maxPlayers - _clients.size());
  }

  Ruint8		Game::maxPlayers(void) const
  {
    return (_maxPlayers);
  }

  void			Game::maxPlayers(Ruint8 maxPlayers)
  {
    _maxPlayers = maxPlayers;
  }

  Ruint8		Game::status(void) const
  {
    return (_status);
  }

  void			Game::status(Ruint8 status)
  {
    _status = status;
  }

  Client		*Game::owner() const
  {
    return (_owner);
  }

  Game::client_list	&Game::getClients(void)
  {
    return (_clients);
  }

  // ::Game			*Game::game(void) const
  // {
  // 	  return (_game);
  // }
  // void			Game::game(::Game *game)
  // {
  // 	  _game = game;
  // }

  Game::Predicate::Predicate(const std::string &name) :
    _name(name)
  {

  }

  bool	Game::Predicate::operator()(const Client *c)
  {
    return (c->username() == _name);
  }
}
