#include	"RefereeClient.hh"

RefereeClient::RefereeClient()
{
}

RefereeClient::~RefereeClient()
{
}

void	RefereeClient::loadScenario(const Scenario &scenario)
{
}

void	RefereeClient::update()
{
  throw UnloadedScenarioException();
}
