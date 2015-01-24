#include	"ChatSendRequestTest.hh"

const std::string	ChatSendRequestTest::A_MESSAGE = "This is a message";

void	ChatSendRequestTest::SetUp()
{
  sendRequest = new ChatSendRequest(A_MESSAGE);
}

void	ChatSendRequestTest::TearDown()
{
  delete sendRequest;
}

TEST_F(ChatSendRequestTest, whenGetMessageItsCorrect)
{
  EXPECT_EQ(ChatSendRequestTest::A_MESSAGE, sendRequest->msg());
}


TEST_F(ChatSendRequestTest, whenCopyWithConstructorObjectItRemainsIdentical)
{
  ChatSendRequest	theCopy(*sendRequest);

  EXPECT_EQ(ChatSendRequestTest::A_MESSAGE, theCopy.msg());
}

TEST_F(ChatSendRequestTest, whenCopyWithOperatorObjectItRemainsIdentical)
{
  ChatSendRequest	theCopy;
  theCopy = *sendRequest;

  EXPECT_EQ(ChatSendRequestTest::A_MESSAGE, theCopy.msg());
}

TEST_F(ChatSendRequestTest, whenCloneItCreateChatSendObject)
{
  ChatSendRequest	*theCopy = dynamic_cast<ChatSendRequest *>(sendRequest->clone());

  EXPECT_NE(theCopy, (void *)0ULL);
  delete theCopy;
}

TEST_F(ChatSendRequestTest, whenCloneItCreatesIdenticalObject)
{
  ChatSendRequest	*theCopy = dynamic_cast<ChatSendRequest *>(sendRequest->clone());

  EXPECT_NE(sendRequest, theCopy);
  EXPECT_EQ(sendRequest->msg(), theCopy->msg());
  delete theCopy;
}


