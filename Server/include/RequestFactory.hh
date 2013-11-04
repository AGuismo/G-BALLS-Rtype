#ifndef REQUESTFACTORY_H_
# define REQUESTFACTORY_H_

# include	<map>
# include	"ARequest.hh"
# include	"RequestCode.hh"
# include	"Bind.hpp"

class		Protocol;

namespace	request
{
  class		Factory
  {
  private:
    Factory();
    ~Factory();

  private:
    static Factory	&getInstance();

  public:
    static const ARequest	factory(Protocol &, const requestCode::CodeID code);
    static void			factory(Protocol &, const ARequest &);

  private:
    std::map<requestCode::CodeID, Function<Protocol &(ARequest::*)(Protocol &)> >	_corresp;
  };
}

#endif /* REQUESTFACTORY_H_ */
