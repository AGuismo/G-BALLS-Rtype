#ifndef ENTITYFACTORY_H_
# define ENTITYFACTORY_H_

# include	<map>
# include	"IEntityFactory.hh"

class EntityFactory : public IEntityFactory
{
public:
  EntityFactory();
  virtual ~EntityFactory();

  Entity	*createEntityByType(rtype::protocol::game::FullType entityType) const;
  Entity	*createEntityByType(rtype::protocol::game::MajorType entityMajorType) const;


private:
  EntityFactory(EntityFactory const&);
  EntityFactory& operator=(EntityFactory const&);

private:
  std::map<rtype::protocol::game::FullType, Entity *>	_correspondanceEntityTypeMap;
};

#endif /* ENTITYFACTORY_H_ */
