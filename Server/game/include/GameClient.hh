#ifndef GAMECLIENT_H_
# define GAMECLIENT_H_

# if defined(linux)
#  include	<netinet/in.h>
# elif defined(WIN32)
#  include	<winsock2.h>
# else
#  error "Undefined Operating system."
#endif

# include	<queue>
# include	<map>
# include	<list>
//# include	"ARequest.hh"
# include	"RequestQueue.hh"
# include	"RequestCode.hh"

class		ARequest;
class		Player;
class		MainReferee;

namespace	game
{
  class		GamePool;

  class Client
  {
    typedef void(Client::*request_fn)(const ARequest &);
    typedef std::map<requestCode::CodeID, request_fn>	request_callback_map_type;
  public:
    Client(requestCode::SessionID clientID);
    Client(requestCode::SessionID clientID, struct sockaddr_in addr);
    virtual ~Client();

  public:
    void	update(MainReferee &referee);
    void	finalize();
    void	waitForJoin();

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
    requestCode::SessionID	clientID() const;
    void			clientID(const requestCode::SessionID clientID);
    void			alive(const bool &state);
    bool			alive() const ;
    void			hasLeft(const bool &state);

  public:
    void			gamePool(GamePool *gamePool);
    GamePool			*gamePool() const;

    struct sockaddr_in		getAddr() const { return _addr; };
    void			setAddr(struct sockaddr_in addr) { _addr = addr; };
    bool			hasLeft() const { return _hasLeft; };
    bool			hasJoin() const { return _hasJoin; };
    void			hasJoin(bool b) { _hasJoin = b; };

  private:
    void			request_alive(const ARequest &req);
    void			request_leave(const ARequest &req);
    void			request_elem(const ARequest &req);

  private:
    bool			_alive;
    int				_updateToLive;

  private:
    bool			_hasLeft;
    bool			_hasJoin;
    RequestQueue		_input;
    RequestQueue		_output;
    GamePool			*_associatedPool;
    request_callback_map_type	_requestCallback;

  private:
    struct sockaddr_in		_addr;
    requestCode::SessionID	_id;
  };
}

#endif /* GAMECLIENT_H_ */
