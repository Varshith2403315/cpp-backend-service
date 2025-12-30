#include "server/Server.h"
#include "routing/Router.h"
//handlers
#include "handlers/DeleteKVHandler.h"
#include "handlers/GetKVHandler.h"
#include "handlers/PostKVHandler.h"
#include "handlers/HealthHandler.h"
#include "storage/KVstore.h"
////////////////////////////////////////////
#include <iostream>

int main() {

    KVStore store("kv.data");

    //Create router
    Router router;

    //Create handlers
    HealthHandler healthHandler;
    PostKVHandler postKVHandler(store);
    GetKVHandler getKVHandler(store);
    DeleteKVHandler deleteKVHandler(store);

    //startup phase
    router.registerRoute(
        HttpMethod::GET,
        "/health",
        [&](const Request& req) {
            return healthHandler.handle(req);
        }
    );
    // POST /kv
    router.registerRoute(
        HttpMethod::POST,
        "/kv",
        [&](const Request& req) {
            return postKVHandler.handle(req);
        }
    );

    // GET /kv/key
    router.registerRoute(
        HttpMethod::GET,
        "/kv",
        [&](const Request& req) {
            return getKVHandler.handle(req);
        }
    );

    // DELETE /kv/key
    router.registerRoute(
        HttpMethod::DELETE_,
        "/kv",
        [&](const Request& req) {
            return deleteKVHandler.handle(req);
        }
    );

    //server with configured router
    Server server(router);

    //temposs
    std::vector<std::string> tests = {
    "POST /kv name Varshith",
    "GET /kv/name",
    "DELETE /kv/name",
    "GET /kv/name"
};

for (const auto& input : tests) {
    Response response = server.handleRequest(input);
    std::cout << input << " -> "
              << static_cast<int>(response.status())
              << " "
              << response.body()
              << std::endl;
}


    return 0;
}

