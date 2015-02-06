#include	"ElemRequestTest.hh"

const unsigned short			ElemRequestTest::A_PLAYER_ID = 55;
const rtype::protocol::game::Stamp	ElemRequestTest::A_STAMP = 12;
const rtype::protocol::SessionID	ElemRequestTest::A_SESSION_ID = 47;
const Position				ElemRequestTest::A_PLAYER_POSITION = Position(17, 24);
const Entity	*ElemRequestTest::AN_ENTITY = new Player(ElemRequestTest::A_PLAYER_ID,
							 ElemRequestTest::A_PLAYER_POSITION);

void	ElemRequestTest::SetUp()
{
  elemRequest = new ElemRequest();
}

void	ElemRequestTest::TearDown()
{
  delete elemRequest;
}

TEST_F(ElemRequestTest, whenUseConstructorParameterItSetsProperly)
{
  ElemRequest	myElemRequest(*ElemRequestTest::AN_ENTITY,
			      ElemRequestTest::A_SESSION_ID,
			      ElemRequestTest::A_STAMP);

  EXPECT_EQ(ElemRequestTest::A_SESSION_ID, myElemRequest.SessionID());
  EXPECT_EQ(ElemRequestTest::A_STAMP, myElemRequest.Stamp());
  EXPECT_EQ(ElemRequestTest::AN_ENTITY->getType().full, myElemRequest.type());
  EXPECT_EQ(ElemRequestTest::A_PLAYER_ID, myElemRequest.ID());
  EXPECT_EQ(ElemRequestTest::A_PLAYER_POSITION, myElemRequest.entity()->getPosition());
}

TEST_F(ElemRequestTest, whenCopyWithConstructorObjectItRemainsIdentical)
{
  elemRequest->entity(*ElemRequestTest::AN_ENTITY);

  ElemRequest	theCopy(*elemRequest);

  EXPECT_EQ(ElemRequestTest::AN_ENTITY->getType().full, theCopy.type());
  EXPECT_EQ(ElemRequestTest::A_PLAYER_ID, theCopy.ID());
  EXPECT_EQ(ElemRequestTest::A_PLAYER_POSITION, theCopy.entity()->getPosition());
}

TEST_F(ElemRequestTest, whenCopyWithOperatorObjectItRemainsIdentical)
{
  elemRequest->entity(*ElemRequestTest::AN_ENTITY);
  ElemRequest	theCopy;

  theCopy = *elemRequest;

  EXPECT_EQ(ElemRequestTest::AN_ENTITY->getType().full, theCopy.type());
  EXPECT_EQ(ElemRequestTest::A_PLAYER_ID, theCopy.ID());
  EXPECT_EQ(ElemRequestTest::A_PLAYER_POSITION, theCopy.entity()->getPosition());
}

TEST_F(ElemRequestTest, whenCloneItCreateElemObject)
{
  ElemRequest	*theCopy = dynamic_cast<ElemRequest *>(elemRequest->clone());

  EXPECT_NE(theCopy, (void *)0ULL);
  delete theCopy;
}

TEST_F(ElemRequestTest, whenCloneItCreatesIdenticalObject)
{
  elemRequest->entity(*ElemRequestTest::AN_ENTITY);

  ElemRequest	*theCopy = dynamic_cast<ElemRequest *>(elemRequest->clone());

  EXPECT_NE(elemRequest, theCopy);
  EXPECT_EQ(elemRequest->type(), theCopy->type());
  EXPECT_EQ(elemRequest->ID(), theCopy->ID());
  EXPECT_EQ(elemRequest->entity()->getPosition(), theCopy->entity()->getPosition());
  delete theCopy;
}
