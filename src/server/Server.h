#ifndef SERVER_H
#define SERVER_H

#include "../routing/Router.h"
#include <string>

class Server {
public:
    explicit Server(const Router& router);

    Response handleRequest(const std::string& rawRequest) const;

private:
    const Router& router_;
};

#endif
