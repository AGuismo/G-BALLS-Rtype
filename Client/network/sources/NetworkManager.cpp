#include	"NetworkManager.hh"

namespace	network
{
  Manager::Manager() :
    _th(Func::Bind(&Manager::routine, this))
  {

  }

  Manager::~Manager()
  {

  }

  int	Manager::routine()
  {
	  return (0);
  }
}
