//
// Window.cpp for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:37:38 2013 brigno
// Last update Mon Nov  4 13:35:23 2013 brigno
//

#include	"Window.hh"
#include	"Background.hh"
#include	"Image.hh"
#include	"AWidget.hh"
#include	"Text.hh"
#include	"TextArea.hh"
#include	"Button.hh"

Window::Window(const std::string &name, int width, int height)
{
  Text *tmp = new Text("Font/NEUROPOL.ttf", this->_event, sf::Vector2i(470, 340), sf::Vector2i(983, 519), 12, true);
  Text *tmp2 = new Text("Font/NEUROPOL.ttf", this->_event, sf::Vector2i(470, 440), sf::Vector2i(983, 657), 12, false);

  this->_window.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
  this->_window.setVerticalSyncEnabled(true);
  this->_window.setFramerateLimit(25);
  this->_window.setKeyRepeatEnabled(false);
  this->_backgroundPtr = new Background("Images/background1.png", "Images/background2.png");
  this->_listImage.push_back(new Image("Images/title.png", sf::Vector2i(380, 50)));
  this->_listImage.push_back(new Image("Images/form.png", sf::Vector2i(390, 180)));
  this->_listWidget.push_back(new TextArea(this->_event, *tmp, sf::Vector2i(470, 340), sf::Vector2i(750, 410)));
  this->_listWidget.push_back(new TextArea(this->_event, *tmp2, sf::Vector2i(470, 440), sf::Vector2i(750, 505)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new Button(this->_event, "Images/Enter.png", "Images/EnterHover.png", "Images/EnterFocus.png", sf::Vector2i(470, 600), sf::Vector2i(550, 600)));
  this->_listWidget.push_back(new Button(this->_event, "Images/Exit.png", "Images/ExitHover.png", "Images/ExitFocus.png", sf::Vector2i(600, 600), sf::Vector2i(700, 750)));
  this->_objectFocus = 0;
}

Window::~Window()
{
}

void	Window::setDraw()
{
  this->_backgroundPtr->scroll();
}

void	Window::draw()
{
  std::vector<AWidget*>::iterator	it;
  std::vector<Image*>::iterator itImg;

  this->_window.draw(this->_backgroundPtr->getFirstBackground());
  this->_window.draw(this->_backgroundPtr->getSecondBackground());
  for (itImg = this->_listImage.begin(); itImg != this->_listImage.end(); itImg++)
    this->_window.draw((*itImg)->getImage());
  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    (*it)->draw(this->_window);
  this->_window.display();
}

AWidget	*Window::returnMouseFocus(float x, float y)
{
  std::vector<AWidget*>::iterator	it;

  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    {
      if ((*it)->isFocus(sf::Vector2i(x, y)) == true)
	return *it;
    }
  return (0);
}

void	Window::catchEvent()
{
  while (this->_window.pollEvent(this->_event))
    {
      switch (this->_event.type)
	{
	case sf::Event::Closed:
	  this->_window.close();
	  break;
	case sf::Event::KeyPressed:
	  if (this->_event.key.code == sf::Keyboard::Escape)
	    this->_window.close();
	  break;
	case sf::Event::TextEntered:
	  if (this->_objectFocus != 0)
	    this->_objectFocus->onFocus();
	  break;
	case sf::Event::MouseButtonPressed:
	  if (this->_objectFocus != 0)
	    this->_objectFocus->stopFocus();
	  this->_objectFocus = returnMouseFocus(this->_event.mouseButton.x, this->_event.mouseButton.y);
	  if (this->_objectFocus != 0)
	    this->_objectFocus->onFocus();
	  break;
	case sf::Event::MouseMoved:
	  if (this->_objectFocus != 0)
	    {
	      this->_objectFocus->stopHover();
	      this->_objectFocus = returnMouseFocus(this->_event.mouseMove.x, this->_event.mouseMove.y);
	      if (this->_objectFocus != 0)
		this->_objectFocus->onHover();
	    }
	  std::cout << "x : " << this->_event.mouseMove.x << " y : " << this->_event.mouseMove.y << std::endl;
	  break;
	case sf::Event::MouseButtonReleased:
	  if (this->_objectFocus != 0)
	    {
	      this->_objectFocus->stopFocus();
	      this->_objectFocus = returnMouseFocus(this->_event.mouseButton.x, this->_event.mouseButton.y);
	      if (this->_objectFocus != 0)
		this->_objectFocus->stopFocus();
	    }
	  break;
	default:
	  break;
	}
    }
}

void	Window::launchWindow()
{
  while (this->_window.isOpen())
    {
      this->catchEvent();
      this->setDraw();
      this->draw();
    }
}

Background		*Window::getBackgroundPtr()
{
  return (this->_backgroundPtr);
}

const std::vector<Image*>	&Window::getListImage() const
{
  return (this->_listImage);
}

const std::vector<AWidget*>	&Window::getListWidget() const
{
  return (this->_listWidget);
}
