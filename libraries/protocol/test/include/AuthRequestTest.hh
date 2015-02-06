#ifndef AUTHREQUESTTEST_H_
# define AUTHREQUESTTEST_H_

#include	<gtest/gtest.h>
#include	"AuthRequest.hh"

class AuthRequestTest : public ::testing::Test
{
public:
  static const std::string			AN_USERNAME;
  static const rtype::protocol::PasswordType	A_PASSWORD;
  static const rtype::protocol::PasswordType	CURRENT_PASSWORD;
  static const rtype::protocol::PasswordType	NEW_PASSWORD;
  static const rtype::protocol::SessionID		A_SESSION_ID;

protected:

  virtual void	SetUp();
  virtual void TearDown();

  Auth::Connect		*connectRequest;
  Auth::NewUser		*newUserRequest;
  Auth::ChangePass	*changePassRequest;
};


#endif /* AUTHREQUESTTEST_H_ */
