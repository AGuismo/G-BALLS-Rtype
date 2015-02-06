#include	<gtest/gtest.h>
#include	"RefereeClient.hh"
#include	"Scenario.hh"

class	RefereeClientTest: public ::testing::Test
{

  void	SetUp()
  {
  }




};

TEST_F(RefereeClientTest, whenLoadScenarioUndoneBeforeUpdateExpectThrow)
{
  RefereeClient	referee;

  EXPECT_THROW(referee.update(), IReferee::UnloadedScenarioException);
}

TEST_F(RefereeClientTest, whenLoadScenarioDoneBeforeUpdateExpectNoThrow)
{
  RefereeClient	referee;
  Scenario	aScenario;

  referee.loadScenario(aScenario);
  EXPECT_NO_THROW(referee.update());
}
