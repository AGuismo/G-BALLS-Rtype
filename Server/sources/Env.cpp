#include	"Env.hh"

namespace rtype
{
  Env		&Env::getInstance()
  {
    static Env	*singleton = 0;

    if (singleton == 0)
      singleton = new Env();
    return (*singleton);
  }

  void	Env::initNetwork()
  {
    network.TCPServerPort = TCP_SERVER_PORT;
    network.UDPServerPort = UDP_SERVER_PORT;
    network.maxPendingClients = MAX_PENDING_CLIENTS;
  }

  void	Env::initGames()
  {
    game.maxSimultaneousGames = MAX_SIMULTANEOUS_GAMES;
    game.bossDelay = BOSS_DELAY;
  }

  bool	Env::loadFile(const std::string &file)
  {
    (void)file;
    throw "Under Dev";
    return (false);
  }

  Env::Env()
  {
    initNetwork();
    initGames();
  }

  Env::~Env()
  {

  }
}
