#ifndef GAMECLIENT_H_
# define GAMECLIENT_H_

# include	<queue>
# include	"RequestQueue.hh"
# include	"RequestCode.hh"

class	ARequest;

class		Game;
namespace	game
{
  class		Player;
}
namespace	game
{

  class Client
  {
  public:
    Client();
	Client(struct sockaddr_in addr);
    virtual ~Client();

  public:
    void	update();
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

  private:
    bool			_used;
    RequestQueue		_input;
    RequestQueue		_output;

  private:
    requestCode::SessionID	_id;
	struct sockaddr_in		_addr;
  };
}

#endif /* GAMECLIENT_H_ */
