#include		<SFML/Audio.hpp>
#include		"AObject.h"
#include		"game.h"
#include		"Layer.h"
#include		<algorithm>
#include		"Timer.h" // A VIRER

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

	if (!_soundManager.addSound(42, new std::string("./Sounds/BydosSimpleLaser.wav")))
		std::cerr << "go die motherfucker" << std::endl;

	return true;
}
// 	Layer(int id, sf::Texture *lText, sf::Vector2f *lInit, sf::Vector2f *lReset, sf::Vector2f *lLim, sf::Vector2f *lInc, Timer *lT, sf::RenderWindow *gWindow, bool lEn);

static void playtest()
{
	sf::Sound					*sound = new sf::Sound;
	sf::SoundBuffer				*buffer = new sf::SoundBuffer; // ce buffer est local à la fonction, il sera détruit...

	if (buffer->loadFromFile("./Sounds/Lepi.ogg"))
	{
		std::cout << "playing" << std::endl;
	sound->setBuffer(*buffer);
	sound->play();
	//sound.setLoop(true);
	}
	
/*	sf::Music					*music = new sf::Music();

	if (music->openFromFile("./Sounds/Lepi.ogg"))
	{
		std::cout << "playing2" << std::endl;
		music->play();
		music->setLoop(true);
	}*/
}

void							Game::run(void)
{
	_gameWindow->setFramerateLimit(25);

	addObj(PLAYER1, 42, 100);
	addObj(PLAYER2, 20, 40);
	addObj(PLAYER3, 77, 10);
	addObj(PLAYER4, 48, 200);
	addObj(SBYDOS1, 455, 140);

	Timer						test(new sf::Time(sf::seconds(5.25)));


/*	Layer						*testl = new Layer(42, _textureManager.getTexture(LAYER1), new sf::Vector2f(1280.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(-1280.0f, 0.0f), new sf::Vector2f(4.0f, 0.0f), NULL, _gameWindow, true);
	Layer						*test2 = new Layer(42, _textureManager.getTexture(LAYER1), new sf::Vector2f(1280.0f, 0.0f), new sf::Vector2f(1280.0f, 0.0f), new sf::Vector2f(-1280.0f, 100.0f), new sf::Vector2f(4.0f, 0.0f), NULL, _gameWindow, true);
	Layer						*test3 = new Layer(42, _textureManager.getTexture(LAYER2), new sf::Vector2f(1280.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(-1280.0f, 400.0f), new sf::Vector2f(0.0f, -1.0f), NULL, _gameWindow, true);
	Layer						*test4 = new Layer(43, _textureManager.getTexture(LAYER3), new sf::Vector2f(1280.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(-1280.0f, 0.0f), new sf::Vector2f(2.0f, 0.0f), NULL, _gameWindow, true);
	Layer						*test5 = new Layer(42, _textureManager.getTexture(LAYER4), new sf::Vector2f(1280.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), new sf::Vector2f(-1280.0f, 0.0f), new sf::Vector2f(0.0f, 0.0f), &test, _gameWindow, false);
	*/

/*	sf::Sound					sound;
	sf::SoundBuffer				buffer; // ce buffer est local à la fonction, il sera détruit...

	if (buffer.loadFromFile("./Sounds/DeepSpace.ogg"))
	{
		sound.setBuffer(buffer);
		sound.play();
		sound.setLoop(true);
	}*/

/*	sf::Music					sound;
	sf::SoundBuffer				buffer; // ce buffer est local à la fonction, il sera détruit...

	if (sound.openFromFile("./Sounds/DeepSpace.ogg"))
	{
//		sound.setBuffer(buffer);
		sound.play();
		sound.setLoop(true);
	}*/

/*	sf::Sound					*sound2 = new sf::Sound;
	sf::SoundBuffer				buffer2; // ce buffer est local à la fonction, il sera détruit...

	sf::SoundBuffer				buffer3; // ce buffer est local à la fonction, il sera détruit...

	if (buffer2.loadFromFile("./Sounds/Lepi.ogg"))
	{
		buffer3 = buffer2;
		delete buffer2;
		sound2.setBuffer(buffer3);
		sound2.play();
		sound2.setLoop(true);
	}*/

	_soundManager.playSound(42);
	playtest();
	while (_gameWindow->isOpen())
	{
		if (test.isEnded())
		{
			//std::cout << "timer ended" << std::endl;
			// test.restart();
		}

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
				case sf::Keyboard::Space:
/*					if ((sound.getStatus() == sf::SoundSource::Paused) || (sound.getStatus() == sf::SoundSource::Stopped))
						sound.play();
					else if (sound.getStatus() == sf::SoundSource::Playing)
						sound.pause();*/
					break;
				case sf::Keyboard::Up:
					updateObj(42, Up);
					break;
				case sf::Keyboard::Down:
					updateObj(42, Down);
					//test5->enable();
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
/*		testl->update();
		testl->draw();
		test2->update();
		test2->draw();
		test3->update();
		test3->draw();
		test4->update();
		test4->draw();
		test5->update();
		test5->draw();*/
		/*		if (bg1 == -1280)
			bg1 = 1280;
		if (bg2 == -1280)
			bg2 = 1280;

		_bgImg1.setPosition(bg1, 0);*/
		//_bgImg2.setPosition(0, 0);
		//_gameWindow->draw(_bgImg2);
		//_gameWindow->draw(_bgImg2);
		_layerManager.upDraw();
		draw();
//		sf::sleep(sf::seconds(1));

		_gameWindow->display();
/*		bg1 -= 1;
		bg2 -= 1;*/
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

Game::Game(sf::RenderWindow *gameWindow, sf::Event *event) : _factory(gameWindow, &_textureManager), _layerManager(gameWindow, &_textureManager), _soundManager()
{
	_gameWindow = gameWindow;
	_event = event;
	_idPlayer = 42;
}
