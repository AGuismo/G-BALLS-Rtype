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
      unsigned short int		bossDelay;
      unsigned long long		gameDelay;
	  int						updateToLive;
	}					game;
    static const unsigned short int	MAX_SIMULTANEOUS_GAMES =	20;
    static const unsigned short int	BOSS_DELAY	       =	90;
    static const unsigned long long	gameDelay	       =	250000;
	static const int				updateToLive = 8;

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
