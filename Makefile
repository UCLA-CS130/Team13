FLAGS = -l boost_system -pthread -std=c++0x -g -Wall
SOURCE_FILES = http_server.cpp nginx-configparser/config_parser.cc webserver_main.cc connection.cpp connection_manager.cpp request_handler.cpp request_parser.cpp response.cpp request.cpp
TEST_FILES = http_server.cpp nginx-configparser/config_parser.cc connection.cpp connection_manager.cpp request_handler.cpp request_parser.cpp response.cpp request.cpp
GTEST_DIR = googletest/googletest

all: compile

compile: $(SOURCE_FILES)
	@g++ $(SOURCE_FILES) $(FLAGS) -o webserver

clean:
	@rm -rf webserver *.dSYM *.o *.a
	
test: compile
	chmod a+x integration-test.py
	./integration-test.py

unittest:
	#g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread server_main_test.cc config_parser.cc EchoHandler.cc HttpResponse.cc ${GTEST_DIR}/src/gtest_main.cc libgtest.a -o server_tests -lboost_system -lpthread
	g++ -isystem ${GTEST_DIR}/include $(TEST_FILES) ${GTEST_DIR}/src/gtest_main.cc http_server_test.cpp libgtest.a $(FLAGS) -o http_server_test

gtest: $(GTEST_DIR)
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
