#ifndef GRPCTESTTASK_GRPCCLIENT_H
#define GRPCTESTTASK_GRPCCLIENT_H

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "absl/flags/parse.h"
#include "absl/flags/flag.h"

#include "api.grpc.pb.h"
#include "api.pb.h"

class grpcClient {
public:
    grpcClient(std::shared_ptr<grpc::Channel> channel) : stub_(api::MaintainingApi::NewStub(channel)) {}

    std::string Ping(const std::string& client_ip);
private:
    std::unique_ptr<api::MaintainingApi::Stub> stub_;
};


#endif //GRPCTESTTASK_GRPCCLIENT_H
