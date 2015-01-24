#pragma once

#include	<vector>
#include	<list>
#include	"types.hh"
#include	"GameClient.hh"
#include	"Clock.hh"

//class	Event;
class	MainReferee;

namespace	net
{
  class		UdpServer;
}

namespace game
{
  class	GamePool;

  class Game
  {
  public:
    enum Status
      {
	NONE = 0,
	WAITING_PLAYER = 1,
	IN_GAME = 2,
	FINISHED = 4,
	CANCELED = 8
      };

    typedef std::list<Client *>	client_list;

  public:
    Game(const client_list &players);
    ~Game();

    void			timer(struct timeval t);
    struct timeval		&timer();
    const struct timeval	&timer() const;
    client_list			&clients();
    const client_list		&clients() const;
    bool			success() const;
    Status			status() const;
    void			parent(GamePool *parent);
    GamePool			*gamePool() const;
    void			gameID(requestCode::SessionID gameID);
    requestCode::SessionID	gameID() const;
    game::Stamp			getStamp() const;

    template <typename Req>
    void		pushRequestToEveryone(const Req &req)
    {
      _toSend.requestPush(new Req(req));
    }

    bool		update();
    void		prepareGame();

  private:
    void		sendUpdates(const std::vector<unsigned short> &toDelete);
    void		send(const ARequest &req);

    void		cancelGame();
    void		endGame();
    void		updateGame();
    void		waitingForPlayers();

  private:
    requestCode::SessionID	_gameID;
    GamePool		*_parent;
    Clock		_clock;
    struct timeval	_timer;
    int			_attempsClientConfirmation;
    Status		_status;
    client_list		_clients;
    MainReferee		*_referee;
    RequestQueue	_toSend;

    friend class Referee;
  };
}
