#ifndef DELETE_KV_HANDLER_H
#define DEFINE_KV_HANDLER_H

#include "../http/Request.h"
#include "../http/Response.h"
#include "../storage/KVstore.h"

class DeleteKVHandler
{
private:
    KVStore& store_;
public:
    explicit DeleteKVHandler(KVStore& store);
    Response handle(const Request& request);
};

#endif