#include "HealthHandler.h"


Response HealthHandler::handle(const Request& request) const {
    if(request.method() == HttpMethod::GET && request.path() == "/health") {
        return Response(StatusCode::OK, "OK");
    }
    return Response(StatusCode::NOT_FOUND , "Not Found");
}