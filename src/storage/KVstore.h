#ifndef KVSTORE_H
#define KVSTORE_H

#include <string>
#include <unordered_map>
#include <mutex>

enum class KVResult {
    OK,
    NOT_FOUND
};

class KVStore {
public:
    explicit KVStore(const std::string& filePath);

    KVResult put(const std::string& key, const std::string& value);
    KVResult get(const std::string& key, std::string& outValue) const;
    KVResult erase(const std::string& key);

private:
    void persist() const;
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::string> data_;
    std::string filePath_;
};

#endif
