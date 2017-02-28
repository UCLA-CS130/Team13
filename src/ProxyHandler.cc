#include "ProxyHandler.h"
#include "ProxyClient.h"
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

const std::string HOST_TOKEN = "host";
const std::string PORT_TOKEN = "port";

RequestHandler::Status ProxyHandler::HandleRequest(const Request& request,
                     Response* response) {

    ProxyClient proxyClient;
    proxyClient.Init("www.boost.org", "80");

    return RequestHandler::OK;
}

RequestHandler::Status ProxyHandler::Init(const std::string& uri_prefix,
            const NginxConfig& config) {
    uri_prefix_ = uri_prefix;

    // Get remote host and post from config.
    if (config.statements_.size() >= 2) {
        for (auto const& statement: config.statements_) {
            std::vector<std::string> tokens = statement->tokens_;
            if (tokens.size() == 2) {
                if (tokens.at(0) == HOST_TOKEN) {
                    host_ = tokens.at(1);
                }
                else if (tokens.at(0) == PORT_TOKEN) {
                    port_ = tokens.at(1);
                }
            }
        }

        // Set default port to 80
        if (port_.length() == 0){
            port_ = "80";
        }

        // Error checking on config parameters.
        if (host_ == "") {
            BOOST_LOG_TRIVIAL(error) << "No host specified\n";
            return BAD_CONFIG;
        }
        int port_as_int;
        try {
            port_as_int = std::stoi(port_);
        }
        catch (std::exception const &e) {
            BOOST_LOG_TRIVIAL(error) << "Port number is not a valid number\n";
            return BAD_CONFIG;
        }
        if (port_as_int > 65535 || port_as_int < 0) {
            BOOST_LOG_TRIVIAL(error) << "Port is outside acceptable range\n";
            return BAD_CONFIG;
        }

        BOOST_LOG_TRIVIAL(info) << "Init ProxyHandler " << "host: " << host_ << ", port: " << port_ << "\n";
        return OK;
    }
    BOOST_LOG_TRIVIAL(error) << "Init ProxyHandler: bad config\n";
    return NOT_ENOUGH_PARAM;
}