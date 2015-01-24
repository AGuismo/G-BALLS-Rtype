#ifndef CHATRECVREQUESTTEST_H_
# define CHATRECVREQUESTTEST_H_

#include	<gtest/gtest.h>
#include	"ChatRecvRequest.hh"

class ChatRecvRequestTest : public ::testing::Test
{
public:
  static const std::string	A_MESSAGE;

protected:

  virtual void	SetUp();
  virtual void TearDown();

  ChatRecvRequest	*recvRequest;
};

#endif /* CHATRECVREQUESTTEST_H_ */
