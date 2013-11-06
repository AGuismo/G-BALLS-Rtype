#include		"AObject.h"
#include		"game.h"
#include		<algorithm>


bool							Game::load(void)
{
	if(!_spriteManager.addTexture(PLAYER1, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_spriteManager.addTexture(PLAYER2, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_spriteManager.addTexture(PLAYER3, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_spriteManager.addTexture(PLAYER4, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_spriteManager.addTexture(SBYDOS1, std::string("./Images/r-typesheet5.png")))
		return false;
	_bgTexture.loadFromFile("./Images/r-typebackground1-2.png");
	_bgImg.setTexture(_bgTexture);
	return true;
}


void							Game::run(void)
{
	_gameWindow->setFramerateLimit(25);

	addObj(PLAYER1, 42, 100);
	addObj(PLAYER2, 20, 40);
	addObj(PLAYER3, 77, 10);
	addObj(PLAYER4, 48, 200);
	addObj(SBYDOS1, 455, 140);


	while (_gameWindow->isOpen())
	{
		while (_gameWindow->pollEvent(*_event))
		{
			switch (_event->type)
			{
			case sf::Event::Closed:
				_gameWindow->close();
				break;
			case sf::Event::KeyPressed:
				switch (_event->key.code)
				{
				case sf::Keyboard::Left:
					updateObj(42, Left);
					break;
				case sf::Keyboard::Right:
					updateObj(42, Right);
					break;
				case sf::Keyboard::Up:
					updateObj(42, Up);
					break;
				case sf::Keyboard::Down:
					updateObj(42, Down);
					break;
				case sf::Keyboard::Escape:
					return;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		_gameWindow->clear();

		update();
		_gameWindow->draw(_bgImg);
		draw();
//		sf::sleep(sf::seconds(1));
		_gameWindow->display();
	}
}

void							Game::draw(void)
{
	for (obj_type::iterator it = _objects.begin(); it != _objects.end(); ++it)
		(*it)->draw();
}

void							Game::update(void)
{
	// too soon
}

bool							Game::updateObj(int id, Action action)
{
	obj_type::iterator it = std::find_if(_objects.begin(), _objects.end(), AObject::predicate(id));
	if (it != _objects.end())
	{
		(*it)->update(action);
		return true;
	}
	return false;
}

bool							Game::addObj(ObjType type, int id, int pos)
{
	AObject						*obj;

	if ((obj = _factory.createObject(type, id, pos, East)) != NULL)
	{
		_objects.push_back(obj);
		return true;
	}
	return false;
}

Game::Game(sf::RenderWindow *gameWindow, sf::Event *event) : _factory(gameWindow, &_spriteManager)
{
	_gameWindow = gameWindow;
	std::cout << _gameWindow << std::endl;
	_event = event;
	_idPlayer = 42;
}
