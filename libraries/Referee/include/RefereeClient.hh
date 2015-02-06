#ifndef REFEREECLIENT_H_
# define REFEREECLIENT_H_

# include	"IReferee.hh"

class RefereeClient : public IReferee
{
public:
  RefereeClient();
  virtual ~RefereeClient();

public:
  void	update();
  void	loadScenario(const Scenario &scenario);

private:
  RefereeClient(RefereeClient const&);
  RefereeClient& operator=(RefereeClient const&);
};


#endif /* REFEREECLIENT_H_ */
