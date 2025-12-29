cmake_minimum_required(VERSION 3.10)

project(cpp_backend_service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    src/main.cpp

    src/server/Server.cpp
    src/routing/Router.cpp

    src/handlers/HealthHandler.cpp
    src/handlers/PostKVHandler.cpp
    src/handlers/GetKVHandler.cpp
    src/handlers/DeleteKVHandler.cpp

    src/storage/KVStore.cpp
)

target_include_directories(app PRIVATE
    src
    src/server
    src/routing
    src/handlers
    src/storage
    src/http
)
