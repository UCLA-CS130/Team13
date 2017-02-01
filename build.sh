#!/bin/bash

case `uname` in
  Linux) g++ http_server.cpp webserver_main.cc -std=c++0x -g -Wall -o http_server;;
  Darwin) clang++ config_parser.cc config_parser_main.cc -std=c++11 -g -Wall -stdlib=libc++ -o config_parser;;
  *) echo "Unknown operating system";;
esac

