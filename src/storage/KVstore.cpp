#include "KVStore.h"
#include <fstream> // input taker
#include <cstdio>  //opening and reading and renaming
#include <sstream>   
#include <stdexcept>  // error handling
#include <mutex> // locking


KVStore::KVStore(const std::string& filePath)
    : filePath_(filePath) {

    std::ifstream in(filePath_);
    if (!in) {
        // if File does not exist we start with empty store
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string key, value;

        if (!(iss >> key >> value) || !iss.eof()) {
            throw std::runtime_error("Malformed persistence file");
        }

        data_[key] = value;
    }
}

void KVStore::persist() const {
    std::string tempFile = filePath_ + ".tmp";

    std::ofstream out(tempFile);
    if (!out) {
        throw std::runtime_error("Failed to open temp persistence file");
    }

    for (const auto& [key, value] : data_) {
        out << key << " " << value << "\n";
    }

    out.flush();
    out.close();

    if (std::rename(tempFile.c_str(), filePath_.c_str()) != 0) {
        throw std::runtime_error("Atomic rename failed");
    }
}


KVResult KVStore::put(const std::string& key, const std::string& value) {

    std::lock_guard<std::mutex> lock(mutex_);

    data_[key] = value;
    persist();
    return KVResult::OK;
}

KVResult KVStore::get(const std::string& key, std::string& outValue) const {

    std::lock_guard<std::mutex> lock(mutex_);

    auto it = data_.find(key);
    if (it == data_.end()) {
        return KVResult::NOT_FOUND;
    }
    outValue = it->second;
    return KVResult::OK;
}

KVResult KVStore::erase(const std::string& key) {

    std::lock_guard<std::mutex> lock(mutex_);

    auto count = data_.erase(key);
    if (count == 0) {
        return KVResult::NOT_FOUND;
    }
    persist();
    return KVResult::OK;
}
