#include	"BuffRequest.hh"
#include	"BuffRequestTest.hh"

const unsigned short	BuffRequestTest::AN_ID = 5;
const unsigned char	BuffRequestTest::A_TYPE = 15;

void	BuffRequestTest::SetUp()
{
  buffRequest = new BuffRequest;
}

void	BuffRequestTest::TearDown()
{
  delete buffRequest;
}


TEST_F(BuffRequestTest, whenSetRequestIDChangeItProperly)
{
  buffRequest->ID(BuffRequestTest::AN_ID);

  EXPECT_EQ(BuffRequestTest::AN_ID, buffRequest->ID());
}

TEST_F(BuffRequestTest, whenSetTypeChangeItProperly)
{
  buffRequest->type(BuffRequestTest::A_TYPE);

  EXPECT_EQ(BuffRequestTest::A_TYPE, buffRequest->type());
}

TEST_F(BuffRequestTest, whenCopyWithConstructorObjectItRemainsIdentical)
{
  buffRequest->ID(BuffRequestTest::AN_ID);
  buffRequest->type(BuffRequestTest::A_TYPE);

  BuffRequest	theCopy(*buffRequest);

  EXPECT_EQ(BuffRequestTest::AN_ID, theCopy.ID());
  EXPECT_EQ(BuffRequestTest::A_TYPE, theCopy.type());
}

TEST_F(BuffRequestTest, whenCopyWithOperatorObjectItRemainsIdentical)
{
  buffRequest->ID(BuffRequestTest::AN_ID);
  buffRequest->type(BuffRequestTest::A_TYPE);

  BuffRequest	theCopy;
  theCopy = *buffRequest;

  EXPECT_EQ(BuffRequestTest::AN_ID, theCopy.ID());
  EXPECT_EQ(BuffRequestTest::A_TYPE, theCopy.type());
}

TEST_F(BuffRequestTest, whenCloneTheObjectItRemainsCreateIdenticalObject)
{
  buffRequest->ID(BuffRequestTest::AN_ID);
  buffRequest->type(BuffRequestTest::A_TYPE);

  BuffRequest	*theCopy = dynamic_cast<BuffRequest *>(buffRequest->clone());

  EXPECT_NE(buffRequest, theCopy);
  EXPECT_EQ(buffRequest->ID(), theCopy->ID());
  EXPECT_EQ(buffRequest->type(), theCopy->type());
  delete theCopy;
}
