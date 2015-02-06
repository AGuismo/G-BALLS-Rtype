#include	"DeathRequestTest.hh"

const rtype::protocol::Ruint16		DeathRequestTest::AN_ID = 45;
const rtype::protocol::game::Stamp	DeathRequestTest::A_STAMP = 42;

void	DeathRequestTest::SetUp()
{
  deathRequest = new DeathRequest();
}

void	DeathRequestTest::TearDown()
{
  delete deathRequest;
}

TEST_F(DeathRequestTest, whenUseConstructorParameterItSetsProperly)
{
  DeathRequest	myDeathRequest(DeathRequestTest::AN_ID, DeathRequestTest::A_STAMP);

  EXPECT_EQ(DeathRequestTest::AN_ID, myDeathRequest.ID());
  EXPECT_EQ(DeathRequestTest::A_STAMP, myDeathRequest.Stamp());
}

TEST_F(DeathRequestTest, whenSetIdItsCorrect)
{
  deathRequest->ID(DeathRequestTest::AN_ID);

  EXPECT_EQ(DeathRequestTest::AN_ID, deathRequest->ID());
}


TEST_F(DeathRequestTest, whenCopyWithConstructorObjectItRemainsIdentical)
{
  deathRequest->ID(DeathRequestTest::AN_ID);

  DeathRequest	theCopy(*deathRequest);

  EXPECT_EQ(DeathRequestTest::AN_ID, theCopy.ID());
}

TEST_F(DeathRequestTest, whenCopyWithOperatorObjectItRemainsIdentical)
{
  deathRequest->ID(DeathRequestTest::AN_ID);
  DeathRequest	theCopy;

  theCopy = *deathRequest;

  EXPECT_EQ(DeathRequestTest::AN_ID, theCopy.ID());
}

TEST_F(DeathRequestTest, whenCloneItCreateDeathObject)
{
  DeathRequest	*theCopy = dynamic_cast<DeathRequest *>(deathRequest->clone());

  EXPECT_NE(theCopy, (void *)0ULL);
  delete theCopy;
}

TEST_F(DeathRequestTest, whenCloneItCreatesIdenticalObject)
{
  deathRequest->ID(DeathRequestTest::AN_ID);

  DeathRequest	*theCopy = dynamic_cast<DeathRequest *>(deathRequest->clone());

  EXPECT_NE(deathRequest, theCopy);
  EXPECT_EQ(deathRequest->ID(), theCopy->ID());
  delete theCopy;
}
