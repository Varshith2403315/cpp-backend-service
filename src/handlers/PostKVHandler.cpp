#include "PostKVHandler.h"
#include <sstream>

PostKVHandler::PostKVHandler(KVStore& store)
    : store_(store) {}

Response PostKVHandler::handle(const Request& request) {
    std::istringstream iss(request.body());
    std::string key;
    std::string value;

    iss >> key >> value;

    if (key.empty() || value.empty()) {
        return Response(StatusCode::BAD_REQUEST, "Invalid key or value");
    }

    store_.put(key, value);
    return Response(StatusCode::OK, "Stored");
}
