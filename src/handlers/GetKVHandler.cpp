#include "GetKVHandler.h"

GetKVHandler::GetKVHandler(KVStore& store)
    : store_(store) {}

Response GetKVHandler::handle(const Request& request) {
    const std::string& path = request.path();
    const std::string prefix = "/kv/";

    // Validate path format
    if (path.size() <= prefix.size() ||
        path.substr(0, prefix.size()) != prefix) {
        return Response(StatusCode::BAD_REQUEST, "Invalid key path");
    }

    std::string key = path.substr(prefix.size());

    std::string value;
    KVResult result = store_.get(key, value);

    if (result == KVResult::NOT_FOUND) {
        return Response(StatusCode::NOT_FOUND, "Key not found");
    }

    return Response(StatusCode::OK, value);
}
