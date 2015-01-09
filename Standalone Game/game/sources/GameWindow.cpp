#if defined(WIN32) && defined(SFML_STATIC)
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#endif // SFML_STATIC
#include		"GameWindow.hh"
#include		"AScreen.hh"
#include		"Game.hh"

bool					GameWindow::load(void)
{
  if (!_game->load())
    throw AScreen::Exception("Game Window failed to init");
  return true;
}

void					GameWindow::clearWindow()
{
}

int						GameWindow::run(void)
{
	_game->run();
	return AScreen::SCR_MENU;
}


GameWindow::GameWindow(sf::RenderWindow &window) :
  AScreen(window, AScreen::INGAME), _game(new Game(&window, &_event))
{
}
