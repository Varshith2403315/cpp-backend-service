#ifndef KVSTORE_H
#define KVSTORE_H

#include <string>
#include <unordered_map>

enum class KVResult {
    OK,
    NOT_FOUND
};

class KVStore {
public:
    KVResult put(const std::string& key, const std::string& value);

    KVResult get(const std::string& key, std::string& outValue) const;

    KVResult erase(const std::string& key);

private:
    std::unordered_map<std::string, std::string> data_;
};

#endif
