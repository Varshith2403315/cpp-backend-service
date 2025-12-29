#include "Server.h"
#include <sstream>
#include <iostream>
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

    std::string routePath = path;
    if (routePath.rfind("/kv/", 0) == 0) {
        routePath = "/kv";
    }
    std::string body;
    std::getline(iss, body);

    // Removing leading spaces if present
    if (!body.empty() && body[0] == ' ') {
        body.erase(0, 1);
    }

    Request request(method, path, body);
    return router_.dispatch(routePath, request);

}

