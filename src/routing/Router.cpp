#include "Router.h"

Response Router::route(const Request& request) const {
    if (request.path() == "/health") {
        return healthHandler_.handle(request);
    }

    return Response(StatusCode::NOT_FOUND, "Route not found");
}
