#ifndef IREFEREE_H_
# define IREFEREE_H_

# include	<stdexcept>

class	Scenario;

class	IReferee
{
public:
  virtual void	loadScenario(const Scenario &scenario) = 0;
  virtual void	update() = 0;


  class UnloadedScenarioException : public std::exception
  {
  public:
    virtual const char	*what() const throw()
    {
      return ("No scenario was loaded. Referee can't Update.");
    }
  };

};




#endif /* IREFEREE_H_ */
