cmake_minimum_required(VERSION 3.10)

project(cpp_backend_service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    src/main.cpp
    src/server/Server.cpp
    src/routing/Router.cpp
    src/handlers/HealthHandler.cpp
)
