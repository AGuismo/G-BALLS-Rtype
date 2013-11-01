#include	"Env.hh"

namespace rtype
{
  Env		Env::getInstance()
  {
    static Env	*singleton = 0;

    if (singleton == 0)
      singleton = new Env();
    return (*singleton);
  }

  Env::Env()
  {

}

  Env::~Env()
  {

}
}
