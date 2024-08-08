// #include <iostream>
// #include <memory>
// #include <string>
// #include <grpcpp/grpcpp.h>
//
// // This would typically be in a separate .proto file and generated
// // For simplicity, we'll define the service and messages here
// namespace remote_object {
//     class Empty {};
//
//     class Value {
//     public:
//         int32_t value() const { return value_; }
//         void set_value(int32_t value) { value_ = value; }
//     private:
//         int32_t value_ = 0;
//     };
//
//     class RemoteObject {
//     public:
//         class Service {
//         public:
//             virtual grpc::Status GetValue(grpc::ServerContext* context, const Empty* request, Value* reply) = 0;
//             virtual grpc::Status SetValue(grpc::ServerContext* context, const Value* request, Empty* reply) = 0;
//             virtual grpc::Status Increment(grpc::ServerContext* context, const Empty* request, Empty* reply) = 0;
//         };
//     };
// }
//
// class RemoteObjectServiceImpl final : public remote_object::RemoteObject::Service {
// public:
//     grpc::Status GetValue(grpc::ServerContext* context, const remote_object::Empty* request, remote_object::Value* reply) override {
//         reply->set_value(value_);
//         return grpc::Status::OK;
//     }
//
//     grpc::Status SetValue(grpc::ServerContext* context, const remote_object::Value* request, remote_object::Empty* reply) override {
//         value_ = request->value();
//         return grpc::Status::OK;
//     }
//
//     grpc::Status Increment(grpc::ServerContext* context, const remote_object::Empty* request, remote_object::Empty* reply) override {
//         value_++;
//         return grpc::Status::OK;
//     }
//
// private:
//     int32_t value_ = 0;
// };
//
// void RunServer() {
//     std::string server_address("0.0.0.0:50051");
//     RemoteObjectServiceImpl service;
//
//     grpc::ServerBuilder builder;
//     builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//     //error: no matching function for call to ‘grpc::ServerBuilder::RegisterService(RemoteObjectServiceImpl*)’
//     //lcan't be fixed by regeneration, ine commented
//     // builder.RegisterService(&service);
//     std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
//     std::cout << "Server listening on " << server_address << std::endl;
//     server->Wait();
// }
//
// class RemoteObjectClient {
// public:
//     //error: ‘Stub’ is not a member of ‘remote_object::RemoteObject’
//     //can't be fixed by regeneration, file is commented
//     RemoteObjectClient(std::shared_ptr<grpc::Channel> channel)
//         : stub_(remote_object::RemoteObject::NewStub(channel)) {}
//
//     int GetValue() {
//         grpc::ClientContext context;
//         remote_object::Empty request;
//         remote_object::Value reply;
//         grpc::Status status = stub_->GetValue(&context, request, &reply);
//         if (status.ok()) {
//             return reply.value();
//         } else {
//             std::cout << "RPC failed: " << status.error_message() << std::endl;
//             return -1;
//         }
//     }
//
//     void SetValue(int value) {
//         grpc::ClientContext context;
//         remote_object::Value request;
//         request.set_value(value);
//         remote_object::Empty reply;
//         grpc::Status status = stub_->SetValue(&context, request, &reply);
//         if (!status.ok()) {
//             std::cout << "RPC failed: " << status.error_message() << std::endl;
//         }
//     }
//
//     void Increment() {
//         grpc::ClientContext context;
//         remote_object::Empty request;
//         remote_object::Empty reply;
//         grpc::Status status = stub_->Increment(&context, request, &reply);
//         if (!status.ok()) {
//             std::cout << "RPC failed: " << status.error_message() << std::endl;
//         }
//     }
//
// private:
//     std::unique_ptr<remote_object::RemoteObject::Stub> stub_;
// };
//
// void RunClient() {
//     RemoteObjectClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
//
//     std::cout << "Initial value: " << client.GetValue() << std::endl;
//
//     client.SetValue(10);
//     std::cout << "After setting value to 10: " << client.GetValue() << std::endl;
//
//     client.Increment();
//     std::cout << "After incrementing: " << client.GetValue() << std::endl;
// }
//
// int main(int argc, char** argv) {
//     if (argc > 1 && std::string(argv[1]) == "server") {
//         RunServer();
//     } else {
//         RunClient();
//     }
//     return 0;
// }