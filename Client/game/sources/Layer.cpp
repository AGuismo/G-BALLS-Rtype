#include		"Layer.hh"
#include		<iostream>

void						Layer::draw(void)
{
	if (_lEnabled)
		_gameWindow->draw(_lSprite);
}

void						Layer::update(void)
{
	if ((_lTime != NULL && !_lTime->isEnded()) || (_lEnabled && _lTime == NULL))
	{
		if (_lEnabled)
		{
			_lCurPos.x -= _lIncrement.x;
			_lCurPos.y -= _lIncrement.y;
			_lCurPos.x = (_lCurPos.x == _lLimPos.x) ? _lResetPos.x : _lCurPos.x;
			_lCurPos.y = (_lCurPos.y == _lLimPos.y) ? _lResetPos.y : _lCurPos.y;
			_lSprite.setPosition(_lCurPos.x, _lCurPos.y);
		}
	}
	_lEnabled = ((_lTime && _lTime->isEnded()) || !_lEnabled) ? false : true;
}

void						Layer::enable(void)
{
	if (_lTime)
		_lTime->restart();
	_lEnabled = true;
}

void						Layer::disable(void)
{
	_lEnabled = false;
}

Layer::Layer(int id, const sf::Texture &lText, const sf::Vector2f &lInit,
	     const sf::Vector2f &lReset, const sf::Vector2f &lLim,
	     const sf::Vector2f &lInc, Timer *lT, sf::RenderWindow *gWindow, bool lEn) :
  _lCurPos(lInit), _lInitPos(lReset), _lResetPos(lReset), _lLimPos(lLim), _lIncrement(lInc)
{
	_id = id;
	_lTexture = lText;
	_lResetPos = lReset;
	_lIncrement = lInc;
	_lLimPos = lLim;
	_lCurPos = lInit;
	_lInitPos = lReset;
	_lTime = lT;
	_gameWindow = gWindow;
	_lEnabled = lEn;
	_lSprite.setTexture(_lTexture);
}
