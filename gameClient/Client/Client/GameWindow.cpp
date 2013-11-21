#include		"gameWindow.h"


bool					GameWindow::load(void)
{
	if (!_game.load())
		return false;
	return true;
}

int						GameWindow::run(void)
{
	_game.run();
	return 1;
}


GameWindow::GameWindow(const std::string &name, int width, int height) : _game(&this->_gameWindow, &_event)
{
	_gameWindow.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
	std::cout << &_gameWindow << std::endl;
}