#include "server/Server.h"
#include "routing/Router.h"
#include "handlers/HealthHandler.h"

#include <iostream>

int main() {


    //Create router
    Router router;

    //Create handlers
    HealthHandler healthHandler;

    //startup phase
    router.registerRoute(
        HttpMethod::GET,
        "/health",
        [&](const Request& req) {
            return healthHandler.handle(req);
        }
    );

    //server with configured router
    Server server(router);

    // trails
    std::string input = "GET /health";
    Response response = server.handleRequest(input);

    std::cout << static_cast<int>(response.status())
              << " "
              << response.body()
              << std::endl;

    return 0;
}

//compiles 
//   g++ main.cpp server/Server.cpp routing/Router.cpp handlers/HealthHandler.cpp -o app 

//runs 
//   ./app
