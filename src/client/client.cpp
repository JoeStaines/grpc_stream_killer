#include "grpc_lib/crashing_this_plane.grpc.pb.h"

#include <grpc++/grpc++.h>

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main() {
    auto&& grpc_client = grpc::CreateChannel("127.0.0.1:50050", grpc::InsecureChannelCredentials());
    auto&& stub = WithNoSurvivors::NewStub(grpc_client);

    auto&& s_fut = std::async(std::launch::async, [&]() { 
        grpc::ClientContext s_ctx;
        StreamerRequest s_req;
        StreamerResponse s_res;

        auto&& reader = stub->Streamer(&s_ctx, s_req);
        while (reader->Read(&s_res)) {
            std::cout << "Got stream!" << std::endl;
        }
    });

    auto&& fut = std::async(std::launch::async, [&]() {
        CallProcessRequest req;
        CallProcessResponse res;

        for (std::size_t i = 0; i < 1000; ++i) {
            grpc::ClientContext ctx;
            auto&& status = stub->CallProcess(&ctx, req, &res);
            if (!status.ok()) {
                throw std::runtime_error("AAAAAAAH!");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    auto&& r_fut = std::async(std::launch::async, [&]() {
        ReturnMeRequest r_req;
        r_req.set_text("testy");
        ReturnMeResponse r_res;

        for (std::size_t i = 0; i < 1000; ++i) {
            grpc::ClientContext r_ctx;
            auto&& status = stub->ReturnMe(&r_ctx, r_req, &r_res);
            if (!status.ok()) {
                throw std::runtime_error("OOOOOOOOH!");
            }
            std::cout << r_res.text() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    
    fut.get();
    r_fut.get();
    s_fut.get();
    
}