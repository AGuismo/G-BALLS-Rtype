#include		"Bang.h"
#include		"game.h"

void						Bang::draw(void)
{
	if (!_timerMvt->isEnded())
	{
		_image.setTextureRect(_bangAnimation->getFrame());
		_gameWindow->draw(_image);
	}
	else
		_alive = false;
}

void			Bang::update(LookDirection lDir, int updtatedPos)
{
	(void)lDir;
	(void)updtatedPos;
}


Bang::Bang(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_id = id;
	_texture = text;
	_cCurPos = pos;
	_cNextPos = pos;
	_alive = true;
	_gameWindow = gameWindow;
	_image.setTexture(*text);
	_image.setTextureRect(sf::IntRect(0, 0, 650, 100));
	switch (type)
	{
	case NORMAL_BANG:
		_mvtTime = 0.72f;
		_timerMvt = new Timer(new sf::Time(sf::seconds(_mvtTime)));
		_bangAnimation = new Animation(0.12f);
		_bangAnimation->addFrame(sf::IntRect(258, 0, 65, 70));
		_bangAnimation->addFrame(sf::IntRect(323, 0, 65, 70));
		_bangAnimation->addFrame(sf::IntRect(388, 0, 65, 70));
		_bangAnimation->addFrame(sf::IntRect(453, 0, 65, 70));
		_bangAnimation->addFrame(sf::IntRect(518, 0, 65, 70));
		_bangAnimation->addFrame(sf::IntRect(583, 0, 65, 70));
		_image.setPosition((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos) - 20);
		break;
	case BIG_BANG:
		_mvtTime = 0.8f;
		_timerMvt = new Timer(new sf::Time(sf::seconds(_mvtTime)));
		_bangAnimation = new Animation(0.1f);
		_bangAnimation->addFrame(sf::IntRect(270, 76, 110, 110));
		_bangAnimation->addFrame(sf::IntRect(400, 76, 110, 110));
		_bangAnimation->addFrame(sf::IntRect(530, 76, 110, 110));
		_bangAnimation->addFrame(sf::IntRect(0, 198, 130, 134));
		_bangAnimation->addFrame(sf::IntRect(130, 198, 130, 134));
		_bangAnimation->addFrame(sf::IntRect(260, 198, 130, 134));
		_bangAnimation->addFrame(sf::IntRect(390, 198, 130, 134));
		_bangAnimation->addFrame(sf::IntRect(520, 198, 130, 134));
		_image.setPosition((float)Game::POSX(_cCurPos) - 15, (float)Game::POSY(_cCurPos) - 40);
		break;
	default:
		break;
	}
}
