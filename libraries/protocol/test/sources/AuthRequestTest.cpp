#include	"AuthRequestTest.hh"

const std::string		AuthRequestTest::AN_USERNAME = "myTest";
const rtype::protocol::PasswordType	AuthRequestTest::A_PASSWORD = "aPassword";
const rtype::protocol::PasswordType	AuthRequestTest::CURRENT_PASSWORD = "ACurrentPassword";
const rtype::protocol::PasswordType	AuthRequestTest::NEW_PASSWORD = "TheChangePassword";
const rtype::protocol::SessionID	AuthRequestTest::A_SESSION_ID = 42;


void	AuthRequestTest::SetUp()
{
  connectRequest = new Auth::Connect(AN_USERNAME, A_PASSWORD);
  newUserRequest = new Auth::NewUser(AN_USERNAME, A_PASSWORD);
  changePassRequest = new Auth::ChangePass(AN_USERNAME, CURRENT_PASSWORD, NEW_PASSWORD, A_SESSION_ID);
}

void	AuthRequestTest::TearDown()
{
  delete connectRequest;
  delete newUserRequest;
  delete changePassRequest;
}


TEST_F(AuthRequestTest, whenGetConnectUsernameItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::AN_USERNAME, connectRequest->username());
}

TEST_F(AuthRequestTest, whenGetConnectPasswordItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, connectRequest->password());
}

TEST_F(AuthRequestTest, whenCopyConnectWithConstructorObjectItRemainsIdentical)
{
  Auth::Connect	theCopy(*connectRequest);

  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy.username());
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, theCopy.password());
}

TEST_F(AuthRequestTest, whenCopyConnectWithOperatorObjectItRemainsIdentical)
{
  Auth::Connect	theCopy;
  theCopy = *connectRequest;

  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy.username());
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, theCopy.password());
}

TEST_F(AuthRequestTest, whenCloneConnectItCreateConnectObject)
{
  Auth::Connect	*theCopy = dynamic_cast<Auth::Connect *>(connectRequest->clone());

  EXPECT_NE(theCopy, (void *)0ULL);
  delete theCopy;
}

TEST_F(AuthRequestTest, whenCloneConnectItCreatesIdenticalObject)
{
  Auth::Connect	*theCopy = dynamic_cast<Auth::Connect *>(connectRequest->clone());

  EXPECT_NE(connectRequest, theCopy);
  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy->username());
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, theCopy->password());
  delete theCopy;
}






TEST_F(AuthRequestTest, whenGetNewUserUsernameItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::AN_USERNAME, newUserRequest->username());
}

TEST_F(AuthRequestTest, whenGetNewUserPasswordItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, newUserRequest->password());
}

TEST_F(AuthRequestTest, whenCopyNewUserWithConstructorObjectItRemainsIdentical)
{
  Auth::NewUser	theCopy(*newUserRequest);

  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy.username());
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, theCopy.password());
}

TEST_F(AuthRequestTest, whenCopyNewUserWithOperatorObjectItRemainsIdentical)
{
  Auth::NewUser	theCopy;
  theCopy = *newUserRequest;

  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy.username());
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, theCopy.password());
}

TEST_F(AuthRequestTest, whenCloneNewUserItCreateNewUserObject)
{
  Auth::NewUser	*theCopy = dynamic_cast<Auth::NewUser *>(newUserRequest->clone());

  EXPECT_NE(theCopy, (void *)0ULL);
  delete theCopy;
}

TEST_F(AuthRequestTest, whenCloneNewUserItCreatesIdenticalObject)
{
  Auth::NewUser	*theCopy = dynamic_cast<Auth::NewUser *>(newUserRequest->clone());

  EXPECT_NE(newUserRequest, theCopy);
  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy->username());
  EXPECT_EQ(AuthRequestTest::A_PASSWORD, theCopy->password());
  delete theCopy;
}




TEST_F(AuthRequestTest, whenGetChangePassUsernameItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::AN_USERNAME, changePassRequest->username());
}

TEST_F(AuthRequestTest, whenGetChangePassCurrentPasswordItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::CURRENT_PASSWORD, changePassRequest->curpassword());
}

TEST_F(AuthRequestTest, whenGetChangePassNewPasswordItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::NEW_PASSWORD, changePassRequest->newpassword());
}

TEST_F(AuthRequestTest, whenGetChangePassSessionIdItsCorrect)
{
  EXPECT_EQ(AuthRequestTest::A_SESSION_ID, changePassRequest->sessionID());
}

TEST_F(AuthRequestTest, whenCopyChangePassWithConstructorObjectItRemainsIdentical)
{
  Auth::ChangePass	theCopy(*changePassRequest);

  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy.username());
  EXPECT_EQ(AuthRequestTest::CURRENT_PASSWORD, theCopy.curpassword());
  EXPECT_EQ(AuthRequestTest::NEW_PASSWORD, theCopy.newpassword());
  EXPECT_EQ(AuthRequestTest::A_SESSION_ID, theCopy.sessionID());
}

TEST_F(AuthRequestTest, whenCopyChangePassWithOperatorObjectItRemainsIdentical)
{
  Auth::ChangePass	theCopy;
  theCopy = *changePassRequest;

  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy.username());
  EXPECT_EQ(AuthRequestTest::CURRENT_PASSWORD, theCopy.curpassword());
  EXPECT_EQ(AuthRequestTest::NEW_PASSWORD, theCopy.newpassword());
  EXPECT_EQ(AuthRequestTest::A_SESSION_ID, theCopy.sessionID());
}

TEST_F(AuthRequestTest, whenCloneChangePassItCreateChangePassObject)
{
  Auth::ChangePass	*theCopy = dynamic_cast<Auth::ChangePass *>(changePassRequest->clone());

  EXPECT_NE(theCopy, (void *)0ULL);
  delete theCopy;
}

TEST_F(AuthRequestTest, whenCloneChangePassItCreatesIdenticalObject)
{
  Auth::ChangePass	*theCopy = dynamic_cast<Auth::ChangePass *>(changePassRequest->clone());

  EXPECT_NE(changePassRequest, theCopy);
  EXPECT_EQ(AuthRequestTest::AN_USERNAME, theCopy->username());
  EXPECT_EQ(AuthRequestTest::CURRENT_PASSWORD, theCopy->curpassword());
  EXPECT_EQ(AuthRequestTest::NEW_PASSWORD, theCopy->newpassword());
  EXPECT_EQ(AuthRequestTest::A_SESSION_ID, theCopy->sessionID());
  delete theCopy;
}
