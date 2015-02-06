#ifndef REFEREECLIENT_H_
# define REFEREECLIENT_H_

# include	"IReferee.hh"
# include	"GameMap.hh"

class RefereeClient : public IReferee
{
public:
  RefereeClient();
  virtual ~RefereeClient();

public:
  void	update();
  void	loadScenario(const Scenario &scenario);

  const GameMap	&getMap() const;

private:
  RefereeClient(RefereeClient const&);
  RefereeClient& operator=(RefereeClient const&);

  Scenario	*_scenario;
  GameMap	_map;
};


#endif /* REFEREECLIENT_H_ */
