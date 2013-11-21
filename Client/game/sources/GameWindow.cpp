#if defined(WIN32) && defined(SFML_STATIC)
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#endif // SFML_STATIC
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


GameWindow::GameWindow(sf::RenderWindow &window, network::Manager &network) :
  AScreen(window, network, AScreen::INGAME), _game(&_window, &_event)
{
}
