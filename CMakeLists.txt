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

include(grpc/examples/cpp/cmake/common.cmake)

get_filename_component(api_proto "protos/api.proto" ABSOLUTE)
get_filename_component(api_proto_path "${api_proto}" PATH)

set(api_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/api.pb.cc")
set(api_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/api.pb.h")
set(api_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/api.grpc.pb.cc")
set(api_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/api.grpc.pb.h")

add_custom_command(
        OUTPUT "${api_proto_srcs}" "${api_proto_hdrs}" "${api_grpc_srcs}" "${api_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${api_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${api_proto}"
        DEPENDS "${api_proto}"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(api_grpc_proto
        ${api_proto_srcs}
        ${api_proto_hdrs}
        ${api_grpc_srcs}
        ${api_grpc_hdrs})

target_link_libraries(api_grpc_proto
        absl::check
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

add_executable(server_grpc src/grpc/server/server.cpp)
target_link_libraries(server_grpc
        api_grpc_proto
        absl::check
        absl::flags
        absl::flags_parse
        absl::log
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
        )



set(SOURCES_SERVER server.cpp src/udp/server/ServerMainWindow.cpp)
set(HEADERS_SERVER include/udp/server/ServerMainWindow.h)

set(SOURCES_CLIENT
        client.cpp
        src/udp/client/ClientMainWindow.cpp
        src/udp/client/MyTableModel.cpp
        src/udp/client/AddressRecord.cpp
        src/grpc/client/grpcClient.cpp)
set(HEADERS_CLIENT
        include/udp/client/ClientMainWindow.h
        include/udp/client/MyTableModel.h
        include/udp/client/AddressRecord.h
        include/grpc/client/grpcClient.h)

add_executable(gRPCTestTaskServer ${SOURCES_SERVER} ${HEADERS_SERVER})
target_link_libraries(gRPCTestTaskServer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        )

add_executable(gRPCTestTaskClient ${SOURCES_CLIENT} ${HEADERS_CLIENT})
target_link_libraries(gRPCTestTaskClient
        api_grpc_proto
        absl::check
        absl::flags
        absl::flags_parse
        absl::log
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        )
