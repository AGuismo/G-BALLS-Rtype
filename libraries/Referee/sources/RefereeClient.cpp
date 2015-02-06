#include	"Scenario.hh"
#include	"RefereeClient.hh"

RefereeClient::RefereeClient():
  _scenario(0)
{
}

RefereeClient::~RefereeClient()
{
  delete _scenario;
}

void	RefereeClient::loadScenario(const Scenario &scenarioToLoad)
{
  const std::vector<Player>	&players = scenarioToLoad.getPlayers();

  if (_scenario != 0)
    delete _scenario;
  _scenario = new Scenario(scenarioToLoad);
  for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it)
    _map.addEntity(*it);
}

void	RefereeClient::update()
{
  if (_scenario == 0)
    throw UnloadedScenarioException();

}

const GameMap	&RefereeClient::getMap() const
{
  return (_map);
}
