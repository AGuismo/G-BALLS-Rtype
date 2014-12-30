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
//# include	"ARequest.hh"
# include	"RequestQueue.hh"
# include	"RequestCode.hh"

class		ARequest;

namespace	game
{
  class		Player;
  class		Game;
  class		Missile;
  class		Referee;
}

namespace	game
{
  class Client
  {
    /*typedef void(*request_callback)(ARequest *, Client *);
      typedef std::map<requestCode::CodeID, request_callback> request_callback_map;*/
  public:
    Client(requestCode::SessionID);
    Client(requestCode::SessionID, struct sockaddr_in addr);
    virtual ~Client();

  public:
    void	update(Game &game);
    void	finalize();

  private:
    Client(Client const&);
    Client& operator=(Client const&);

    // public:
    //   bool			inUse(void) const {return (_used);};
    //   void			inUse(bool used) {_used = used;};

  public:
    ARequest			*requestPop();
    ARequest			*requestPopOutput();
    void			requestPushInput(ARequest *req);
    void			requestPush(ARequest *req);

  public:
    requestCode::SessionID	sessionID() const;
    void			sessionID(const requestCode::SessionID);
    void			alive(const bool &state);
    bool			alive() const ;
    void			hasLeft(const bool &state);

  public:
    void			game(Game *game);
    Game			*game(void) const;
    void			player(game::Player *player);
    game::Player		*player(void) const;

    struct sockaddr_in		getAddr() const { return _addr; };
    void			setAddr(struct sockaddr_in addr) { _addr = addr; };
    bool			hasLeft() const { return _hasLeft; };
    bool			hasJoin() const { return _hasJoin; };
    void			hasJoin(bool b) { _hasJoin = b; };

  private:
    game::Player		*_player;
    bool			_alive;
    int				_updateToLive;

  private:
    bool			_hasLeft;
    bool			_hasJoin;
    RequestQueue		_input;
    RequestQueue		_output;
    /*request_callback_map _requestCallback;*/

  private:
    struct sockaddr_in		_addr;
    requestCode::SessionID	_id;

    friend class Game;
    friend class Referee;
  };
}

#endif /* GAMECLIENT_H_ */
