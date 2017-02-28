#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "ProxyClient.h"
#include "RequestHandler.h"

bool ProxyClient::Init(std::string host, std::string port)
{
  host_ = host;
  port_ = port;
  // Boost client creation
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::resolver resolver(io_service);

  //Resolve Endpoints
  // Resolve hostname / port number
  boost::asio::ip::tcp::resolver::query query(host_, port_);
  boost::asio::ip::tcp::resolver::iterator endpoint_it= resolver.resolve(query), end;

  //Attempt to bind socket to io_service and connect
  boost::system::error_code err;
  socket_ = new boost::asio::ip::tcp::socket(io_service);
  boost::asio::connect(*socket_, endpoint_it, end, err);
  if (err) {
      std::cerr << "ERROR: " << err << "\n";
      return false;
    }
    else return true;
}

RequestHandler::Status ProxyClient::HTTPRequest(const Request& request, std::string& response) {

  // Send the request.
  boost::asio::write(*socket_, boost::asio::buffer(request.raw_request()));

  //Read from socket, filling out response_ buffer
  boost::system::error_code err;
  handle_read_content(err);

  if (err){
    std::cerr << "ERROR: " << err;
    return RequestHandler::PROXY_FAILURE;
  }

  using boost::asio::buffers_begin;
  auto bufs = response_.data();
  std::string result(buffers_begin(bufs), buffers_begin(bufs) + response_.size());
  response = result;

  return RequestHandler::OK;
}



 void ProxyClient::handle_read_content(const boost::system::error_code& err)
  {
    if (!err)
    {
      // Continue reading remaining data until EOF.
      boost::asio::async_read(*socket_, response_,
          boost::asio::transfer_at_least(1),
          boost::bind(&ProxyClient::handle_read_content, this,
            boost::asio::placeholders::error));
    }
    else if (err != boost::asio::error::eof)
    {
      std::cout << "Error: " << err << "\n";
    }
  }