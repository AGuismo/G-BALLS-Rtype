//
// Window.cpp for Window in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 11:37:38 2013 brigno
// Last update Tue Nov  5 03:21:38 2013 brigno
//

#include	"MenuWindow.hh"
#include	"Background.hh"
#include	"Image.hh"
#include	"AWidget.hh"
#include	"Text.hh"
#include	"TextArea.hh"
#include	"Button.hh"
#include	"Interface.hh"
#include	"Network.hh"

MenuWindow::MenuWindow(const std::string &name, int width, int height, Network *network):
  _status(CONTINUE), _objectFocus(0), _objectHover(0), _network(network)
{
  Text *tmp = new Text("Font/NEUROPOL.ttf", "LoginText", this->_event, sf::Vector2i(518, 370), sf::Vector2i(510, 375), sf::Vector2i(750, 405), 12, true);
  Text *tmp2 = new Text("Font/NEUROPOL.ttf", "PasswordText", this->_event, sf::Vector2i(518, 470), sf::Vector2i(510, 475), sf::Vector2i(755, 505), 12, false);

  this->_window.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
  this->_window.setVerticalSyncEnabled(true);
  this->_window.setFramerateLimit(25);
  this->_window.setKeyRepeatEnabled(false);
  this->_backgroundPtr = new Background("Images/background1.png", "Images/background2.png");
  this->_listImage.push_back(new Image("Images/title.png", sf::Vector2i(380, 50)));
  this->_listImage.push_back(new Image("Images/form.png", sf::Vector2i(390, 180)));
  this->_listWidget.push_back(new TextArea(this->_event, "LoginArea", *tmp, sf::Vector2i(470, 340), sf::Vector2i(510, 375), sf::Vector2i(750, 405)));
  this->_listWidget.push_back(new TextArea(this->_event, "PasswordArea", *tmp2, sf::Vector2i(470, 440), sf::Vector2i(510, 475), sf::Vector2i(755, 505)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new Button(this->_event, "EnterButton", "Images/Enter.png", "Images/EnterHover.png", "Images/EnterFocus.png", sf::Vector2i(490, 550), sf::Vector2i(500, 560), sf::Vector2i(630, 595), CHANGE_SCR));
  this->_listWidget.push_back(new Button(this->_event, "ExitButton", "Images/Exit.png", "Images/ExitHover.png", "Images/ExitFocus.png", sf::Vector2i(650, 550), sf::Vector2i(655, 560), sf::Vector2i(785, 595), EXIT));
}

MenuWindow::~MenuWindow()
{
}

void	MenuWindow::setDraw()
{
  this->_backgroundPtr->scroll();
}

void	MenuWindow::draw()
{
  widget_list::iterator	it;
  image_list::iterator	itImg;

  this->_window.draw(this->_backgroundPtr->getFirstBackground());
  this->_window.draw(this->_backgroundPtr->getSecondBackground());
  for (itImg = this->_listImage.begin(); itImg != this->_listImage.end(); itImg++)
    this->_window.draw((*itImg)->getImage());
  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    (*it)->draw(this->_window);
  this->_window.display();
}

AWidget	*MenuWindow::returnMouseFocus(float x, float y)
{
  widget_list::iterator	it;

  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    {
    if ((*it)->isFocus(sf::Vector2i(x, y)) == true)
	return *it;
    }
  return (0);
}

void	MenuWindow::catchEvent()
{
  while (this->_window.pollEvent(this->_event))
    {
      if (this->_status == CHANGE_SCR)
	{
	  std::string tmp = dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"))->getText();
	  std::string tmp2 = dynamic_cast<Text*>(Interface::getInstance().getWidget("PasswordText"))->getText();
	  std::cout << tmp << std::endl;
	  std::cout << tmp2 << std::endl;
	  this->_window.close();
	  /*------ APPELLER LE SCREEN SUIVANT ---------*/
	}
      else if (this->_status == EXIT)
	this->_window.close();
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
	    this->_status = this->_objectFocus->onFocus();
	  break;
	case sf::Event::MouseMoved:
	  if (this->_objectHover != 0)
	    this->_objectHover->stopHover();
	  this->_objectHover = returnMouseFocus(this->_event.mouseMove.x, this->_event.mouseMove.y);
	  if (this->_objectHover != 0)
	    this->_objectHover->onHover();
	  std::cout << "x: " << this->_event.mouseMove.x << ", y : " << this->_event.mouseMove.y << std::endl;
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

void	MenuWindow::run()
{
  while (this->_window.isOpen())
    {
      this->catchEvent();
      this->setDraw();
      this->draw();
    }
}

Background		*MenuWindow::getBackgroundPtr()
{
  return (this->_backgroundPtr);
}

const MenuWindow::image_list	&MenuWindow::getListImage() const
{
  return (this->_listImage);
}

const MenuWindow::widget_list	&MenuWindow::getListWidget() const
{
  return (this->_listWidget);
}
