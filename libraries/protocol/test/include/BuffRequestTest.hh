#ifndef BUFFREQUESTTEST_H_
# define BUFFREQUESTTEST_H_

#include	<gtest/gtest.h>

class BuffRequest;

class BuffRequestTest : public ::testing::Test
{
public:
  static const unsigned short	AN_ID;
  static const unsigned char	A_TYPE;

protected:

  virtual void	SetUp();
  virtual void TearDown();

  BuffRequest	*buffRequest;
};


#endif /* BUFFREQUESTTEST_H_ */
