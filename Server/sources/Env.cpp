#include	"Env.hh"

namespace rtype
{
  const char	*Env::DB_PATH = "./misc/rtype.db";

  Env		&Env::getInstance()
  {
    static Env	singleton;

    return (singleton);
  }

  void	Env::initNetwork()
  {
    network.TCPServerPort = TCP_SERVER_PORT;
    network.UDPServerPort = UDP_SERVER_PORT;
    network.maxPendingClients = MAX_PENDING_CLIENTS;
    network.maxUDPpacketLength = MAX_UDP_PACKET_LENGTH;
  }

  void	Env::initGames()
  {
    game.maxSimultaneousGames = MAX_SIMULTANEOUS_GAMES;
    game.bossDelay = BOSS_DELAY;
	game.mapSize = MAPSIZE;
	game.maxBoss = MAXBOSS;
	game.maxIA = MAX_IA;
	game.minIA = MIN_IA;
	game.popIAmax = POP_IA_MAX;
	game.popIArange = POP_IA_RANGE;
	game.updateToLive = UPDATE_TO_LIVE;
	game.gameDelay = GAME_DELAY;
  }

  bool	Env::loadFile(const std::string &file)
  {
    (void)file;
    throw "Under Dev";
    return (false);
  }

  Env::Env()
  {
    DatabasePath = DB_PATH;
    initNetwork();
    initGames();
  }

  Env::~Env()
  {

  }
}
