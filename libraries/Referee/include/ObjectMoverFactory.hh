#ifndef OBJECT_MOVER_FACTORY
# define	OBJECT_MOVER_FACTORY

# include	<map>
# include	"Entity.hh"

class	Position;
class	ObjectMover;

class			ObjectMoverFactory
{
public:
  ObjectMover		*createObject(const entity::Type &type, unsigned short id, const Position &pos);

public:
  static ObjectMoverFactory	&getInstance(void);

private:

  ObjectMoverFactory();
  ~ObjectMoverFactory();

private:
  ObjectMoverFactory(const ObjectMoverFactory &);
  ObjectMoverFactory		operator=(const ObjectMoverFactory &);
};

#endif // !OBJECT_MOVER_FACTORY
