//
//  Worker.h
//  MIT 6.824
//
//  Created by 段世博 on 2020/8/3.
//  Copyright © 2020 段世博. All rights reserved.
//

#ifndef Worker_h
#define Worker_h


#endif /* Worker_h */
#include <memory>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "temp.hpp"

namespace mapreduce {
class MasterClient;

class MapWorker:public MapWorkerService{
public:
    bool run_task(Task task) override;
    int64_t remote_read(RemoteReadArgs args) override;
    
private:
    int64_t _read(std::string filepath);
    int64_t _local_write(std::string filepath);
    
    //compute the key in which spilt
    uint32_t _partition(const std::string& key);
    
    //combine in one file
    void _sort_and_combiner();
    //combine across all spilt file
    void _combiner_and_merge();
    
    std::unique_ptr<MasterClient> master_client;
};

class ReduceWorker:public ReduceWorkerService{
public:
    bool run_task(Task task) override;

private:
    int64_t _write(std::string addr, std::string filepath);
    
    void _merge();
    
    std::unique_ptr<MasterClient> master_client;
    std::vector<std::unique_ptr<MasterClient>> worker_clients;
};

class MasterClient{
public:
    MasterClient(std::string addr){
        
    }
    
    void process_map_completion();
    void process_reduce_completion();
private:
    std::string master_addr;
    //std::unique_ptr<> stub_;
};

}

