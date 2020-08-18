//
//  Master.cpp
//  MIT 6.824
//
//  Created by 段世博 on 2020/8/3.
//  Copyright © 2020 段世博. All rights reserved.
//

#include "Master.hpp"

namespace mapreduce {

bool Master::run_map_task(std::string& key,Task* task){
    //多线程需要线程安全
    mapTrackers[key].status = Status::RUNNING;
    mapTrackers[key].task = task;
    
    //asyns invoke the map worker's function
    Result result;
    //create channel
    
    
    _remote_run_map_task(key,task,&result);
    mapResults.emplace_back(std::move(result));
    reduceTrackers[key].status = Status::IDLE;
    return true;
}

bool Master:: run_reduce_task(std::string& key,Task* task){
    reduceTrackers[key].status = Status::RUNNING;
    reduceTrackers[key].task = task;
    
    //asyns invoke the map worker's function
    Result result;
    reduceResults.emplace_back(std::move(result));
    return true;
}

bool Master::process_reduce_completion(std::string key,Task task){
    //修改Task状态
    reduceTrackers[key].status = Status::IDLE;
    run_reduce_task();
    return true;
}

bool Master::process_map_completion(std::string key,Task task){
    //修改Task状态
    mapTrackers[key].status = Status::IDLE;
    return true;
}

void Master::_process_fault(){
    
}
}
