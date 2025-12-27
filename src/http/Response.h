#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

enum class StatusCode {
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
};

class Response {
private:
    StatusCode status_;
    std::string body_;

public:
    explicit Response(StatusCode status, std::string body)
        : status_(status), body_(std::move(body)) {}

    StatusCode status() const noexcept {
        return status_;
    }

    const std::string& body() const noexcept {
        return body_;
    }
};

#endif
