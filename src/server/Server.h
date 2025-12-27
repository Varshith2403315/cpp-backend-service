#ifndef SERVER_H
#define SERVER_H

#include "../routing/Router.h"
#include "../http/Request.h"
#include "../http/Response.h"

#include <string>

class Server {
private:
    Router router_;

public:
    Response handleRequest(const std::string& rawRequest) const;
};

#endif
