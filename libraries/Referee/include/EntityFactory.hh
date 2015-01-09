#ifndef ENTITY_FACTORY
# define	ENTITY_FACTORY

# include	<map>
# include	"Entity.hh"

class	Position;
class	ObjectMover;

class					EntityFactory
{
public:
	ObjectMover			*createObject(const Entity::type &type, unsigned short id, const Position &pos);

public:
	static EntityFactory		&getInstance(void);

private:

	EntityFactory();
	~EntityFactory();

private:
	EntityFactory(const EntityFactory &);
	EntityFactory			operator=(const EntityFactory &);
};

#endif // !ENTITY_FACTORY
