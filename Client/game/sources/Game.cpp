#include		<SFML/Audio.hpp>
#include		<SFML/Network.hpp>
#include		"EventRequest.hh"
#include		"LeaveRequest.h"
#include		"AObject.h"
#include		"game.h"
#include		"Layer.h"
#include		"RequestCode.hh"
#include		"NetworkManager.hh"
#include		<algorithm>
#include		"Timer.h"

const float Game::VLAG = 0.4f;
const float Game::ALIVE_TIMER = 3.0f;
const float Game::MAX_VLAG = 3.0f;
const float Game::OBJ_DEC_X_FRAME = Game::PX_DEC_X /  8.0f;
const float Game::OBJ_DEC_Y_FRAME = Game::PX_DEC_Y / 8.0f;
using namespace requestCode::game::client;

Game::~Game()
{
  for (obj_type::iterator it = _objects.begin(); it != _objects.end(); ++it)
    delete *it;
}

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
	if (!_textureManager.addTexture(NORMAL_BANG, std::string("./Images/r-typesheet44.png")))
		return false;
	if (!_textureManager.addTexture(BIG_BANG, std::string("./Images/r-typesheet44.png")))
		return false;
	if (!_textureManager.addTexture(PLAYER_LASER, std::string("./Images/r-typesheet2.png")))
		return false;
	if (!_textureManager.addTexture(PLAYER_BLAST, std::string("./Images/r-typesheet1.png")))
		return false;
	if (!_textureManager.addTexture(BYDOS_PLASMA, std::string("./Images/r-typesheet43.png")))
		return false;
	if (!_textureManager.addTexture(BYDOS_LASER, std::string("./Images/r-typesheet43.png")))
		return false;
	if (!_textureManager.addTexture(ZOGZOG, std::string("./Images/r-typesheet24.png")))
		return false;
	if (!_textureManager.addTexture(SLIDER, std::string("./Images/r-typesheet23.png")))
		return false;
	if (!_textureManager.addTexture(SHRIMP_BOSS, std::string("./Images/r-typesheet30.png")))
		return false;
	if (!_textureManager.addTexture(GARBAGE_BOSS, std::string("./Images/r-typesheet38.png")))
		return false;


	if (!_layerManager.addLayer(LAYER1, LAYER_1, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER2, LAYER_2, sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1000.0f), sf::Vector2f(-4.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(-50.0f, 100.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1000.0f), sf::Vector2f(-4.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(300.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1000.0f), sf::Vector2f(-8.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(42.0f, -890.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 700.0f), sf::Vector2f(-3.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(200.0f, 0.0f), sf::Vector2f(200.0f, 0.0f), sf::Vector2f(800.0f, 1400.0f), sf::Vector2f(-5.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 900.0f), sf::Vector2f(-8.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(42.0f, -890.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 700.0f), sf::Vector2f(-3.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(LAYER3, LAYER_3, sf::Vector2f(200.0f, 0.0f), sf::Vector2f(200.0f, 0.0f), sf::Vector2f(800.0f, 1400.0f), sf::Vector2f(-5.0f, -5.0f), NULL, true))
		return false;


	if (!AudioManager::getInstance().add(AGAME_MUSIC, AMUSIC, true, std::string("./Sounds/Lepi.ogg")))
		return false;
	if (!AudioManager::getInstance().add(APLAYER_LASER, ASOUND, false, std::string("./Sounds/PlayerLaser.wav")))
		return false;
	if (!AudioManager::getInstance().add(APLAYER_CHARGED, ASOUND, true, std::string("./Sounds/PlayerCharged.wav")))
		return false;
	if (!AudioManager::getInstance().add(APLAYER_RELEASED, ASOUND, false, std::string("./Sounds/PlayerReleased.wav")))
		return false;
	if (!AudioManager::getInstance().add(APLAYER_DESTRUCTION, ASOUND, false, std::string("./Sounds/PlayerDestruction.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABYDOS_PLASMA, ASOUND, false, std::string("./Sounds/BydosPlasma.flac")))
		return false;
	if (!AudioManager::getInstance().add(BYDOS_LASER, ASOUND, false, std::string("./Sounds/BydosLaser.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABYDOS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosDestruction.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABYDOS_BOSS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosBossDestruction.wav")))
		return false;
	return true;
}

//projectiles + singleton

void							Game::run(void)
{
	Timer						_playerMvtLock(sf::seconds(0.20f));
	Timer						_playerFireLock(sf::seconds(0.42f));
	Timer						_playerBlastLock(sf::seconds(1.0f));
	Timer						test(sf::seconds(50.0f));
	ARequest					*req;

	_gameWindow->setFramerateLimit(25);
	_gameWindow->setKeyRepeatEnabled(true);
	// addObj(PLAYER1, 42, 100);
	// addObj(PLAYER2, 20, 40);
	// addObj(PLAYER3, 77, 10);
	// addObj(PLAYER4, 48, 200);
	// addObj(GARBAGE_BOSS, 4877, 0);
	// addObj(ZOGZOG, 4877, 100);
	// addObj(ZOGZOG, 44, 100);
	// addObj(ZOGZOG, 4877, 255);
	// addObj(SBYDOS1, 455, 140);

	AudioManager::getInstance().play(AGAME_MUSIC);


	_network.setUdp(sf::IpAddress("127.0.0.5"), 44202);
	_network.switchTo(network::Manager::UDP);


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
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							std::cout << "NORTH WEST MOTHERFUCKER" << std::endl;
							_network.sendRequest(new EventRequest(MOVE, NORTH_WEST));
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							std::cout << "SOUTH WEST MOTHERFUCKER" << std::endl;
							_network.sendRequest(new EventRequest(MOVE, SOUTH_WEST));
						}
						else
						{
							// updatePlayer(Left);
							_network.sendRequest(new EventRequest(MOVE, WEST));
						}
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Right:
					if (_playerMvtLock.isEnded())
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							std::cout << " MOTHERFUCKER NORTH EAST" << std::endl;
							_network.sendRequest(new EventRequest(MOVE, SOUTH_EAST));
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							std::cout << "SOUTH east MOTHERFUCKER" << std::endl;
							_network.sendRequest(new EventRequest(MOVE, SOUTH_WEST));
						}
						else
						{
							// updatePlayer(Right);
							_network.sendRequest(new EventRequest(MOVE, EAST));
						}
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Up:
					if (_playerMvtLock.isEnded())
					{
						// updatePlayer(Up);
						_network.sendRequest(new EventRequest(MOVE, NORTH));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Down:
					if (_playerMvtLock.isEnded())
					{
						// updatePlayer(Down);
						_network.sendRequest(new EventRequest(MOVE, SOUTH));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Space:
					if (_playerFireLock.isEnded())
					{
						// AudioManager::getInstance().play(APLAYER_LASER);
						_network.sendRequest(new EventRequest(SHOOT, SIMPLE));
						// delObj(44);
						_playerFireLock.restart();
					}
					break;
				case sf::Keyboard::Escape:
					_network.sendRequest(new LeaveRequest());
				  cleanGame();
				  return;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		while ((req = _network.recvRequest()) != 0)
		  ;
		//LAAAAAAAAAAAAAAAAAA

		_gameWindow->clear();
		cleanObjects();
		_layerManager.upDraw();
		drawObjects();
		_gameWindow->display();
	}
	cleanGame();
}


void							Game::drawObjects(void)
{
	for (obj_type::iterator it = _objects.begin(); it != _objects.end(); ++it)
		(*it)->draw();
}


void							Game::cleanObjects(void)
{
	for (obj_type::iterator it = _objects.begin(); it != _objects.end();)
	{
		if (!(*it)->isAlive())
		{
			AObject	*entity = *it;
			it = _objects.erase(it);
			std::cout << entity->getObjType() << std::endl;
			delete entity;
		}
		else
			++it;
	}
}


bool							Game::updatePlayer(Action action)
{
	int							updatedPos = UNCHANGED;
	obj_type::iterator			it = std::find_if(_objects.begin(), _objects.end(), AObject::predicate(_idPlayer));

	if (it != _objects.end())
	{
		switch (action)
		{
		case Left:
			updatedPos = ((*it)->getCaseCurPos() % Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() - 1;
			(*it)->update(Unset, updatedPos);
			break;
		case Right:
			updatedPos = (((*it)->getCaseCurPos() + 1) % Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() + 1;
			(*it)->update(Unset, updatedPos);
			break;
		case Up:
			updatedPos = ((*it)->getCaseCurPos() / Game::SIZE_GAME_BOARD == 0) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() - Game::SIZE_GAME_BOARD;
			(*it)->update(Unset, updatedPos);
			break;
		case Down:
			updatedPos = ((*it)->getCaseCurPos() + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? (*it)->getCaseCurPos() : (*it)->getCaseCurPos() + Game::SIZE_GAME_BOARD;
			(*it)->update(Unset, updatedPos);
			break;
		default:
			(*it)->update(Unset, updatedPos);
			break;
		}
//		return true;
	}


	obj_type::iterator ot = std::find_if(_objects.begin(), _objects.end(), AObject::predicate(44));
	if (ot != _objects.end())
	{
		switch (action)
		{
		case Left:
			updatedPos = ((*ot)->getCaseCurPos() % Game::SIZE_GAME_BOARD == 0) ? (*ot)->getCaseCurPos() : (*ot)->getCaseCurPos() - 1;
			(*ot)->update(Unset, updatedPos);
			break;
		case Right:
			updatedPos = (((*ot)->getCaseCurPos() + 1) % Game::SIZE_GAME_BOARD == 0) ? (*ot)->getCaseCurPos() : (*ot)->getCaseCurPos() + 1;
			(*ot)->update(Unset, updatedPos);
			break;
		case Up:
			updatedPos = ((*ot)->getCaseCurPos() / Game::SIZE_GAME_BOARD == 0) ? (*ot)->getCaseCurPos() : (*ot)->getCaseCurPos() - Game::SIZE_GAME_BOARD;
			(*ot)->update(Unset, updatedPos);
			break;
		case Down:
			updatedPos = ((*ot)->getCaseCurPos() + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? (*ot)->getCaseCurPos() : (*ot)->getCaseCurPos() + Game::SIZE_GAME_BOARD;
			(*ot)->update(Unset, updatedPos);
			break;
		case Fire:
			updatedPos = (*ot)->getCaseCurPos() + 6;
			(*ot)->update(Unset, updatedPos);
			break;
		default:
			(*ot)->update(Unset, updatedPos);
			break;
		}
		return true;
	}
	return false;
}


bool						Game::delObj(int id)
{
	obj_type::iterator		it = std::find_if(_objects.begin(), _objects.end(), AObject::predicate(id));

	if (it != _objects.end())
	{
		AObject	*entity = *it;

		_objects.erase(it);
		entity->onDestruction(*this);
		delete entity;
		return true;
	}
	return false;
}

/*GAME_MUSIC = 0,
PLAYER_LASER,
PLAYER_CHARGED,
PLAYER_RELEASED,
PLAYER_DESTRUCTION,
BYDOS_PLASMA,
BYDOS_LASER,
BYDOS_DESTRUCTION,
BYDOS_BOSS_DESTRUCTION*/

bool							Game::updateObj(ObjType type, LookDirection lDir, int id, int pos)
{
	obj_type::iterator it = std::find_if(_objects.begin(), _objects.end(), AObject::predicate(id));

	if (it != _objects.end())
	{
		(*it)->update(lDir, pos);
		return true;
	}
	else
		return (addObj(type, id, pos));
}

bool							Game::addObj(ObjType type, int id, int pos)
{
	AObject						*obj;

	if ((obj = Factory::getInstance().createObject(type, id, pos, East)) != NULL)
	{
		_objects.push_back(obj);
		return true;
	}
	return false;
}

void							Game::cleanGame()
{
	for (obj_type::iterator it = _objects.begin(); it != _objects.end();)
	{
			AObject	*entity = *it;
			std::cout << (*it)->getObjType() << std::endl;
			it = _objects.erase(it);
			delete entity;
	}
	if (_gameWindow->isOpen())
		_gameWindow->clear();
	AudioManager::getInstance().stop(AGAME_MUSIC);
}

int							Game::generateId(void)
{
	static int				id = 66000;

	return ((id + 1) < 66000) ? 66000 : id + 1;
}

Game::Game(sf::RenderWindow *gameWindow, sf::Event *event, network::Manager &net) : _layerManager(gameWindow, &_textureManager), _network(net)
{
	Factory::getInstance().init(gameWindow, &_textureManager);
	_gameWindow = gameWindow;
	_event = event;
	_idPlayer = 42;
}
