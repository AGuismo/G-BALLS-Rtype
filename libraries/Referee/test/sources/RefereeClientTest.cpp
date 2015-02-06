#include	<gtest/gtest.h>
#include	"RefereeClient.hh"
#include	"GameMap.hh"
#include	"Scenario.hh"

class	RefereeClientTest: public ::testing::Test
{
protected:
  void	SetUp()
  {
    referee = new RefereeClient;
  }

  void	TearDown()
  {
    delete referee;
  }

  RefereeClient	*referee;
  Scenario	aScenario;
};

TEST_F(RefereeClientTest, whenLoadScenarioUndoneBeforeUpdateExpectThrow)
{
  EXPECT_THROW(referee->update(), IReferee::UnloadedScenarioException);
}

TEST_F(RefereeClientTest, whenLoadScenarioDoneBeforeUpdateExpectNoThrow)
{
  referee->loadScenario(aScenario);
  EXPECT_NO_THROW(referee->update());
}

TEST_F(RefereeClientTest, whenILoadAScenarioWithOnePlayerAndIGetMapExpectedPlayerInMap)
{
  aScenario.addPlayer(Player(5, Position(5, 7)));

  referee->loadScenario(aScenario);

  const GameMap	&map = referee->getMap();
  EXPECT_NO_THROW(map.findEntityByID(5));
}

TEST_F(RefereeClientTest, whenMovePlayerOutsideMapExpectedPlayerDead)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenMovePlayerInsideMapExpectedPlayerAlive)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenMovePlayerTwiceInIntervalExpectedJustMoveOnce)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenAllPlayersAreDeadExpectedGameFinished)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenFireExpectedPlayerStillAlive)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenFireSuccessExpectedMissileInMap)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenFireTwiceInIntervalExpectedJustOneMissileInMap)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenReceiveIncomingElemRequestTreatItProperlyOnUpdate)
{
  FAIL();
}

TEST_F(RefereeClientTest, whenReceiveIncomingDeathRequestTreatItProperlyOnUpdate)
{
  FAIL();
}

TEST_F(RefereeClientTest, OnOnePlayerPartywhenReceiveIncomingDeathRequestForMyPlayerOnUpdateExpectedGameFinished)
{
  FAIL();
}

