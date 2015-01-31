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
  Client(requestCode::SessionID id, State st = NONE);
  ~Client();

public:
  static requestCode::SessionID		generateUniqueID();

  const requestCode::SessionID		&id() const;
  void					id(requestCode::SessionID id);
  State					state() const;
  void					state(State st);

private:
  Client(Client const&);
  Client& operator=(Client const&);

private:
  requestCode::SessionID	_id;
  State				_state;
};

#endif /* CLIENT_H_ */
