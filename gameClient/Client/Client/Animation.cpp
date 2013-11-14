#include		"Animation.h"


void								Animation::addFrame(sf::IntRect rect)
{

}

const sf::IntRect&					Animation::getFrame(void) const
{
	if (_aTimer->isEnded())
	{
/*		if (_curFrame + 1 < _frames.size())
			_curFrame = 0;
		++_curFrame;*/
	}
	return _frames[_curFrame];
}
