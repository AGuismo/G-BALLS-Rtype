#include <iostream>
#include <cstdlib>
#include "base.hh"

#include	"StateManager.hh"
#include	"IState.hh"
// #include	"GameState.hh"
// #include	"MenuState.hh"

namespace input
{
    class Manager
    {
	public:
	int i;
	Manager() : i(0) {}
	virtual ~Manager() {}
    };
}

#define output std::cout << __PRETTY_FUNCTION__ << " → " << ushort(++i) << std::endl;

#define state(T) T : public state::IState	\
    {						\
	unsigned char	i;			\
	static const int flag = 1;		\
	IState*	clone() const			\
	{					\
	    IState*	clone = new T;		\
	    (*clone) = (*this);			\
	    return clone;			\
	}					\
						\
	void	draw(void)	 { output; }	\
	void	update(void)	 { output; }	\
    };

class state(Menu);
class state(SubMenu);
class state(Game);
class state(GameMenu);

int	main()
{
    input::Manager	inputManager;
    state::Manager	stateManager(inputManager);

    state::IState *	menu		= new Menu();
    state::IState *	subMenu		= new SubMenu();
    state::IState *	game		= new Game();
    state::IState *	gameMenu	= new GameMenu();

    stateManager.add("Menu",         menu);
    stateManager.add("SubMenu",   subMenu);
    stateManager.add("Game",         game);
    stateManager.add("GameMenu", gameMenu);

    stateManager.push("Menu");
    stateManager.update();

    stateManager.switchTo("Game");
    stateManager.update();

    stateManager.pop();
    stateManager.update();

    stateManager.switchTo("Game");
    stateManager.update();

    stateManager.switchTo("GameMenu");
    stateManager.update();

    stateManager.switchTo("SubMenu");
    stateManager.update();

    std::cout << (stateManager.find("SubMenu") == stateManager.top()) << std::endl;

    stateManager.at("SubMenu");
    return EXIT_SUCCESS;
}
