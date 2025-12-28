#ifndef GET_KV_HANDLER_H
#define GET_KV_HANDLER_H

#include "../http/Request.h"
#include "../http/Response.h"
#include "../storage/KVStore.h"

class GetKVHandler {
    private :
        KVStore& store_;
    public : 
        explicit GetKVHandler(KVStore& store);
        Response handle(const Request& request);
};



#endif