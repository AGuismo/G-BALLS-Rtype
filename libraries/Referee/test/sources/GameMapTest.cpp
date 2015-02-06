#include	<gtest/gtest.h>
#include	"GameMap.hh"
#include	"Entity.hh"
#include	"Player.hh"
#include	"Missile.hh"

using namespace rtype::protocol;

class GameMapTest: public ::testing::Test
{
public:
  static const game::ID	ENTITY_ID_FIRST;
  static const game::ID	ENTITY_ID_SECOND;
  static const game::ID	ENTITY_ID_THIRD;

protected:
  Player	aPlayer;
  Player	anotherPlayer;
  Missile	aMissile;

  void	SetUp()
  {
    gameMap = new GameMap;
    aPlayer.setID(ENTITY_ID_FIRST);
    anotherPlayer.setID(ENTITY_ID_SECOND);
    aMissile.setID(ENTITY_ID_THIRD);
  }

  void	TearDown()
  {
    delete gameMap;
  }

  GameMap	*gameMap;
};

const game::ID	GameMapTest::ENTITY_ID_FIRST = 7;
const game::ID	GameMapTest::ENTITY_ID_SECOND = 15;
const game::ID	GameMapTest::ENTITY_ID_THIRD = 12;


TEST_F(GameMapTest, whenCreateMapItsEmpty)
{
  ASSERT_EQ(gameMap->begin(), gameMap->end());
}

TEST_F(GameMapTest, whenAddOneEntityItExistsOnMap)
{
  gameMap->addEntity(aPlayer);

  ASSERT_TRUE(gameMap->entityExists(aPlayer.getID()));
}

TEST_F(GameMapTest, whenAddOneEntityAndAddTheSameThrowError)
{
  gameMap->addEntity(aPlayer);
  ASSERT_THROW(gameMap->addEntity(aPlayer), GameMap::EntityAlreadyExistException);
}

TEST_F(GameMapTest, whenAddTwoEntitiesTheyExistOnMap)
{
  gameMap->addEntity(aPlayer);
  gameMap->addEntity(anotherPlayer);

  ASSERT_TRUE(gameMap->entityExists(aPlayer.getID()));
  ASSERT_TRUE(gameMap->entityExists(anotherPlayer.getID()));
}

TEST_F(GameMapTest, whenAddOneEntityCanFindAndRetreiveIt)
{
  gameMap->addEntity(aPlayer);
  Entity	*entityInMap = gameMap->findEntityByID(aPlayer.getID());

  ASSERT_EQ(ENTITY_ID_FIRST, entityInMap->getID());
}

TEST_F(GameMapTest, whenFindAnEntityThatDontExistThrowException)
{
  ASSERT_THROW(gameMap->findEntityByID(aPlayer.getID()), GameMap::EntityDontExistException);
}

TEST_F(GameMapTest, whenDeleteAnEntityThatExistInMapDontExistAnymore)
{
  gameMap->addEntity(aPlayer);
  gameMap->delEntity(aPlayer.getID());

  ASSERT_FALSE(gameMap->entityExists(aPlayer.getID()));
}

TEST_F(GameMapTest, whenDeleteAnEntityThatDontExistInMapThrow)
{
  ASSERT_THROW(gameMap->delEntity(aPlayer.getID()), GameMap::EntityDontExistException);
}
