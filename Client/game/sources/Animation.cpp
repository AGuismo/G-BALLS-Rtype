#include		"Animation.h"


void								Animation::addFrame(sf::IntRect rect)
{
	_frames.push_back(rect);
}

const sf::IntRect&					Animation::getFrame(void)
{
	if (_aTimer.isEnded())
	{
		if (_curFrame + 2 > _frames.size())
			_curFrame = 0;
		else
			++_curFrame;
		_aTimer.restart();
	}
	return _frames[_curFrame];
}

Animation::Animation() :
  _curFrame(0)
{
}
Animation::Animation(float aTime) :
  _aTimer(sf::seconds(aTime)), _curFrame(0)
{
}

Animation::Animation(const Animation &src) :
  _frames(src._frames), _aTimer(src._aTimer)
{

}

Animation				&Animation::operator=(const Animation &src)
{
  if (this != &src)
    {
      _frames = src._frames;
      _aTimer = src._aTimer;
    }
  return (*this);
}
