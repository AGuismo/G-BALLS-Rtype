#ifndef AGAMEREQUESTTEST_H_
# define AGAMEREQUESTTEST_H_

#include	<gtest/gtest.h>
#include	"AGameRequest.hh"

class AGameRequestTest : public ::testing::Test
{
public:
  static const rtype::protocol::CodeID		A_CODE_ID;
  static const rtype::protocol::SessionID	A_SESSION_ID;
  static const rtype::protocol::game::Stamp	A_STAMP;

public:
  class	EmptyGameRequest: public AGameRequest
  {
  public:
    EmptyGameRequest(const rtype::protocol::CodeID code = A_CODE_ID):
      AGameRequest(code) {}
    EmptyGameRequest(const EmptyGameRequest &src): AGameRequest(src) {}

    virtual ~EmptyGameRequest() {}

    ARequest	*clone() const {return (0);}
    Protocol	&serialize(Protocol &p) const {return (p);}
    Protocol	&unserialize(Protocol &p) {return (p);}
  };

protected:

  virtual void	SetUp();
  virtual void	TearDown();

  EmptyGameRequest	*gameRequest;
};


#endif /* AGAMEREQUESTTEST_H_ */
