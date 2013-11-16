#include					"AObject.h"

void						AObject::findAnimation(void) //faire l'invers batard
{
	if (_cCurPos == _cNextPos)
		return;

	if (_vCurPos.x < _vNextPos.x) // déplacement droite
	{
		std::cout << "right" << std::endl;
		_action = Right;
	}
	else if (_vCurPos.x > _vNextPos.x) // déplacement gauche
	{
		std::cout << "left" << std::endl;
		_action = Left;
	}
	else if (_vCurPos.y < _vNextPos.y) // down
	{
		std::cout << "down" << std::endl;
		_action = Down;
	}
	else if (_vCurPos.y > _vNextPos.y) // up
	{
		std::cout << "up" << std::endl;
		_action = Up;
	}

/*	switch (action)
	{
	case Left:
		updatedPos = ((*it)->getCaseCurPos() % Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() - 1;
		(*it)->update(Left, Unset, updatedPos);
		break;
	case Right:
		updatedPos = (((*it)->getCaseCurPos() + 1) % Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() + 1;
		(*it)->update(Right, Unset, updatedPos);
		break;
	case Up:
		updatedPos = ((*it)->getCaseCurPos() / Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() - Game::SIZE_GAME_BOARD;
		(*it)->update(Up, Unset, updatedPos);
		break;
	case Down:
		updatedPos = ((*it)->getCaseCurPos() + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() + Game::SIZE_GAME_BOARD;
		(*it)->update(Down, Unset, updatedPos);
		break;
	case Fire:
		updatedPos = (*it)->getCaseCurPos() + 6;
		(*it)->update(Right, Unset, updatedPos);
		break;
	default:
		(*it)->update(Nothing, Unset, updatedPos);
		break;
	}*/
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
