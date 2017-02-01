#!/bin/bash

GTEST_DIR=googletest/googletest
case `uname` in
  Linux)
    g++ -std=c++0x -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
    ar -rv libgtest.a gtest-all.o
    g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread http_server_test.cpp http_server.cpp ${GTEST_DIR}/src/gtest_main.cc nginx-configparser/config_parser.cc libgtest.a -lboost_system  -o http_server_test ;;
  Darwin)
    clang++ -std=c++11 -stdlib=libc++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
    ar -rv libgtest.a gtest-all.o
    clang++ -std=c++11 -stdlib=libc++ -isystem ${GTEST_DIR}/include -pthread config_parser_test.cc config_parser.cc ${GTEST_DIR}/src/gtest_main.cc libgtest.a -o config_parser_test ;;
  *)
    echo "Unknown operating system." ;;
esac