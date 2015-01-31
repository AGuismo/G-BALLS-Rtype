#include	"ChatRecvRequestTest.hh"

const std::string	ChatRecvRequestTest::A_MESSAGE = "This is a message";

void	ChatRecvRequestTest::SetUp()
{
  recvRequest = new ChatRecvRequest(A_MESSAGE);
}

void	ChatRecvRequestTest::TearDown()
{
  delete recvRequest;
}

TEST_F(ChatRecvRequestTest, whenGetMessageItsCorrect)
{
  EXPECT_EQ(ChatRecvRequestTest::A_MESSAGE, recvRequest->msg());
}


TEST_F(ChatRecvRequestTest, whenCopyWithConstructorObjectItRemainsIdentical)
{
  ChatRecvRequest	theCopy(*recvRequest);

  EXPECT_EQ(ChatRecvRequestTest::A_MESSAGE, theCopy.msg());
}

TEST_F(ChatRecvRequestTest, whenCopyWithOperatorObjectItRemainsIdentical)
{
  ChatRecvRequest	theCopy;
  theCopy = *recvRequest;

  EXPECT_EQ(ChatRecvRequestTest::A_MESSAGE, theCopy.msg());
}

TEST_F(ChatRecvRequestTest, whenCloneItCreateChatRecvObject)
{
  ChatRecvRequest	*theCopy = dynamic_cast<ChatRecvRequest *>(recvRequest->clone());

  EXPECT_NE(theCopy, (void *)0ULL);
  delete theCopy;
}

TEST_F(ChatRecvRequestTest, whenCloneItCreatesIdenticalObject)
{
  ChatRecvRequest	*theCopy = dynamic_cast<ChatRecvRequest *>(recvRequest->clone());

  EXPECT_NE(recvRequest, theCopy);
  EXPECT_EQ(recvRequest->msg(), theCopy->msg());
  delete theCopy;
}


