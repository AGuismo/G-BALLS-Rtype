#include	<stdexcept>
#include	"ProtocolTypes.hh"

class	Entity;

class	IEntityFactory
{
public:
  virtual ~IEntityFactory() {};

  virtual Entity	*createEntityByType(rtype::protocol::game::FullType entityType) const = 0;
  virtual Entity	*createEntityByType(rtype::protocol::game::MajorType entityType) const = 0;

  class	WrongEntityTypeException : public std::exception
  {
    const char	*what() const throw()
    {
      return ("You're trying to pass an invalid Entity type.");
    }
  };

};
