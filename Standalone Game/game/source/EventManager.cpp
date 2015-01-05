#include	"EventManager.hh"

EventManager::EventManager(sf::Event &e, const sf::Time &refreshTime):
_refreshTime(refreshTime), _e(e)
{

}

EventManager::~EventManager()
{
}

void	EventManager::registerKey(sf::Keyboard::Key key, EventManager::ICallback<sf::Keyboard::Key> *callback, bool repeat)
{
	_keyCallbacks[key] = State<sf::Keyboard::Key>(callback, repeat);
}

bool	EventManager::unregisterKey(sf::Keyboard::Key key)
{
	keyboard_callback_map::iterator	it = _keyCallbacks.find(key);

	if (it == _keyCallbacks.end())
		return (false);
	_keyCallbacks.erase(it);
	return (true);
}

void	EventManager::update()
{
	for (keyboard_callback_map::iterator it = _keyCallbacks.begin(); it != _keyCallbacks.end(); ++it)
	{
		if (sf::Keyboard::isKeyPressed(it->first))
		{
			if (it->second.repeated)
			{
				if (it->second.active && it->second.lastPress.getElapsedTime() > _refreshTime ||
					!it->second.active)
				{
					(*it->second.event)(it->first);
					it->second.lastPress.restart();
					it->second.active = true;
				}
			}
		}
		else if (it->second.repeated)
			it->second.active = false;
	}
}