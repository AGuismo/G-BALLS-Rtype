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
	if (!_bgTexture1.loadFromFile("./Images/r-typebackground1-2.png"))
		return false;
	_bgImg1.setTexture(_bgTexture1);
	if (!_bgTexture2.loadFromFile("./Images/r-typebackground1-1.png"))
		return false;
	_bgImg2.setTexture(_bgTexture2);

	return true;
}


void							Game::run(void)
{
	float						bg1 = 0;
	float						bg2 = 1280;

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
				break;
			case sf::Event::KeyReleased:
				switch (_event->key.code)
				{
				case sf::Keyboard::Up:
					updateObj(42, Nothing);
					std::cout << "UP RELEASED " << std::endl;
					break;
				case sf::Keyboard::Down:
					updateObj(42, Nothing);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		_gameWindow->clear();

		update();
		if (bg1 == -1280)
			bg1 = 1280;
		if (bg2 == -1280)
			bg2 = 1280;

		_bgImg1.setPosition(bg1, 0);
		_bgImg2.setPosition(bg2, 0);
		_gameWindow->draw(_bgImg1);
		_gameWindow->draw(_bgImg2);
		draw();
//		sf::sleep(sf::seconds(1));

		_gameWindow->display();
		bg1 -= 1;
		bg2 -= 1;
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
	_event = event;
	_idPlayer = 42;
}
