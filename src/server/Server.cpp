#include "Server.h"
#include <sstream>

Server::Server(const Router& router)
    : router_(router) {}

Response Server::handleRequest(const std::string& rawRequest) const {
    std::istringstream iss(rawRequest);
    std::string methodStr;
    std::string path;

    iss >> methodStr >> path;
    if (methodStr.empty() || path.empty()) {
        return Response(StatusCode::BAD_REQUEST, "Malformed request");
    }

    HttpMethod method;
    if (methodStr == "GET") method = HttpMethod::GET;
    else if (methodStr == "POST") method = HttpMethod::POST;
    else if (methodStr == "PUT") method = HttpMethod::PUT;
    else if (methodStr == "DELETE") method = HttpMethod::DELETE_;
    else return Response(StatusCode::BAD_REQUEST, "Invalid HTTP method");

    Request request(method, path, "");
    return router_.dispatch(request);
}
