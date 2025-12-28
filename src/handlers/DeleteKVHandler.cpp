#include "DeleteKVHandler.h"

DeleteKVHandler::DeleteKVHandler(KVStore& store)
    : store_(store) {}

Response DeleteKVHandler::handle(const Request& request) {
    const std::string& path = request.path();
    const std::string prefix = "/kv/";

    if (path.size() <= prefix.size() ||
        path.substr(0, prefix.size()) != prefix) {
        return Response(StatusCode::BAD_REQUEST, "Invalid key path");
    }

    std::string key = path.substr(prefix.size());

    KVResult result = store_.erase(key);

    if (result == KVResult::NOT_FOUND) {
        return Response(StatusCode::NOT_FOUND, "Key not found");
    }

    return Response(StatusCode::OK, "Deleted");
}
