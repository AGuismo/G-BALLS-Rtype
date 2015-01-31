#include		<SFML/Audio.hpp>
#include		<SFML/Network.hpp>
#include		<algorithm>
#include		"Game.hh"
#include		"InfosUser.hh"

// Physics
#include		"Timer.hh"
#include		"EventManager.hh"
#include		"Animation.hh"
#include		"Layer.hh"
#include		"TextureManager.hh"
#include		"Missile.hh"

// Network
#include		"NetworkManager.hh"

// Protocol
#include		"RequestCode.hh"
#include		"AliveRequest.hh"
#include		"LeaveRequest.hh"
#include		"ElemRequest.hh"

using namespace requestCode::game;

Game::~Game()
{
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

  t.push_back(Texture("./Images/r-typesheet1.png", game::TextureManager::Key(Entity::createType(Entity::MISSILE, 1)), sf::IntRect(498, 210, 32, 16)));
  t.push_back(Texture("./Images/r-typesheet1.png", game::TextureManager::Key(Entity::createType(Entity::MISSILE, 2)), sf::IntRect(466, 240, 64, 20)));
  t.push_back(Texture("./Images/r-typesheet1.png", game::TextureManager::Key(Entity::createType(Entity::MISSILE, 3)), sf::IntRect(335, 274, 96, 24)));
  t.push_back(Texture("./Images/r-typesheet1.png", game::TextureManager::Key(Entity::createType(Entity::MISSILE, 4)), sf::IntRect(271, 307, 128, 28)));

  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 1), sf::IntRect(10, 12, 42, 48)));
  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 2), sf::IntRect(76, 12, 42, 48)));
  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 3), sf::IntRect(142, 12, 42, 48)));
  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 4), sf::IntRect(208, 12, 42, 48)));
  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 5), sf::IntRect(274, 12, 42, 48)));
  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 6), sf::IntRect(340, 12, 42, 48)));
  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 7), sf::IntRect(406, 12, 42, 48)));
  t.push_back(Texture("./Images/r-typesheet5.png", game::TextureManager::Key(Entity::createType(Entity::MOBS, 1), Animation::ACT_DEFAULT, 8), sf::IntRect(472, 12, 42, 48)));

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

  //_objects[0x4242] = ObjectFactory::getInstance().createObject(me.getType(), me.getID(), me.getPosition());;
  //_objects[5] = ObjectFactory::getInstance().createObject(Entity::createType(Entity::MOBS, 1), 5, Position(800, 500, Position::WEST));
  return true;
}

void			Game::onMyselfMove(Position::dir direction)
{
  _referee.acceptMove(direction);
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

void			Game::onEscape(sf::Keyboard::Key key, Game *self)
{
  self->_onGame = false;
}

void			Game::onFire(sf::Keyboard::Key key, Game *self)
{
  if (!self->_referee.acceptFire())
    return;
  //for (std::vector<Missile>::iterator it = createdMissiles.begin(); it != createdMissiles.end(); ++it)
  //	self->_objects[it->getID()] = ObjectFactory::getInstance().createObject(it->getType(), it->getID(), it->getPosition());
}

void							Game::sendPlayerInfo() const
{
  Player						myPlayer;
  Referee::missile_list_type	playerMissiles;
  network::Manager			&networkManager = network::Manager::getInstance();

  if (!_referee.playerInformations(myPlayer, playerMissiles))
    return;
  networkManager.sendRequest(ElemRequest::create<Player>(myPlayer, InfosUser::getInstance().authenticate.id, 0), network::Manager::UDP);
  for (Referee::missile_list_type::const_iterator it = playerMissiles.begin();
       it != playerMissiles.end(); ++it)
  {
    networkManager.sendRequest(ElemRequest::create<Missile>(*it, InfosUser::getInstance().authenticate.id, 0), network::Manager::UDP);
  }
}

void							Game::run(void)
{
  Timer						_playerBlastLock(sf::seconds(2.0f));
  Timer						_aliveRequest(sf::seconds(0.75f));
  Timer						_lostConnection(sf::seconds(6.0f));
  EventManager				ev(*_event);
  std::vector<unsigned short>	toDelete;
  //ARequest					*req;

  //_gameWindow->setFramerateLimit(25);
  _gameWindow->setKeyRepeatEnabled(true);
  ev.registerKey(sf::Keyboard::Left, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveLeft, this), sf::seconds(0.25f));
  ev.registerKey(sf::Keyboard::Right, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveRight, this), sf::seconds(0.25f));
  ev.registerKey(sf::Keyboard::Up, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveUp, this), sf::seconds(0.25f));
  ev.registerKey(sf::Keyboard::Down, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onMoveDown, this), sf::seconds(0.25f));
  ev.registerKey(sf::Keyboard::Space, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onFire, this), sf::seconds(0.5f));
  ev.registerKey(sf::Keyboard::Escape, new EventManager::Callback<sf::Keyboard::Key, Game *>(&Game::onEscape, this));

  network::Manager::getInstance().setUdp(sf::IpAddress(InfosUser::getInstance().authenticate.addressIp), InfosUser::getInstance().authenticate.portUDP);
  _referee.setPlayerID(InfosUser::getInstance().authenticate.id);
  AudioManager::getInstance().play(AGAME_MUSIC);
  _onGame = true;

  while (_gameWindow->isOpen() && _onGame)
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
    ev.update();

    /* Get request from MasterReferee, send it to referee and apply to objects(Mover) */

    _referee.update(toDelete);
    if (!toDelete.empty())
    {
      for (std::vector<unsigned short>::iterator it = toDelete.begin(); it != toDelete.end(); ++it)
      {
	if (*it == _referee.getMyPlayer().getID())
	{
	  _onGame = false;
	  break;
	}
	_objects.erase(*it);
      }
    }

    draw();

    while (true)
    {
      std::pair<network::Manager::SendType, ARequest *>	message = network::Manager::getInstance().recvRequestType();

      if (message.first != network::Manager::NONE)
      {
	std::cout << "Receive request of type: " << message.second->code() << std::endl;
	_referee.recvRequestFromServer(*message.second);
	delete message.second;
	_lostConnection.restart();
      }
      else
	break;
    }

    if (_aliveRequest.isEnded())
    {
      network::Manager::getInstance().sendRequest(AliveRequest(InfosUser::getInstance().authenticate.id, 0), network::Manager::UDP); // 0 => stamp
      sendPlayerInfo();
      _aliveRequest.restart();
    }

    //if (_lostConnection.isEnded())
    //{
    //	network::Manager::getInstance().sendRequest(LeaveRequest(InfosUser::getInstance().authenticate.id, 0), network::Manager::UDP);
    //	_onGame = false;
    //}
  }
  network::Manager::getInstance().closeUdp();
  cleanGame();
  _gameWindow->close();
}

void		Game::draw()
{
  _gameWindow->clear();
  _layerManager.upDraw();
  drawObjects();
  _gameWindow->display();
}

Animation	&Game::createAnimation(const Entity &entity)
{
  Animation		anim(entity.getType());
  const game::TextureManager::texture_map_type	textures = _textureManager.getTextureByType(entity.getType());

  for (game::TextureManager::texture_map_type::const_iterator it = textures.begin();
       it != textures.end(); ++it)
    anim.addFrame(it->first.action, it->second);
  _objects[entity.getID()] = anim;
  return (_objects[entity.getID()]);
}

Animation	&Game::getAnimation(const Entity &current)
{
  obj_map_type::iterator	itAnim = _objects.find(current.getID());

  return (itAnim == _objects.end() ? createAnimation(current) : itAnim->second);
}

void		Game::drawObjects(void)
{
  const Referee::entity_set_type	&map = _referee.getMap();

  for (Referee::entity_set_type::const_iterator it = map.begin(); it != map.end(); ++it)
  {
    const Entity					*current = *it;
    Animation						&animation = getAnimation(*current);
    const sf::Texture				&texture = animation.getFrame();
    sf::Sprite						sprite(texture);

    sprite.setPosition(PositionToVector2f(current->getPosition()));
    _gameWindow->draw(sprite);
  }
}

bool						Game::delObj(int id)
{
  obj_map_type::iterator		it = _objects.find(id);

  if (it != _objects.end())
  {
    _objects.erase(it);
    //obj->onDestruction(*this);
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
  _objects.erase(_objects.begin(), _objects.end());
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

sf::Vector2f	Game::PositionToVector2f(const Position &pos)
{
  return (sf::Vector2f(pos.x, pos.y));
}
Game::Game(sf::RenderWindow *gameWindow, sf::Event *event) : _layerManager(gameWindow)
{
  _gameWindow = gameWindow;
  _event = event;

  _map[requestCode::game::ELEM] = &Game::elem;
  _map[requestCode::game::DEATH] = &Game::death;
  _map[requestCode::game::BUFF] = &Game::buff;
  _map[requestCode::game::SCORE] = &Game::score;
  _map[requestCode::game::VICTORY] = &Game::victory;
  _map[requestCode::game::LOOSE] = &Game::loose;
  _map[requestCode::game::NEXTSTAGE] = &Game::nextStage;
}
