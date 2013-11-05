#include	"Player.h"
#include	"Game.h"


void			Player::draw(void)
{
	_gameWindow->draw(_image);
}

void			Player::update(int newPos, Action act)
{
	_pos = newPos;
	_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
}

Player::Player(ObjType obj, sf::Texture *text, int pos, sf::RenderWindow *gameWindow)
{
	_type = obj;
	_texture = text;
	_pos = pos;
	_gameWindow = gameWindow;
}