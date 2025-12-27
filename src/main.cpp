#include "server/Server.h"
#include <iostream>

int main() {
    Server server;

    std::string input = "POST /health";
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
