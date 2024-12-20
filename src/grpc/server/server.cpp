#include <iostream>
#include <memory>
#include <string>
#include <cstdint>

#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "api.grpc.pb.h"
#include "api.pb.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

class ApiServiceImplementation final : public api::MaintainingApi::Service {
    grpc::Status Ping(
            grpc::ServerContext *context,
            const api::PingRequest *request,
            api::PingResponse *response
    ) override {
        return grpc::Status::OK;
    }
};

void RunServer(uint16_t port) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    ApiServiceImplementation apiServiceImplementation;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&apiServiceImplementation);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << '\n';
    server->Wait();
}

int main(int argc, char **argv) {
    absl::ParseCommandLine(argc, argv);
    RunServer(absl::GetFlag(FLAGS_port));
    return 0;
}