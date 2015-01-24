#ifndef AUTHREQUESTTEST_H_
# define AUTHREQUESTTEST_H_

#include	<gtest/gtest.h>
#include	"AuthRequest.hh"

class AuthRequestTest : public ::testing::Test
{
public:
  static const std::string			AN_USERNAME;
  static const requestCode::PasswordType	A_PASSWORD;
  static const requestCode::PasswordType	CURRENT_PASSWORD;
  static const requestCode::PasswordType	NEW_PASSWORD;
  static const requestCode::SessionID		A_SESSION_ID;

protected:

  virtual void	SetUp();
  virtual void TearDown();

  Auth::Connect		*connectRequest;
  Auth::NewUser		*newUserRequest;
  Auth::ChangePass	*changePassRequest;
};


#endif /* AUTHREQUESTTEST_H_ */
