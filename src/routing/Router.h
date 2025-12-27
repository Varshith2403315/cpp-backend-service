#ifndef ROUTER_H
#define ROUTER_H

#include "../http/Request.h"
#include "../http/Response.h"
#include "../handlers/HealthHandler.h"

class Router {
private:
    HealthHandler healthHandler_;

public:
    Response route(const Request& request) const;
};

#endif
