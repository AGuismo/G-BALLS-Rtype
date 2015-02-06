#ifndef REQUESTFACTORY_H_
# define REQUESTFACTORY_H_

# include	<map>
# include	"ARequest.hh"
# include	"RequestCode.hh"

class		Protocol;

namespace	request
{
  class		Factory
  {
    typedef	std::map<rtype::protocol::CodeID, ARequest *> lnk_type;
  private:
    Factory();
    ~Factory();

  private:
    static Factory	&getInstance();

  public:
    static ARequest	*factory(Protocol &, const rtype::protocol::CodeID code);
    static void		factory(Protocol &, const ARequest &);

  private:
    lnk_type		_lnk;
  };
}

#endif /* REQUESTFACTORY_H_ */
