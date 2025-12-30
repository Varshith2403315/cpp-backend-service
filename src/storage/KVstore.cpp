#include "KVStore.h"
#include <fstream>
#include <cstdio>  
#include <sstream>
#include <stdexcept>


KVStore::KVStore(const std::string& filePath)
    : filePath_(filePath) {

    std::ifstream in(filePath_);
    if (!in) {
        // File does not exist → start with empty store
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
    data_[key] = value;
    persist();
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
    
    persist();
    return KVResult::OK;
}
