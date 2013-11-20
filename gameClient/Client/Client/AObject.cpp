#include					"AObject.h"

void						AObject::findAnimation(void) //faire l'invers batard
{
	if (_cCurPos == _cNextPos)
		return;

	if (_vCurPos.x < _vNextPos.x) // déplacement droite
	{
		_action = Right;
	}
	else if (_vCurPos.x > _vNextPos.x) // déplacement gauche
	{
		_action = Left;
	}
	else if (_vCurPos.y < _vNextPos.y) // down
	{
		_action = Down;
	}
	else if (_vCurPos.y > _vNextPos.y) // up
	{
		_action = Up;
	}
}


const sf::Vector2f			&AObject::getVectorNextPos(void)
{
	return (_vNextPos);
}

const sf::Vector2f			&AObject::getVectorCurPos(void)
{
	return (_vNextPos);
}

int							AObject::getCaseNextPos(void)
{
	return (_cNextPos);
}

int							AObject::getCaseCurPos(void)
{
	return (_cNextPos);
}
