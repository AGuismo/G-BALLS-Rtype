#if defined(WIN32) && defined(SFML_STATIC)
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#endif // SFML_STATIC
#include		"gameWindow.h"
#include		"AScreen.hh"

bool					GameWindow::load(void)
{
  if (!_game.load())
    throw AScreen::Exception("Game Window failed to init");
  return true;
}

void					GameWindow::clearWindow(void)
{

}

int						GameWindow::run(void)
{
	_game.run();
	return 1;
}


GameWindow::GameWindow(sf::RenderWindow &window, network::Manager &network) :
  AScreen(window, network, AScreen::INGAME), _game(&window, &_event)
{
}
