#include		<SFML/Audio.hpp>
#include		<SFML/Network.hpp>
#include		"EventRequest.hh"
#include		"DeathRequest.h"
#include		"ElemRequest.hh"
#include		"LeaveRequest.h"
#include		"AliveRequest.h"
#include		"AObject.h"
#include		"game.h"
#include		"Layer.h"
#include		"RequestCode.hh"
#include		"NetworkManager.hh"
#include		<algorithm>
#include		"Timer.h"
#include		"InfosUser.hh"

const float Game::VLAG = 0.4f;
const float Game::ALIVE_TIMER = 3.0f;
const float Game::MAX_VLAG = 3.0f;
const float Game::OBJ_DEC_X_FRAME = Game::PX_DEC_X /  8.0f;
const float Game::OBJ_DEC_Y_FRAME = Game::PX_DEC_Y / 8.0f;

using namespace requestCode::game::client;
using namespace requestCode::game;

Game::~Game()
{
  for (obj_type::iterator it = _objects.begin(); it != _objects.end(); ++it)
    delete *it;
}

bool							Game::load(void)
{
	if(!_textureManager.addTexture(server::PLAYER1, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(server::PLAYER2, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(server::PLAYER3, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(server::PLAYER4, std::string("./Images/r-typesheet42.png")))
		return false;
	if (!_textureManager.addTexture(server::SBYDOS1, std::string("./Images/r-typesheet5.png")))
		return false;
	if (!_textureManager.addTexture(server::LAYER1, std::string("./Images/Aurora1.png")))
		return false;
	if (!_textureManager.addTexture(server::LAYER2, std::string("./Images/Aurora2.png")))
		return false;
	if (!_textureManager.addTexture(server::LAYER3, std::string("./Images/Comet1.png")))
		return false;
	if (!_textureManager.addTexture(server::NORMAL_BANG, std::string("./Images/r-typesheet44.png")))
		return false;
	if (!_textureManager.addTexture(server::BIG_BANG, std::string("./Images/r-typesheet44.png")))
		return false;
	if (!_textureManager.addTexture(server::PLAYER_LASER, std::string("./Images/r-typesheet2.png")))
		return false;
	if (!_textureManager.addTexture(server::PLAYER_BLAST, std::string("./Images/r-typesheet1.png")))
		return false;
	if (!_textureManager.addTexture(server::BYDOS_PLASMA, std::string("./Images/r-typesheet43.png")))
		return false;
	if (!_textureManager.addTexture(server::BYDOS_LASER, std::string("./Images/r-typesheet43.png")))
		return false;
	if (!_textureManager.addTexture(server::ZOGZOG, std::string("./Images/r-typesheet24.png")))
		return false;
	if (!_textureManager.addTexture(server::SLIDER, std::string("./Images/r-typesheet23.png")))
		return false;
	if (!_textureManager.addTexture(server::SHRIMP_BOSS, std::string("./Images/r-typesheet30.png")))
		return false;
	if (!_textureManager.addTexture(server::GARBAGE_BOSS, std::string("./Images/r-typesheet38.png")))
		return false;
	if (!_textureManager.addTexture(server::INDESTRUCTIBLE_WALL, std::string("./Images/r-type_indestructible_wall.png")))
		return false;

	if (!_layerManager.addLayer(server::LAYER1, LAYER_1, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER2, LAYER_2, sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1000.0f), sf::Vector2f(-4.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(-50.0f, 100.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1000.0f), sf::Vector2f(-4.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(300.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1000.0f), sf::Vector2f(-8.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(42.0f, -890.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 700.0f), sf::Vector2f(-3.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(200.0f, 0.0f), sf::Vector2f(200.0f, 0.0f), sf::Vector2f(800.0f, 1400.0f), sf::Vector2f(-5.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 900.0f), sf::Vector2f(-8.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(42.0f, -890.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 700.0f), sf::Vector2f(-3.0f, -5.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(200.0f, 0.0f), sf::Vector2f(200.0f, 0.0f), sf::Vector2f(800.0f, 1400.0f), sf::Vector2f(-5.0f, -5.0f), NULL, true))
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
	if (!AudioManager::getInstance().add(server::BYDOS_LASER, ASOUND, false, std::string("./Sounds/BydosLaser.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABYDOS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosDestruction.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABYDOS_BOSS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosBossDestruction.wav")))
		return false;
	return true;
}


void							Game::run(void)
{
	Timer						_playerMvtLock(sf::seconds(0.20f));
	Timer						_playerFireLock(sf::seconds(0.42f));
	Timer						_playerBlastLock(sf::seconds(1.0f));
	Timer						_aliveRequest(sf::seconds(0.25f));
	Timer						test(sf::seconds(50.0f));
	ARequest					*req;

	_gameWindow->setFramerateLimit(25);
	_gameWindow->setKeyRepeatEnabled(true);
	// addObj(INDESTRUCTIBLE_WALL, 42, 254);
	// addObj(INDESTRUCTIBLE_WALL, 42, 255);
	// addObj(INDESTRUCTIBLE_WALL, 42, 253);
	// addObj(INDESTRUCTIBLE_WALL, 42, 0);
	// addObj(INDESTRUCTIBLE_WALL, 42, 1);
	// addObj(INDESTRUCTIBLE_WALL, 42, 2);
	// addObj(server::PLAYER2, 20, 40);
	// addObj(server::PLAYER3, 77, 10);
	// addObj(server::PLAYER4, 48, 200);
	// addObj(server::GARBAGE_BOSS, 4877, 0);
	// addObj(server::ZOGZOG, 4877, 100);
	// addObj(server::ZOGZOG, 44, 100);
	// addObj(server::ZOGZOG, 4877, 255);
	// addObj(server::SBYDOS1, 455, 140);

	AudioManager::getInstance().play(AGAME_MUSIC);


	_network.setUdp(sf::IpAddress(sf::IpAddress(InfosUser::getInstance().authenticate.addressIp)), InfosUser::getInstance().authenticate.portUDP);
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
							_network.sendRequest(new EventRequest(MOVE, NORTH_WEST, InfosUser::getInstance().authenticate.id));
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							std::cout << "SOUTH WEST MOTHERFUCKER" << std::endl;
							_network.sendRequest(new EventRequest(MOVE, SOUTH_WEST, InfosUser::getInstance().authenticate.id));
						}
						else
						{
							// updatePlayer(Left);
							_network.sendRequest(new EventRequest(MOVE, WEST, InfosUser::getInstance().authenticate.id));
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
							_network.sendRequest(new EventRequest(MOVE, SOUTH_EAST, InfosUser::getInstance().authenticate.id));
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							std::cout << "SOUTH east MOTHERFUCKER" << std::endl;
							_network.sendRequest(new EventRequest(MOVE, SOUTH_WEST, InfosUser::getInstance().authenticate.id));
						}
						else
						{
							// updatePlayer(Right);
							_network.sendRequest(new EventRequest(MOVE, EAST, InfosUser::getInstance().authenticate.id));
						}
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Up:
					if (_playerMvtLock.isEnded())
					{
						// updatePlayer(Up);
						_network.sendRequest(new EventRequest(MOVE, NORTH, InfosUser::getInstance().authenticate.id));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Down:
					if (_playerMvtLock.isEnded())
					{
						// updatePlayer(Down);
						_network.sendRequest(new EventRequest(MOVE, SOUTH, InfosUser::getInstance().authenticate.id));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Space:
					if (_playerFireLock.isEnded())
					{
						// AudioManager::getInstance().play(APLAYER_LASER);
						_network.sendRequest(new EventRequest(SHOOT, SIMPLE, InfosUser::getInstance().authenticate.id));
						// delObj(44);
						_playerFireLock.restart();
					}
					break;
				case sf::Keyboard::Escape:
					_network.sendRequest(new LeaveRequest(InfosUser::getInstance().authenticate.id));
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
		  (this->*_map[req->code()])(req);
		if (_aliveRequest.isEnded())
		{
			_network.sendRequest(new AliveRequest(InfosUser::getInstance().authenticate.id));
			_aliveRequest.restart();
		}
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

bool							Game::updateObj(game::Type type, game::Dir lDir, int id, int pos)
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

bool							Game::addObj(game::Type type, int id, int pos)
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

void	Game::elem(const ARequest *req)
{
  const ElemRequest	*elem = dynamic_cast<const ElemRequest *>(req);

  updateObj(elem->type(), elem->dir(), elem->ID(), elem->pos());
}

void	Game::death(const ARequest *req)
{
  const DeathRequest	*death = dynamic_cast<const DeathRequest *>(req);

  delObj(death->ID());
}

void	Game::buff(const ARequest *req)
{
  (void)req;
}

void	Game::score(const ARequest *req)
{
  (void)req;
}

void	Game::victory(const ARequest *req)
{
  (void)req;
}

void	Game::loose(const ARequest *req)
{
  (void)req;
}

void	Game::nextStage(const ARequest *req)
{
  (void)req;
}

Game::Game(sf::RenderWindow *gameWindow, sf::Event *event, network::Manager &net) : _layerManager(gameWindow, &_textureManager), _network(net)
{
	Factory::getInstance().init(gameWindow, &_textureManager);
	_gameWindow = gameWindow;
	_event = event;
	_idPlayer = 42;

	_map[requestCode::game::ELEM] = &Game::elem;
	_map[requestCode::game::DEATH] = &Game::death;
	_map[requestCode::game::BUFF] = &Game::buff;
	_map[requestCode::game::SCORE] = &Game::score;
	_map[requestCode::game::VICTORY] = &Game::victory;
	_map[requestCode::game::LOOSE] = &Game::loose;
	_map[requestCode::game::NEXTSTAGE] = &Game::nextStage;
}
