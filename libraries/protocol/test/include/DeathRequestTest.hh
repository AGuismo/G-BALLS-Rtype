#ifndef DEATHREQUESTTEST_H_
# define DEATHREQUESTTEST_H_

#include	<gtest/gtest.h>
#include	"DeathRequest.hh"

class DeathRequestTest : public ::testing::Test
{
public:
  static const rtype::protocol::Ruint16		AN_ID;
  static const rtype::protocol::game::Stamp	A_STAMP;

protected:

  virtual void	SetUp();
  virtual void	TearDown();

  DeathRequest	*deathRequest;
};

#endif /* DEATHREQUESTTEST_H_ */
