#include	<iostream>
#include	"Application.hh"
#include	"GameException.hh"
#include	"MenuException.hh"
#include	"LoaderException.hh"

Application::Application()
{
  try
    {
      _menuManager.initialize(); // Load the menu
      _gameManager.initialize(); // Load the game system
      _botLoaderManager.initialize(); // Load the bot-Loader
    }
  catch (const menu::Exception &e) // Menu loader exception
    {
      std::cerr << "In Application::run(), catch: " << e.what() << std::endl;
      throw Application::InitExcept("Application Init fail");
    }
  catch (const game::Exception &e) // game loader exception
    {
      std::cerr << "In Application::run(), catch: " << e.what() << std::endl;
      throw Application::InitExcept("Application Init fail");
    }
  catch (const botLoader::Exception &e) // Catch Bot loader exception
    {
      std::cerr << "In Application::run(), catch: " << e.what() << std::endl;
      throw Application::InitExcept("Application Init fail");
    }
}

Application::~Application()
{

}

void	Application::run()
{
  std::cout << "Start Application::Run" << std::endl;
  _gameManager.run();
  _botLoaderManager.run();
  _menuManager.run();
}


///////////////////////
//  Exception Class  //
///////////////////////
Application::InitExcept::InitExcept(const std::string &msg) throw() :
  _what(msg)
{

}

Application::InitExcept::InitExcept (const Application::InitExcept &src) throw() :
  _what(src._what)
{

}

Application::InitExcept::~InitExcept() throw()
{

}

Application::InitExcept& Application::InitExcept::operator=(Application::InitExcept const &src) throw()
{
  if (&src != this)
    {
      _what = src._what;
    }
  return (*this);
}

const char	*Application::InitExcept::what() const throw()
{
  return (_what.c_str());
}
