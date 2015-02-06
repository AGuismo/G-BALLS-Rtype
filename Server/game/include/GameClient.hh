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
    typedef void(Client::*request_fn)(const ARequest &, MainReferee &);
    typedef std::map<rtype::protocol::CodeID, request_fn>	request_callback_map_type;
  public:
    Client(rtype::protocol::SessionID clientID);
    Client(rtype::protocol::SessionID clientID, struct sockaddr_in addr);
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
    rtype::protocol::SessionID	clientID() const;
    void			clientID(const rtype::protocol::SessionID clientID);
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
    void			request_alive(const ARequest &req, MainReferee &referee);
    void			request_leave(const ARequest &req, MainReferee &referee);
    void			request_elem(const ARequest &req, MainReferee &referee);

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
    rtype::protocol::SessionID	_id;
  };
}

#endif /* GAMECLIENT_H_ */
