#ifndef MENUGAME_H_
# define MENUGAME_H_

# include	<list>
# include	<string>
# include	"types.hh"
# include	"MenuClient.hh"

class Game;

namespace	menu
{
  class Game
  {
  public:
    static const Ruint8 OUT_GAME = 0;
    static const Ruint8 IN_GAME = 1;
    static const Ruint8 CANCELED = 2;
    static const Ruint8 FINISHED = 3;
  public:
    typedef std::list<Client *>	client_list;

  public:
    Game(Client *);
    virtual ~Game();

  public:
    bool			newPlayer(Client *);
    bool			delPlayer(const std::string &name);
    const client_list		&clients() const;

    bool				ispassword() const;
    const requestCode::PasswordType	&password() const;
    void				password(const requestCode::PasswordType &);

    const std::string		&partyName() const;
    void			partyName(const std::string &);

    Ruint8			availableSlots(void) const;

    Ruint8			maxPlayers(void) const;
    void			maxPlayers(Ruint8);

    Ruint8			status(void) const;
    void			status(Ruint8);

    Client			*owner() const;

    client_list			&getClients(void);

    template <typename Req>
    void			broadcast(const Req &req);

  private:
    Game(Game const&);
    Game& operator=(Game const&);

  private:
    Client			*_owner;
    client_list			_clients;
    std::string			_partyName;
    bool			_ispassword;
    Ruint8			_maxPlayers;
    Ruint8			_status;
    ::Game			*_game;
    requestCode::PasswordType	_password;

  private:
    struct	Predicate : public std::unary_function<Client *, bool>
    {
      Predicate(const std::string &name);
      bool	operator()(const Client *);

    private:
      const std::string	&_name;
    };
  };

  template <typename Req>
  void			Game::broadcast(const Req &req)
  {
    for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
      (*it)->requestPush(new Req(req));
  }
}


#endif /* MENUGAME_H_ */
