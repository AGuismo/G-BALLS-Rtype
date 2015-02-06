#include	"AGameRequest.hh"
#include	"AGameRequestTest.hh"

const rtype::protocol::CodeID		AGameRequestTest::A_CODE_ID = 42;
const rtype::protocol::SessionID	AGameRequestTest::A_SESSION_ID = 5;
const rtype::protocol::game::Stamp	AGameRequestTest::A_STAMP = 15;

void	AGameRequestTest::SetUp()
{
  gameRequest = new EmptyGameRequest(A_CODE_ID);
}

void	AGameRequestTest::TearDown()
{
  delete gameRequest;
}

TEST_F(AGameRequestTest, whenSetStampChangeItProperly)
{
  gameRequest->Stamp(AGameRequestTest::A_STAMP);

  EXPECT_EQ(AGameRequestTest::A_STAMP, gameRequest->Stamp());
}

TEST_F(AGameRequestTest, whenSetTypeChangeItProperly)
{
  gameRequest->SessionID(AGameRequestTest::A_SESSION_ID);

  EXPECT_EQ(AGameRequestTest::A_SESSION_ID, gameRequest->SessionID());
}

TEST_F(AGameRequestTest, whenCopyWithConstructorObjectItRemainsIdentical)
{
  gameRequest->Stamp(AGameRequestTest::A_STAMP);
  gameRequest->SessionID(AGameRequestTest::A_SESSION_ID);

  EmptyGameRequest	theCopy(*gameRequest);

  EXPECT_EQ(AGameRequestTest::A_STAMP, theCopy.Stamp());
  EXPECT_EQ(AGameRequestTest::A_SESSION_ID, theCopy.SessionID());
}

TEST_F(AGameRequestTest, whenCopyWithOperatorObjectItRemainsIdentical)
{
  gameRequest->Stamp(AGameRequestTest::A_STAMP);
  gameRequest->SessionID(AGameRequestTest::A_SESSION_ID);

  EmptyGameRequest	theCopy;
  theCopy = *gameRequest;

  EXPECT_EQ(AGameRequestTest::A_STAMP, theCopy.Stamp());
  EXPECT_EQ(AGameRequestTest::A_SESSION_ID, theCopy.SessionID());
}
