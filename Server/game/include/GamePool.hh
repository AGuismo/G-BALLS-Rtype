#ifndef GAMEPOOL_H_
# define GAMEPOOL_H_

# include	<list>
# include	"ThreadEvent.hpp"
# include	"Clock.h"
# include	"Threads.hpp"

class		ICallbacks;
class		AGameRequest;

namespace	game
{

  class	Manager;
  class	Game;

  class GamePool
  {
    static const size_t		MAX_GAMES = 5;
    static size_t		incrementalID;

    typedef Thread::EventQueue<ICallbacks *>		input_event;
    typedef Thread::EventQueue<ICallbacks *>		output_event;
    typedef std::list<Game *>				game_list;

  public:
    GamePool(Manager *parent, output_event &output);
    virtual ~GamePool();

  public:
    const size_t		poolID;

  public:
    void	run();
    void	join();
    void	stop();

  public:
    input_event	&input();
    void	updateGameClocks(const Clock::clock_time &time);
    void	updateGame();
    Manager	*parent() const;

  public:
    void	executeCallback();
    void	dispatchMessages(AGameRequest *req);

    void	newGame(Game *game);
    void	cancelGame(const Game *game);
    void	endGame(const Game *game);

  public:
    bool	full() const;

  private:
    GamePool(GamePool const&);
    GamePool& operator=(GamePool const&);

  private:
    static void		routine(GamePool *);

  private:
    Manager				*_parent;
    bool				_active;
    Threads<void (*)(GamePool *)>	_th;
    Clock				_clock;
    game_list				_games;
    input_event				_input;
    output_event			&_output;
  }; // !GamePool

} // !game

#endif /* GAMEPOOL_H_ */
