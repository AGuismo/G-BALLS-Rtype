#ifndef CHATSENDREQUESTTEST_H_
# define CHATSENDREQUESTTEST_H_

#include	<gtest/gtest.h>
#include	"ChatSendRequest.hh"

class ChatSendRequestTest : public ::testing::Test
{
public:
  static const std::string	A_MESSAGE;

protected:

  virtual void	SetUp();
  virtual void TearDown();

  ChatSendRequest	*sendRequest;
};

#endif /* CHATSENDREQUESTTEST_H_ */
