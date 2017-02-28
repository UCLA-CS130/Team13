//
// client.cc
// ~~~~~~~~~~~~~~~~


#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Response.h"
#include "Request.h"
#include "RequestHandler.h"

class ProxyClient {
public:
    bool Init(std::string host, std::string port);
    bool EstablishConnection(const std::string& host, const std::string& port);
    RequestHandler::Status HTTPRequest(const Request& request, std::string& response);
    Response* SendRequest(const Request& req);
    void handle_read_content(const boost::system::error_code& err);
private:
    std::string host_;
    std::string port_;
    boost::asio::ip::tcp::socket* socket_;
    boost::asio::streambuf response_;
};