#include "gtest/gtest.h"
#include "request.hpp"

using namespace std;
class request_test:public ::testing::Test{
protected:
	request myrequest;
	myrequest.start={'a','b'};
	myrequest.end={'c','d'};
	EXPECT_EQ(myrequest.toString(),"abcd");
	
};