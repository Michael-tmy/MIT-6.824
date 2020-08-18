/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "protos/mrworker.grpc.pb.h"
#else
#include "mrworker.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mrproto::MapTaskReply;
using mrproto::Task;
using mrproto::InterFileLocs;
using mrproto::InterFileData;

using mrproto::MapWorker;
using mrproto::ReduceWorker;

class MapWorkerClient {
 public:
  MapWorkerClient(std::shared_ptr<Channel> channel)
      : stub_(MapWorker::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string run_task(std::vector<std::string>&& paths) {
    // Data we are sending to the server.
    Task task;
    for (auto& path: paths){
        task.add_filepaths(path);
    }

    // Container for the data we expect from the server.
    MapTaskReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->run_task(&context, task, reply);

    // Act upon its status.
    if (status.ok()) {
        std::vector<std::string> ret;
        for (int i=0; i<reply.locs_size();i++){
            ret[i] = std::move(reply.locs(i));
        }
        return ret;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<MapWorker::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1) {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos) {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=') {
        target_str = arg_val.substr(start_pos + 1);
      } else {
        std::cout << "The only correct argument syntax is --target=" << std::endl;
        return 0;
      }
    } else {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  } else {
    target_str = "localhost:50051";
  }
  MapWorkerClient mapworker(grpc::CreateChannel(
      target_str, grpc::InsecureChannelCredentials()));
  std::vector<std::string> paths;

  paths[0] = std::string("test/map_file_1");
  paths[1] = std::string("test/map_file_2");
  std::string reply = mapworker.run_task(paths);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
