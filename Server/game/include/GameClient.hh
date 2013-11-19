#ifndef GAMECLIENT_H_
# define GAMECLIENT_H_

# if defined(linux)
#  include	<netinet/in.h>
# elif defined(WIN32)
#  include	<WinSock2.h>
#endif
# include	<queue>
# include	<map>
# include	<list>
# include	"ARequest.hh"
# include	"RequestQueue.hh"
# include	"RequestCode.hh"

class		ARequest;

class		Game;
class		Missile;
class		Referee;

namespace	game
{
  class		Player;
}

namespace	game
{
  class Client
  {
    /*typedef void(*request_callback)(ARequest *, Client *);
      typedef std::map<requestCode::CodeID, request_callback> request_callback_map;*/
  public:
    Client();
    Client(struct sockaddr_in addr);
    virtual ~Client();

  public:
    void	update(Game &game);
    void	finalize();

  private:
    Client(Client const&);
    Client& operator=(Client const&);

  public:
    bool			inUse(void) const {return (_used);};
    void			inUse(bool used) {_used = used;};

  public:
    ARequest			*requestPop();
    void			requestPush(ARequest *req);

  public:
    requestCode::SessionID	SessionID() const;
	void			alive(const bool &state);
    void			SessionID(const requestCode::SessionID);

  public:
    void			game(Game *game);
    Game			*game(void) const;
    void			player(game::Player *player);
    game::Player		*player(void) const;

    struct sockaddr_in getAddr() const { return _addr; };
    void			setAddr(struct sockaddr_in addr) { _addr = addr; };

  private:
    game::Player		*_player;
    Game			*_game;
    bool			_alive;
    int				_updateToLive;

  private:
    bool			_used;
    RequestQueue		_input;
    RequestQueue		_output;
    /*request_callback_map _requestCallback;*/

  private:
    requestCode::SessionID	_id;
    struct sockaddr_in		_addr;

    friend class ::Game;
    friend class ::Referee;
  };
}

#endif /* GAMECLIENT_H_ */
