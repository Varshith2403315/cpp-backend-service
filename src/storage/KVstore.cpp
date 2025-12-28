#include "KVStore.h"

KVResult KVStore::put(const std::string& key, const std::string& value) {
    data_[key] = value;
    return KVResult::OK;
}

KVResult KVStore::get(const std::string& key, std::string& outValue) const {
    auto it = data_.find(key);
    if (it == data_.end()) {
        return KVResult::NOT_FOUND;
    }

    outValue = it->second;
    return KVResult::OK;
}

KVResult KVStore::erase(const std::string& key) {
    auto count = data_.erase(key);
    if (count == 0) {
        return KVResult::NOT_FOUND;
    }

    return KVResult::OK;
}
