#ifndef CLIENT_H_
# define CLIENT_H_

# include	<queue>
# include	"RequestQueue.hh"

class ARequest;

class Client
{
public:
  enum State
    {
      NONE, // Never happens
      MENU, // Client in menu
      GAME, // Client in Game
      DISCONNECTED, // Client in Game - Menu disconnected
      DELETED // Client in Menu - disconnected
    };

public:
  Client();
  Client(rtype::protocol::SessionID id, State st = NONE);
  ~Client();

public:
  static rtype::protocol::SessionID		generateUniqueID();

  const rtype::protocol::SessionID		&id() const;
  void					id(rtype::protocol::SessionID id);
  State					state() const;
  void					state(State st);

private:
  Client(Client const&);
  Client& operator=(Client const&);

private:
  rtype::protocol::SessionID	_id;
  State				_state;
};

#endif /* CLIENT_H_ */
