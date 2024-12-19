cmake_minimum_required(VERSION 3.24)
project(gRPCTestTask LANGUAGES C CXX VERSION 0.1 DESCRIPTION "Test gRPC/Qt6 task")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} -Wall -Wextra")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

set(SOURCES_SERVER main.cpp src/server/ServerMainWindow.cpp)
set(HEADERS_SERVER include/server/ServerMainWindow.h)

set(SOURCES_CLIENT client.cpp src/client/ClientMainWindow.cpp)
set(HEADERS_CLIENT include/client/ClientMainWindow.h)

add_executable(gRPCTestTaskServer ${SOURCES_SERVER} ${HEADERS_SERVER})
target_link_libraries(gRPCTestTaskServer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        )

add_executable(gRPCTestTaskClient ${SOURCES_CLIENT} ${HEADERS_CLIENT})
target_link_libraries(gRPCTestTaskClient
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        )

