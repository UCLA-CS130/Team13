#include "gtest/gtest.h"
#include "http_server.hpp"

using namespace std;
class request_parser_test:public ::testing::Test{
protected:
	request_parser parser;
	
	
};
TEST_F(request_parser_test,parse_test){
	request myrequest;
	myrequest.header=    //need editing
	myrequest.end=   //need editing
	char* start=new char[1];
	char* end=new char[1];
	parse_result=parser.parse(request,start,end);
	EXPECT_EQ(result.toString(), );//need editing
}

//several more cases