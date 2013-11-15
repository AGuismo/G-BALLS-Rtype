#include		"Animation.h"


void								Animation::addFrame(sf::IntRect rect)
{
	_frames.push_back(rect);
}

const sf::IntRect&					Animation::getFrame(void)
{
	if (_aTimer->isEnded())
	{
		if (_curFrame + 1 > _frames.size())
			_curFrame = 0;
		else
			++_curFrame;
		_aTimer->restart();
	}
	return _frames[_curFrame];
}
