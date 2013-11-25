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
	if (!_textureManager.addTexture(server::BG1, std::string("./Images/Aurora1.png")))
		return false;
	if (!_textureManager.addTexture(server::BG2, std::string("./Images/Aurora2.png")))
		return false;
	if (!_textureManager.addTexture(server::COMET, std::string("./Images/Comet1.png")))
		return false;

	if (!_textureManager.addTexture(server::LOOSE, std::string("./Images/r-type-loose.png")))
		return false;
	if (!_textureManager.addTexture(server::VICTORY, std::string("./Images/r-type-victory.png")))
		return false;
	if (!_textureManager.addTexture(server::NEXSTAGE, std::string("./Images/r-type-next_stage.png")))
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
	if (!_textureManager.addTexture(server::VITALITY_BONUS , std::string("./Images/r-type_vitality_bonus.png")))
		return false;
	if (!_textureManager.addTexture(server::POWER_BONUS, std::string("./Images/r-type_power_bonus.png")))
		return false;


	if (!_layerManager.addLayer(server::BG1, LBG1, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(server::BG2, LBG2, sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
/*	if (!_layerManager.addLayer(server::LAYER3, LAYER_3, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1000.0f), sf::Vector2f(-4.0f, -5.0f), NULL, true))
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
		return false;*/

	if (!_layerManager.addLayer(server::COMET, LCOMET, sf::Vector2f(200.0f, 0.0f), sf::Vector2f(200.0f, 0.0f), sf::Vector2f(1000.0f, 1300.0f), sf::Vector2f(-5.0f, -5.0f), NULL, true))
		return false;


	if (!_layerManager.addLayer(server::VICTORY, LVICTORY, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), new Timer(sf::Time(sf::seconds(4.0))), false))
		return false;
	if (!_layerManager.addLayer(server::LOOSE, LLOOSE, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), new Timer(sf::Time(sf::seconds(4.0))), false))
		return false;
	if (!_layerManager.addLayer(server::NEXSTAGE, LNEXSTAGE, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), new Timer(sf::Time(sf::seconds(4.0))), false))
		return false;

/*	bool							addLayer(game::Type objType, LayerType lType, const sf::Vector2f &lInit,
		const sf::Vector2f &lReset, const sf::Vector2f &lLim,
		const sf::Vector2f &lInc, Timer *lTimer, bool lEn);
*/


	if (!AudioManager::getInstance().add(AGAME_MUSIC, AMUSIC, true, std::string("./Sounds/GameMusic.wav")))
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
	if (!AudioManager::getInstance().add(ABYDOS_LASER, ASOUND, false, std::string("./Sounds/BydosLaser.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABYDOS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosDestruction.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABYDOS_BOSS_DESTRUCTION, ASOUND, false, std::string("./Sounds/BydosBossDestruction.wav")))
		return false;
	if (!AudioManager::getInstance().add(AGAME_OVER, ASOUND, false, std::string("./Sounds/GameOver.wav")))
		return false;
	if (!AudioManager::getInstance().add(ABONUS, ASOUND, false, std::string("./Sounds/Bonus.wav")))
		return false;
	if (!AudioManager::getInstance().add(AVICTORY, ASOUND, false, std::string("./Sounds/Victory.wav")))
		return false;
	if (!AudioManager::getInstance().add(ANEXT_STAGE, ASOUND, false, std::string("./Sounds/NextStage.wav")))
		return false;
	return true;
}


void							Game::run(void)
{
	Timer						_playerMvtLock(sf::seconds(0.20f));
	Timer						_playerFireLock(sf::seconds(0.42f));
	Timer						_playerBlastLock(sf::seconds(1.40f));
	Timer						_aliveRequest(sf::seconds(0.25f));
	ARequest					*req;

	_gameWindow->setFramerateLimit(25);
	_gameWindow->setKeyRepeatEnabled(true);
	// addObj(INDESTRUCTIBLE_WALL, 42, 254);
	// addObj(INDESTRUCTIBLE_WALL, 42, 255);
	// addObj(INDESTRUCTIBLE_WALL, 42, 253);
	// addObj(INDESTRUCTIBLE_WALL, 42, 0);
	// addObj(INDESTRUCTIBLE_WALL, 42, 1);
//	 addObj(server::POWER_BONUS, 42, 80);
	// addObj(server::PLAYER2, 20, 40);
	// addObj(server::PLAYER3, 77, 10);
	// addObj(server::PLAYER4, 48, 200);
	// addObj(server::GARBAGE_BOSS, 4877, 0);
	//addObj(server::ZOGZOG, 4877, 100);
	 addObj(server::POWER_BONUS, 44, 100);
	// addObj(server::ZOGZOG, 4877, 255);
	// addObj(server::SBYDOS1, 455, 140);

	AudioManager::getInstance().play(AGAME_MUSIC);


	_layerManager.enableLayer(LNEXSTAGE);

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
							_network.sendRequest(new EventRequest(MOVE, NORTH_WEST, InfosUser::getInstance().authenticate.id));
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
							_network.sendRequest(new EventRequest(MOVE, SOUTH_WEST, InfosUser::getInstance().authenticate.id));
						else
							_network.sendRequest(new EventRequest(MOVE, WEST, InfosUser::getInstance().authenticate.id));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Right:
					if (_playerMvtLock.isEnded())
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
							_network.sendRequest(new EventRequest(MOVE, SOUTH_EAST, InfosUser::getInstance().authenticate.id));
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
							_network.sendRequest(new EventRequest(MOVE, SOUTH_WEST, InfosUser::getInstance().authenticate.id));
						else
							_network.sendRequest(new EventRequest(MOVE, EAST, InfosUser::getInstance().authenticate.id));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Up:
					if (_playerMvtLock.isEnded())
					{
						_network.sendRequest(new EventRequest(MOVE, NORTH, InfosUser::getInstance().authenticate.id));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Down:
					if (_playerMvtLock.isEnded())
					{
						_network.sendRequest(new EventRequest(MOVE, SOUTH, InfosUser::getInstance().authenticate.id));
						_playerMvtLock.restart();
					}
					break;
				case sf::Keyboard::Space:
					if (_playerFireLock.isEnded())
					{
						// AudioManager::getInstance().play(APLAYER_LASER);
						_network.sendRequest(new EventRequest(SHOOT, SIMPLE, InfosUser::getInstance().authenticate.id));
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

/*		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) == true)
		{
			AudioManager::getInstance().play(APLAYER_CHARGED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) == false && _playerBlastLock.isEnded())
		{
			AudioManager::getInstance().stop(APLAYER_CHARGED);
			AudioManager::getInstance().play(APLAYER_RELEASED);
			_network.sendRequest(new EventRequest(SHOOT, BLAST, InfosUser::getInstance().authenticate.id));
			_playerBlastLock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) == false && !_playerBlastLock.isEnded())
		{
			AudioManager::getInstance().stop(APLAYER_CHARGED);
			_playerBlastLock.restart();
		}*/
		
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

	if ((obj = Factory::getInstance().createObject(type, id, pos, requestCode::game::client::EAST)) != NULL)
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
  AudioManager::getInstance().play(ABONUS);
}

void	Game::score(const ARequest *req)
{
  (void)req;
}

void	Game::victory(const ARequest *req)
{
  (void)req;
  _layerManager.enableLayer(LVICTORY);
  AudioManager::getInstance().play(AVICTORY);
}

void	Game::loose(const ARequest *req)
{
  (void)req;
  _layerManager.enableLayer(LLOOSE);
  AudioManager::getInstance().play(AGAME_OVER);
}

void	Game::nextStage(const ARequest *req)
{
  (void)req;
  _layerManager.enableLayer(LNEXSTAGE);
  AudioManager::getInstance().play(ANEXT_STAGE)  ;
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
