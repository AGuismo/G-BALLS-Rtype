#include		"Animation.hh"

const std::string	Animation::ACT_DEFAULT = "Default";
const std::string	Animation::ACT_UP = "Up";
const std::string	Animation::ACT_DOWN = "Down";

const float			Animation::ANIM_FRAME_DURATION = 0.25f;

void								Animation::addFrame(const std::string &action, sf::Texture *textureFrame)
{
	_animations[action].push_back(textureFrame);
}

const sf::Texture&					Animation::getFrame(const std::string &action)
{
	if (_aTimer.isEnded())
	{
		if (action != _curAction)
		{
			_curAction = action;
			_curFrame = 0;
		}
		if ((_curFrame + 1) == _animations[_curAction].size())
			_curFrame = 0;
		else
			++_curFrame;
		_aTimer.restart();
	}
	return *_animations[_curAction][_curFrame];
}

Animation::Animation() :
_aTimer(sf::seconds(ANIM_FRAME_DURATION)), _curFrame(0), _curAction(ACT_DEFAULT)
{
}

Animation::Animation(const Entity::type &type, float frameDuration) :
_type(type), _aTimer(sf::seconds(frameDuration)), _curFrame(0), _curAction(ACT_DEFAULT)
{
}

Animation::Animation(const Animation &src) :
_type(src._type), _animations(src._animations), _aTimer(src._aTimer), _curFrame(src._curFrame), _curAction(src._curAction)
{

}

Animation				&Animation::operator=(const Animation &src)
{
  if (this != &src)
    {
		_type = src._type;
		_animations = src._animations;
		_aTimer = src._aTimer;
		_curFrame = src._curFrame;
		_curAction = src._curAction;
  }
  return (*this);
}
