#ifndef POST_KV_HANDLER_H
#define POST_KV_HANDLER_H

#include "../http/Request.h"
#include "../http/Response.h"
#include "../storage/KVStore.h"

class PostKVHandler {
public:
    explicit PostKVHandler(KVStore& store);

    Response handle(const Request& request);

private:
    KVStore& store_;
};

#endif
