#include	"ProtocolTypes.hh"

namespace	entity
{
  typedef rtype::protocol::game::MajorType	MajorType;
  typedef rtype::protocol::game::MinorType	MinorType;
  typedef rtype::protocol::game::FullType	FullType;

  enum Major : MajorType
    {
	NONE,
	PLAYER,
	BOSS,
	MOBS,
	WALL,
	BONUS,
	MISSILE
    };

  union	Type
  {
    struct
    {
      MajorType	maj;
      MinorType	min;
    }		desc;
    FullType	full;
  };

}
