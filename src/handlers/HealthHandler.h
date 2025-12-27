#ifndef HEALTH_HANDLER_H
#define HEALTH_HANDLER_H

#include "../http/Request.h"
#include "../http/Response.h"

class HealthHandler {
public:
    Response handle(const Request& request) const;
};

#endif
