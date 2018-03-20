#include "grpc_lib/crashing_this_plane.grpc.pb.h"
#include <grpc++/grpc++.h>

#include <boost/asio.hpp>
#include <boost/process.hpp>

#include <chrono>
#include <iostream>
#include <future>
#include <thread>

class ServiceImpl final : public WithNoSurvivors::Service {
public:
    ServiceImpl()
        : process_service()
        , work(process_service)
        , process_thread()
    {
        process_thread = std::thread([&]() {
            process_service.run();
        });
    }

    ~ServiceImpl() {
        process_service.stop();
        process_thread.join();
    }

    grpc::Status CallProcess(::grpc::ServerContext* context, const ::CallProcessRequest* request, ::CallProcessResponse* response) override
    {
        namespace bp = boost::process;
        std::future<std::string> data;
        std::future<std::string> data_err;

        bp::child("C:\\Windows\\System32\\help.exe",
            bp::std_in.close(),
            bp::std_out > data,
            bp::std_err > data_err,
            process_service
        );
        std::cout << data.get() << std::endl;
        std::cout << data_err.get() << std::endl;
        return grpc::Status::OK;
    }

    grpc::Status Streamer(::grpc::ServerContext* context, const ::StreamerRequest* request, ::grpc::ServerWriter<::StreamerResponse>* writer) override
    {
        for (std::size_t i = 0; i < 1000; ++i) {
            writer->Write(StreamerResponse{});
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        return grpc::Status::OK;
    }

    grpc::Status ReturnMe(::grpc::ServerContext* context, const ::ReturnMeRequest* request, ::ReturnMeResponse* response) override
    {
        response->set_text(request->text());
        return grpc::Status::OK;
    }

private:
    boost::asio::io_service process_service;
    boost::asio::io_service::work work;

    std::thread process_thread;
};

int main() {
    grpc::ServerBuilder server_builder;
    server_builder.AddListeningPort("0.0.0.0:8004", grpc::InsecureServerCredentials());
    
    ServiceImpl service;
    server_builder.RegisterService(&service);

    auto grpc_server = server_builder.BuildAndStart();
    grpc_server->Wait();
}