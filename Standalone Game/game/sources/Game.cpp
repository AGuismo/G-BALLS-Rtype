#include		<SFML/Audio.hpp>
#include		<SFML/Network.hpp>
#include		<algorithm>
#include		"EventManager.hh"
#include		"Animation.hh"
#include		"Game.hh"
#include		"Layer.hh"
#include		"RequestCode.hh"
#include		"Timer.hh"
#include		"ObjectMover.hh"
#include		"InfosUser.hh"
#include		"TextureManager.hh"

using namespace requestCode::game;

Game::~Game()
{
  for (obj_map_type::iterator it = _objects.begin(); it != _objects.end(); ++it)
    delete it->second;
}

bool							Game::load(void)
{
	std::vector<Texture>		t;

	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 1), Animation::ACT_DEFAULT), sf::IntRect(132, 0, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 1), Animation::ACT_UP), sf::IntRect(264, 0, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 1), Animation::ACT_DOWN), sf::IntRect(0, 0, 68, 38)));

	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 2), Animation::ACT_DEFAULT), sf::IntRect(132, 34, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 2), Animation::ACT_UP), sf::IntRect(264, 34, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 2), Animation::ACT_DOWN), sf::IntRect(0, 34, 68, 38)));

	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 3), Animation::ACT_DEFAULT), sf::IntRect(132, 68, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 3), Animation::ACT_UP), sf::IntRect(264, 68, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 3), Animation::ACT_DOWN), sf::IntRect(0, 68, 68, 38)));

	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 4), Animation::ACT_DEFAULT), sf::IntRect(132, 102, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 4), Animation::ACT_UP), sf::IntRect(264, 102, 68, 38)));
	t.push_back(Texture("./Images/r-typesheet42.png", game::TextureManager::Key(Entity::createType(Entity::PLAYER, 4), Animation::ACT_DOWN), sf::IntRect(0, 102, 68, 38)));

 	t.push_back(Texture("./Images/r-typesheet1.png", game::TextureManager::Key(Entity::createType(Entity::MISSILE, 1)), sf::IntRect(368, 336, 162, 40)));

	//if (!_textureManager.addTexture(server::SBYDOS1, std::string("./Images/r-typesheet5.png")))
	//	return false;


	//if (!_textureManager.addTexture(server::NORMAL_BANG, std::string("./Images/r-typesheet44.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::BIG_BANG, std::string("./Images/r-typesheet44.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::PLAYER_LASER, std::string("./Images/r-typesheet2.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::PLAYER_BLAST, std::string("./Images/r-typesheet1.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::BYDOS_PLASMA, std::string("./Images/r-typesheet43.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::BYDOS_LASER, std::string("./Images/r-typesheet43.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::ZOGZOG, std::string("./Images/r-typesheet24.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::SLIDER, std::string("./Images/r-typesheet23.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::SHRIMP_BOSS, std::string("./Images/r-typesheet30.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::GARBAGE_BOSS, std::string("./Images/r-typesheet38.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::INDESTRUCTIBLE_WALL, std::string("./Images/r-type_indestructible_wall.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::VITALITY_BONUS , std::string("./Images/r-type_vitality_bonus.png")))
	//	return false;
	//if (!_textureManager.addTexture(server::POWER_BONUS, std::string("./Images/r-type_power_bonus.png")))
	//	return false;

	for (std::vector<Texture>::iterator it = t.begin(); it != t.end(); ++it)
		if (!_textureManager.addTexture(it->ImagePath, it->TextureCode, it->pos))
			return (false);

	if (!_layerManager.addLayer(std::string("./Images/Aurora1.png"), LBG1, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(std::string("./Images/Aurora2.png"), LBG2, sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(2560.0f, 0.0f), sf::Vector2f(-2560.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), NULL, true))
		return false;
	if (!_layerManager.addLayer(std::string("./Images/Comet1.png"), LCOMET, sf::Vector2f(200.0f, 0.0f), sf::Vector2f(200.0f, 0.0f), sf::Vector2f(1000.0f, 1300.0f), sf::Vector2f(-5.0f, -5.0f), NULL, true))
		return false;

	if (!_layerManager.addLayer(std::string("./Images/r-type-victory.png"), LVICTORY, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), new Timer(sf::Time(sf::seconds(4.0))), false))
		return false;
	if (!_layerManager.addLayer(std::string("./Images/r-type-loose.png"), LLOOSE, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), new Timer(sf::Time(sf::seconds(4.0))), false))
		return false;
	if (!_layerManager.addLayer(std::string("./Images/r-type-next_stage.png"), LNEXSTAGE, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), new Timer(sf::Time(sf::seconds(4.0))), false))
		return false;


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

void			Game::onMyselfMove(Position::dir direction)
{
	ObjectMover	*self = _objects[_idPlayer];

	self->onMove(direction);
}

void			Game::onMoveLeft(sf::Keyboard::Key key, Game *self)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		self->onMyselfMove(Position::NORTH_WEST);
	//_network.sendRequest(new EventRequest(MOVE, NORTH_WEST, InfosUser::getInstance().authenticate.id));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		self->onMyselfMove(Position::SOUTH_WEST);
	//_network.sendRequest(new EventRequest(MOVE, SOUTH_WEST, InfosUser::getInstance().authenticate.id));
	else
		self->onMyselfMove(Position::WEST);
	//_network.sendRequest(new EventRequest(MOVE, WEST, InfosUser::getInstance().authenticate.id));
}

void			Game::onMoveRight(sf::Keyboard::Key key, Game *self)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		self->onMyselfMove(Position::NORTH_EAST);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		self->onMyselfMove(Position::SOUTH_EAST);
	else
		self->onMyselfMove(Position::EAST);
}

void			Game::onMoveUp(sf::Keyboard::Key key, Game *self)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		self->onMyselfMove(Position::NORTH_EAST);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		self->onMyselfMove(Position::NORTH_WEST);
	else
		self->onMyselfMove(Position::NORTH);
}

void			Game::onMoveDown(sf::Keyboard::Key key, Game *self)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		self->onMyselfMove(Position::SOUTH_EAST);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		self->onMyselfMove(Position::SOUTH_WEST);
	else
		self->onMyselfMove(Position::SOUTH);
}

void			Game::onFire(sf::Keyboard::Key key, Game *self)
{
	self->_objects[self->_objectID] = ObjectFactory::getInstance().createObject(Entity::createType(Entity::MISSILE, 1), self->_objectID, Position(500, 500, Position::EAST));
	++self->_objectID;
}

void							Game::run(void)
{
	Timer						_playerFireLock(sf::seconds(0.5f));
	Timer						_playerBlastLock(sf::seconds(2.0f));
	Timer						_aliveRequest(sf::seconds(0.5f));
	Timer						_lostConnection(sf::seconds(3.0f));
	EventManager				ev(*_event, sf::milliseconds(200));
	//ARequest					*req;

	//_gameWindow->setFramerateLimit(25);
	_objectID = 2;
	_gameWindow->setKeyRepeatEnabled(true);
	ev.registerKey(sf::Keyboard::Left, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveLeft, this), true);
	ev.registerKey(sf::Keyboard::Right, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveRight, this), true);
	ev.registerKey(sf::Keyboard::Up, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveUp, this), true);
	ev.registerKey(sf::Keyboard::Down, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveDown, this), true);
	ev.registerKey(sf::Keyboard::Space, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onFire, this), true);

	AudioManager::getInstance().play(AGAME_MUSIC);
	_objects[1] = ObjectFactory::getInstance().createObject(Entity::createType(Entity::PLAYER, 1), 1, Position(250, 250, Position::EAST));

	while (_gameWindow->isOpen())
	{
		while (_gameWindow->pollEvent(*_event))
		{
			switch (_event->type)
			{
			case sf::Event::Closed:
				_gameWindow->close();
				break;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//_network.sendRequest(new LeaveRequest(InfosUser::getInstance().authenticate.id));
			cleanGame();
			return;
		}
		ev.update();

		//while ((req = _network.recvRequest()) != 0)
		//  {
		//    callback_map::iterator	it = _map.find(req->code());

		//    if (it != _map.end())
		//      (this->*(it->second))(req);
		//	_lostConnection.restart();
		//  }

		if (_aliveRequest.isEnded())
		{
			//_network.sendRequest(new AliveRequest(InfosUser::getInstance().authenticate.id));
			_aliveRequest.restart();
		}

		//if (_lostConnection.isEnded())
		//{
			//_network.sendRequest(new LeaveRequest(InfosUser::getInstance().authenticate.id));
		//	cleanGame();
		//	return;
		//}
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
	for (obj_map_type::const_iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		it->second->update();

		const sf::Texture	&texture = it->second->getAnimation().getFrame();
		sf::Sprite	sprite(texture);

		sprite.setPosition(it->second->getCurrentPos());
		_gameWindow->draw(sprite);
	}
}


void							Game::cleanObjects(void)
{
//	for (obj_type::iterator it = _objects.begin(); it != _objects.end();)
//	{
//		if (!(*it)->isAlive())
//		{
//			AObject	*entity = *it;
//			it = _objects.erase(it);
//#if defined(DEBUG)
//			std::cout << entity->getObjType() << std::endl;
//#endif
//			delete entity;
//		}
//		else
//			++it;
//	}
}




bool						Game::delObj(int id)
{
	obj_map_type::iterator		it = _objects.find(id);

	if (it != _objects.end())
	{
		ObjectMover	*obj = it->second;

		_objects.erase(it);
		//obj->onDestruction(*this);
		delete obj;
		return true;
	}
	return false;
}

bool							Game::updateObj(game::Type type, game::Dir lDir, int id, int pos)
{
	//obj_type::iterator it = std::find_if(_objects.begin(), _objects.end(), AObject::predicate(id));

	//if (it != _objects.end())
	//{
	//	(*it)->update(lDir, pos);
	//	return true;
	//}
	//else
	//	return (addObj(type, id, pos));
	return (true);
}

bool							Game::addObj(game::Type type, int id, int pos)
{
	//AObject						*obj;

	//if ((obj = Factory::getInstance().createObject(type, id, pos, requestCode::game::client::EAST)) != NULL)
	//{
	//	_objects.push_back(obj);
	//	return true;
	//}
	//return false;
	return (true);
}

void							Game::cleanGame()
{
	for (obj_map_type::iterator it = _objects.begin(); it != _objects.end();)
	{
			ObjectMover	*obj = it->second;
#if defined(DEBUG)
			std::cout << &obj->getEntity() << std::endl;
#endif
			it = _objects.erase(it);
			delete obj;
	}
	if (_gameWindow->isOpen())
		_gameWindow->clear();
	AudioManager::getInstance().stop(AGAME_MUSIC);
}

void	Game::elem(const ARequest *req)
{
  //const ElemRequest	*elem = dynamic_cast<const ElemRequest *>(req);

  //updateObj(elem->type(), elem->dir(), elem->ID(), elem->pos());
}

void	Game::death(const ARequest *req)
{
  //const DeathRequest	*death = dynamic_cast<const DeathRequest *>(req);

  //delObj(death->ID());
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
 // _inGame = false;
}

void	Game::loose(const ARequest *req)
{
  (void)req;
  _layerManager.enableLayer(LLOOSE);
  AudioManager::getInstance().play(AGAME_OVER);
//  _inGame = false;
}

void	Game::nextStage(const ARequest *req)
{
  (void)req;
  _layerManager.enableLayer(LNEXSTAGE);
  AudioManager::getInstance().play(ANEXT_STAGE);
}

Game::Game(sf::RenderWindow *gameWindow, sf::Event *event) : _layerManager(gameWindow)
{
	ObjectFactory::getInstance().init(&_textureManager);
	_gameWindow = gameWindow;
	_event = event;
	_idPlayer = 1;

	_map[requestCode::game::ELEM] = &Game::elem;
	_map[requestCode::game::DEATH] = &Game::death;
	_map[requestCode::game::BUFF] = &Game::buff;
	_map[requestCode::game::SCORE] = &Game::score;
	_map[requestCode::game::VICTORY] = &Game::victory;
	_map[requestCode::game::LOOSE] = &Game::loose;
	_map[requestCode::game::NEXTSTAGE] = &Game::nextStage;
}
