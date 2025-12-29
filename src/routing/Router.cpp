#include "Router.h"

void Router::registerRoute(HttpMethod method,
                           const std::string& path,
                           Handler handler) {
    routes_[path][method] = std::move(handler);
}

Response Router::dispatch(const Request& request) const {
    const std::string& path = request.path();
    HttpMethod method = request.method();

    // Checker path
    auto pathIt = routes_.find(path);
    if (pathIt == routes_.end()) {
        return Response(StatusCode::NOT_FOUND, "Not Found");
    }
    // checker method
    const auto& methodMap = pathIt->second;
    auto methodIt = methodMap.find(method);
    if (methodIt == methodMap.end()) {
        return Response(StatusCode::METHOD_NOT_ALLOWED, "Method Not Allowed");
    }
    // Dispatch to handler
    const Handler& handler = methodIt->second;
    return handler(request);
}


Response Router::dispatch(const std::string& routePath,
                          const Request& request) const {
    HttpMethod method = request.method();

    auto pathIt = routes_.find(routePath);
    if (pathIt == routes_.end()) {
        return Response(StatusCode::NOT_FOUND, "Not Found");
    }

    const auto& methodMap = pathIt->second;
    auto methodIt = methodMap.find(method);
    if (methodIt == methodMap.end()) {
        return Response(StatusCode::METHOD_NOT_ALLOWED, "Method Not Allowed");
    }

    return methodIt->second(request);
}
