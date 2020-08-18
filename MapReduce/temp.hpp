//
//  temp.hpp
//  MIT 6.824
//
//  Created by 段世博 on 2020/8/3.
//  Copyright © 2020 段世博. All rights reserved.
//
#pragma once
#ifndef temp_h
#define temp_h


#endif /* temp_h */
#include <string>
#include <vector>

namespace mapreduce {

class RemoteReadArgs{
    
};
struct Task{
    std::string filepaths;
    
};

class WorkService{
    
};

class MapWorkerService{
    virtual bool run_task(Task task)=0;
    virtual int64_t remote_read(RemoteReadArgs args)=0;
};

class ReduceWorkerService{
    virtual bool run_task(Task task)=0;
};

class MasterService{
    virtual bool process_map_completion();
    virtual bool process_reduce_completion();
};
}
