#include	<map>
#include	<sstream>
#include	<string>
#include	"Env.hh"

namespace rtype
{
  const std::string Env::DB_PATH = "./misc/rtype.db";

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
	game.minWall = MINWALL;
	game.maxWall = MAXWALL;
	game.popRangeMinWall = POPRANGEMINWALL;
	game.popRangeMaxWall = POPRANGEMAXWALL;
	game.chanceToBreakableMin = CHANCETOBREAKABLEMIN;
	game.chanceToBreakableMax = CHANCETOBREAKABLEMAX;
  }

  template <typename T>
  void	Env::Set(T &obj, const std::string &value)
  {
	  std::stringstream	ss(value);

	  ss >> obj;
  }

  bool	Env::loadFile(const std::string &file)
  {
    (void)file;
	  /*map = getMap(file) -> arnaud_k*/
	  // std::map<std::string, std::map<std::string, std::string >> map;
    // if (map.find("network") != map.end() && map["network"].find("TCP_SERVER_PORT") != map["network"].end())
    // 		  Set(network.TCPServerPort, map["network"]["TCP_SERVER_PORT"]);
    // 	  if (map.find("network") != map.end() && map["network"].find("UDP_SERVER_PORT") != map["network"].end())
    // 		  Set(network.UDPServerPort, map["network"]["UDP_SERVER_PORT"]);
    // 	  if (map.find("network") != map.end() && map["network"].find("MAX_PENDING_CLIENT") != map["network"].end())
    // 		  Set(network.maxPendingClients, map["network"]["MAX_PENDING_CLIENT"]);
    // 	  if (map.find("network") != map.end() && map["network"].find("MAX_UDP_PACKET_LENGTH") != map["network"].end())
    // 		  Set(network.maxUDPpacketLength, map["network"]["MAX_UDP_PACKET_LENGTH"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("MAX_SIMULTANEOUS_GAME") != map["game"].end())
    // 		  Set(game.maxSimultaneousGames, map["game"]["MAX_SIMULTANEOUS_GAME"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("BOSS_DELAY") != map["game"].end())
    // 		  Set(game.bossDelay, map["game"]["BOSS_DELAY"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("GAME_DELAY") != map["game"].end())
    // 		  Set(game.gameDelay, map["game"]["GAME_DELAY"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("UPDATE_TO_LIVE") != map["game"].end())
    // 		  Set(game.updateToLive, map["game"]["UPDATE_TO_LIVE"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("MIN_IA") != map["game"].end())
    // 		  Set(game.minIA, map["game"]["MIN_IA"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("MAX_IA") != map["game"].end())
    // 		  Set(game.maxIA, map["game"]["MAX_IA"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("POP_IA_RANGE") != map["game"].end())
    // 		  Set(game.popIArange, map["game"]["POP_IA_RANGE"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("POP_IA_MAX") != map["game"].end())
    // 		  Set(game.popIAmax, map["game"]["POP_IA_MAX"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("MAPSIZE") != map["game"].end())
    // 		  Set(game.mapSize, map["game"]["MAPSIZE"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("MAXBOSS") != map["game"].end())
    // 		  Set(game.maxBoss, map["game"]["MAXBOSS"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("MINWALL") != map["game"].end())
    // 		  Set(game.minWall, map["game"]["MINWALL"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("MAXWALL") != map["game"].end())
    // 		  Set(game.maxWall, map["game"]["MAXWALL"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("POPRANGEMINWALL") != map["game"].end())
    // 		  Set(game.popRangeMinWall, map["game"]["POPRANGEMINWALL"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("POPRANGEMAXWALL") != map["game"].end())
    // 		  Set(game.popRangeMaxWall, map["game"]["POPRANGEMAXWALL"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("CHANCETOBREAKABLEMIN") != map["game"].end())
    // 		  Set(game.chanceToBreakableMin, map["game"]["CHANCETOBREAKABLEMIN"]);
    // 	  if (map.find("game") != map.end() && map["game"].find("CHANCETOBREAKABLEMAX") != map["game"].end())
    // 		  Set(game.chanceToBreakableMax, map["game"]["CHANCETOBREAKABLEMAX"]);
    // 	  if (map.find("database") != map.end() && map["database"].find("DB_PATH") != map["game"].end())
    // 		  Set(database.DatabasePath, map["database"]["DB_PATH"]);
    return (true);
  }

  Env::Env()
  {
    database.DatabasePath = DB_PATH;
    initNetwork();
    initGames();
  }

  Env::~Env()
  {

  }
}
