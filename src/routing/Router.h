#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <unordered_map>
#include <functional>

#include "../http/Request.h"
#include "../http/Response.h"

using Handler = std::function<Response(const Request&)>;

class Router {
public:
    void registerRoute(HttpMethod method,
                       const std::string& path,
                       Handler handler);

    Response dispatch(const Request& request) const;

private:
    // path -> (method -> handler)
    std::unordered_map<
        std::string,
        std::unordered_map<HttpMethod, Handler>
    > routes_;
};

#endif
