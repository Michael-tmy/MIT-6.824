//
//  Worker.cpp
//  MIT 6.824
//
//  Created by 段世博 on 2020/8/3.
//  Copyright © 2020 段世博. All rights reserved.
//

#include <stdio.h>
#include "Worker.hpp"
#include "temp.hpp"

namespace mapreduce {

bool MapWorker::run_task(Task task){
    _read(task.filepaths);
    
    //map()
    _sort_and_combiner();
    _combiner_and_merge();
    
    master_client->process_map_completion();
    return true;
}

int64_t MapWorker::remote_read(RemoteReadArgs args){
    //invoke _stub
    
    return 0;
}

int64_t MapWorker::_read(std::string filepath){
    
    return 0;
}

int64_t MapWorker::_local_write(std::string filepath){
    uint32_t index = _partition(filepath);
    //Buffer buffer
    //buffer.append(key,value);
    
    return 0;
}

bool ReduceWorker::run_task(Task task){
    //TODO
    //read data and invoke the reduce write by users
    //finally write the result to file
    for (const auto& worker_client: worker_clients){
        //worker_client->remote_read();
    }
    _merge();
    
    //reduce()
    master_client->process_reduce_completion();
    return true;
}

int64_t ReduceWorker::_write(std::string addr, std::string filepath){
    return 0;
}

void MasterClient::process_map_completion(){
    
}

void MasterClient::process_reduce_completion(){
    
}

}
