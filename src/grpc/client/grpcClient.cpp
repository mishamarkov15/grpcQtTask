#include "../../../include/grpc/client/grpcClient.h"


std::string grpcClient::Ping(const std::string& client_ip) {
    api::PingRequest request;
    request.set_clientip(client_ip);

    api::PingResponse response;

    grpc::ClientContext context;

    grpc::Status status = stub_->Ping(&context, request, &response);
    if (status.ok()) {
        return "pong";
    } else {
        std::cerr << status.error_code() << ": " << status.error_message() << "\n";
        return "RPC failed";
    }
}