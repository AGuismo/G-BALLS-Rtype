#include		<SFML/Audio.hpp>
#include		"AObject.h"
#include		"game.h"
#include		"Layer.h"
#include		<algorithm>
#include		"Timer.h" // A VIRER (pas sur)

const float Game::VLAG = 0.4f;


bool							Game::load(void)
{

	if(!_textureManager.addTexture(PLAYER1, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(PLAYER2, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(PLAYER3, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(PLAYER4, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(SBYDOS1, std::string("./Images/r-typesheet5.png")))
		return false;
	if (!_textureManager.addTexture(LAYER1, std::string("./Images/Aurora1.png")))
		return false;
	if (!_textureManager.addTexture(LAYER2, std::string("./Images/Aurora2.png")))
		return false;
	if (!_textureManager.addTexture(LAYER3, std::string("./Images/Comet1.png")))
		return false;


	if (!_layerManager.addLayer(LAYER1, LAYER_1, new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(2560.0f, 0.0f), new sf::Vector2f(-2560.0f, 0.0f), new sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER2, LAYER_2, new sf::Vector2f(2560.0f, 0.0f), new sf::Vector2f(2560.0f, 0.0f), new sf::Vector2f(-2560.0f, 0.0f), new sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(800.0f, 1000.0f), new sf::Vector2f(-4.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(-50.0f, 100.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(800.0f, 1000.0f), new sf::Vector2f(-4.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(300.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(800.0f, 1000.0f), new sf::Vector2f(-8.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(42.0f, -890.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(800.0f, 700.0f), new sf::Vector2f(-3.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(200.0f, 0.0f), new sf::Vector2f(200.0f, 0.0f), new sf::Vector2f(800.0f, 1400.0f), new sf::Vector2f(-5.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(800.0f, 900.0f), new sf::Vector2f(-8.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(42.0f, -890.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(800.0f, 700.0f), new sf::Vector2f(-3.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, new sf::Vector2f(200.0f, 0.0f), new sf::Vector2f(200.0f, 0.0f), new sf::Vector2f(800.0f, 1400.0f), new sf::Vector2f(-5.0f, -5.0f), NULL, true))
		return false;

	if (!_audioManager.add(GAME_MUSIC, AMUSIC, true, std::string("./Sounds/Lepi.ogg")))
		return false;
	if (!_audioManager.add(PLAYER_LASER, ASOUND, false, std::string("./Sounds/PlayerLaser.wav")))
		return false;
	if (!_audioManager.add(PLAYER_CHARGED, ASOUND, true, std::string("./Sounds/PlayerCharged.wav")))
		return false;
	if (!_audioManager.add(PLAYER_RELEASED, ASOUND, false, std::string("./Sounds/PlayerReleased.wav")))
		return false;
	if (!_audioManager.add(PLAYER_DESTRUCTION, ASOUND, false, std::string("./Sounds/PlayerDestruction.wav")))
		return false;
	if (!_audioManager.add(BYDOS_PLASMA, ASOUND, false, std::string("./Sounds/BydosPlasma.flac")))
		return false;
	if (!_audioManager.add(BYDOS_LASER, ASOUND, false, std::string("./Sounds/BydosLaser.wav")))
		return false;
	if (!_audioManager.add(BYDOS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosDestruction.wav")))
		return false;
	if (!_audioManager.add(BYDOS_BOSS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosBossDestruction.wav")))
		return false;
	return true;
}


void							Game::run(void)
{
	Timer						_playerMvtLock(new sf::Time(sf::seconds(0.20f)));
	Timer						_playerFireLock(new sf::Time(sf::seconds(0.42f)));
//	Timer						test(new sf::Time(sf::seconds(5.0f)));

	_gameWindow->setFramerateLimit(25);
	addObj(PLAYER1, 42, 100);
	addObj(PLAYER2, 20, 40);
	addObj(PLAYER3, 77, 10);
	addObj(PLAYER4, 48, 200);
//	addObj(SBYDOS1, 455, 140);

	static int i = 0;

	//_audioManager.play(GAME_MUSIC);

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
					if (_playerMvtLock.isEnded())
					{
						updatePlayer(Left);
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Right:
					if (_playerMvtLock.isEnded())
					{
						updatePlayer(Right);
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Up:
					if (_playerMvtLock.isEnded())
					{
						updatePlayer(Up);
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Down:
					if (_playerMvtLock.isEnded())
					{
						updatePlayer(Down);
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Space:
					if (_playerFireLock.isEnded())
					{
						_audioManager.play(PLAYER_LASER);
						_playerFireLock.restart();
					}
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
					updatePlayer(Nothing);
					std::cout << "UP RELEASED " << std::endl;
					break;
				case sf::Keyboard::Down:
					updatePlayer(Nothing);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		/*if (test.isEnded())
		{
			updatePlayer(Fire);
			test.restart();
		}*/
		_gameWindow->clear();

		update();
		_layerManager.upDraw();
		draw();
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

bool							Game::updatePlayer(Action action)
{
	int							updatedPos = UNCHANGED;

	obj_type::iterator it = std::find_if(_objects.begin(), _objects.end(), AObject::predicate(_idPlayer));
	if (it != _objects.end())
	{
		switch (action)
		{
		case Left:
			updatedPos = ((*it)->getCaseCurPos() % Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() - 1;
			(*it)->update(Left, updatedPos);
			break;
		case Right:
			updatedPos = (((*it)->getCaseCurPos() + 1) % Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() + 1;
			(*it)->update(Right, updatedPos);
			break;
		case Up:
			updatedPos = ((*it)->getCaseCurPos() / Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() - Game::SIZE_GAME_BOARD;
			(*it)->update(Up, updatedPos);
			break;
		case Down:
			updatedPos = ((*it)->getCaseCurPos() + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() + Game::SIZE_GAME_BOARD;
			(*it)->update(Down, updatedPos);
			break;
		case Fire:
			updatedPos = (*it)->getCaseCurPos() + 4;
			(*it)->update(Right, updatedPos);
			break;
		default:
			(*it)->update(Nothing, updatedPos);
			break;
		}
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

Game::Game(sf::RenderWindow *gameWindow, sf::Event *event) : _factory(gameWindow, &_textureManager), _layerManager(gameWindow, &_textureManager), _audioManager()
{
	_gameWindow = gameWindow;
	_event = event;
	_idPlayer = 42;
}