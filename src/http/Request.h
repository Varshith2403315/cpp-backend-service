#ifndef REQUEST_H
#define REQUEST_H

#include <string>

enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE_
};

class Request {
private:
    HttpMethod method_;
    std::string path_;
    std::string body_;

public:
    Request(HttpMethod method, const std::string& path, const std::string& body)
        : method_(method), path_(path), body_(body) {}

    HttpMethod method() const {
        return method_;
    }

    const std::string& path() const {
        return path_;
    }

    const std::string& body() const {
        return body_;
    }
};

#endif
