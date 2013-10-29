//
// Window.cpp for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:37:38 2013 brigno
// Last update Fri Oct 25 18:02:33 2013 brigno
//

#include	"Window.hh"

Window::Window(const std::string &name, int width, int height)
{
  this->_window.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
  this->_window.setVerticalSyncEnabled(true);
  this->_window.setFramerateLimit(25);
  this->_window.setKeyRepeatEnabled(false);
  this->_backgroundPtr = new Background("Images/background.png", "Images/background2.png");
  this->_titlePtr = new Title("Images/title.png");
  this->_formPtr = new  Form("Images/form.png");
  this->_listWidget.push_back(new Text("Font/NEUROPOL.ttf", this->_event, sf::Vector2i(638, 518), sf::Vector2i(972, 581), 12, true, 1));
  this->_listWidget.push_back(new Text("Font/NEUROPOL.ttf", this->_event, sf::Vector2i(639, 660), sf::Vector2i(974, 724), 12, false, 2));
  this->_objectFocus = 0;
}

Window::Window(const std::string &name)
{
  this->_window.create(sf::VideoMode(1600, 900), name, sf::Style::Titlebar | sf::Style::Close);
  this->_window.setVerticalSyncEnabled(true);
  this->_window.setFramerateLimit(25);
  this->_backgroundPtr = new Background("Images/background.png", "Images/background2.png");
  this->_titlePtr = new Title("Images/title.png");
  this->_formPtr = new  Form("Images/form.png");
  this->_listWidget.push_back(new Text("Font/NEUROPOL.ttf", this->_event, sf::Vector2i(638, 518), sf::Vector2i(972, 581), 12, true, 1));
  this->_listWidget.push_back(new Text("Font/NEUROPOL.ttf", this->_event, sf::Vector2i(639, 660), sf::Vector2i(974, 724), 12, false, 2));
  this->_objectFocus = 0;
}

Window::~Window()
{
}

void	Window::setDraw()
{
  this->_formPtr->setPosition();
  this->_titlePtr->setPosition();
  this->_backgroundPtr->scroll();
}

void	Window::draw()
{
  std::vector<AWidget*>::iterator	it;

  this->_window.draw(this->_backgroundPtr->getFirstBackground());
  this->_window.draw(this->_backgroundPtr->getSecondBackground());
  this->_window.draw(this->_titlePtr->getTitle());
  this->_window.draw(this->_formPtr->getForm());
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
	  this->_objectFocus = returnMouseFocus(this->_event.mouseButton.x, this->_event.mouseButton.y);
	  break;
	case sf::Event::MouseMoved:
	  std::cout << "x : " << this->_event.mouseMove.x << " y : " << this->_event.mouseMove.y << std::endl;
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

Title			*Window::getTitlePtr()
{
  return (this->_titlePtr);
}

Form			*Window::getFormPtr()
{
  return (this->_formPtr);
}
