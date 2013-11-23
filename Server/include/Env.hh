#ifndef ENV_H_
# define ENV_H_

#include	<string>

namespace rtype
{
  class Env
  {
  public:
    struct
    {
      unsigned short int		TCPServerPort;
      unsigned short int		UDPServerPort;
      unsigned int			maxPendingClients;
      unsigned int			maxUDPpacketLength;
    }					network;
    static const unsigned short int	TCP_SERVER_PORT     =	44201;
    static const unsigned short int	UDP_SERVER_PORT     =	44202;
    static const unsigned int		MAX_PENDING_CLIENTS =	10;
    static const unsigned int		MAX_UDP_PACKET_LENGTH =	4096;

  public:
    struct
    {
      unsigned short int		maxSimultaneousGames;
      unsigned long long		bossDelay;
      unsigned long long		gameDelay;
      unsigned short int		updateToLive;
      unsigned short int		minIA;
      unsigned short int		maxIA;
      unsigned short int		popIArange;
      unsigned short int		popIAmax;
	  unsigned short int		mapSize;
	  unsigned short int		maxBoss;
    }				game;
    static const unsigned short int	MAX_SIMULTANEOUS_GAMES	=	20;
    static const unsigned long long	BOSS_DELAY				=	90000000;
    static const unsigned long long	GAME_DELAY				=	250000;
    static const unsigned short int	UPDATE_TO_LIVE			=	8;
    static const unsigned short int	MIN_IA					=	4;
    static const unsigned short int	MAX_IA					=	20;
    static const unsigned short int	POP_IA_RANGE			=	2;
    static const unsigned short int	POP_IA_MAX				=	5;
    static const unsigned short int	MAPSIZE					=	16;
      static const unsigned short int MAXBOSS					=	2;
  public:
    const char				*DatabasePath;

    static const char			*DB_PATH;
    static const unsigned int		PASS_SIZE = 32;

  public:
    static Env	&getInstance();

  private:
    void	initNetwork();
    void	initGames();

  public:
    bool	loadFile(const std::string &);

  private:
    Env();
    virtual ~Env();
    Env	&operator=(const Env &);
    Env(const Env &);
  };
}

#endif /* ENV_H_ */
