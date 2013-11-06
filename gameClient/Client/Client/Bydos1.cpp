#include		"Bydos1.h"
#include		"game.h"

void			Bydos1::draw(void)
{
	_gameWindow->draw(_image);
}

void			Bydos1::update(Action act)
{
//	_pos = newPos;
	_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
}

Bydos1::Bydos1(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_texture = text;
	_pos = pos;
	_id = id;
	_ld = ld;
	_gameWindow = gameWindow;
	_image.setTexture(*text);
	_image.setTextureRect(sf::IntRect(5, 2, 48, 72));
	_image.setPosition((float)Game::POSX(_pos) + 10, (float)Game::POSY(_pos) - 20);
}