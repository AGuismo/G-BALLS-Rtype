#ifndef ELEMREQUESTTEST_H_
# define ELEMREQUESTTEST_H_

#include	<gtest/gtest.h>
#include	"ElemRequest.hh"
#include	"Player.hh"

class ElemRequestTest : public ::testing::Test
{
public:
  static const unsigned short			A_PLAYER_ID;
  static const Position				A_PLAYER_POSITION;
  static const Entity				*AN_ENTITY;
  static const rtype::protocol::SessionID	A_SESSION_ID;
  static const rtype::protocol::game::Stamp	A_STAMP;

protected:

  virtual void	SetUp();
  virtual void	TearDown();

  ElemRequest	*elemRequest;
};

#endif /* ELEMREQUESTTEST_H_ */
