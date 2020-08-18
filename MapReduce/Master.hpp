//
//  Master.hpp
//  MIT 6.824
//
//  Created by 段世博 on 2020/8/3.
//  Copyright © 2020 段世博. All rights reserved.
//

#ifndef Master_hpp
#define Master_hpp

#include <stdio.h>

#endif /* Master_hpp */

#include <memory>
#include <map>
#include "temp.hpp"


namespace mapreduce {
class WorkerClient;
struct Result{
    std::string filepath;
};

class Master:public MasterService{
public:
    Master(uint32_t mNum,uint32_t rNum)
    :mWorkerNum(mNum),
    rWorkerNum(rNum)
    {
        
    }
    ~Master();
    bool process_map_completion() override;
    bool process_reduce_completion() override;

private:
    enum Status{
        IDLE,
        RUNNING,
        FAILED,
    };
    struct MapTracker{
        Task* task;
        Status status;
    };
    
    struct ReduceTracker{
        Task* task;
        Status status;
    };
    typedef std::string Addr;
    
    void _process_fault();
    Addr& _get_next_map_woker_addr(){
        return mWokersAddr[(++mcur)%mWorkerNum];
    }
    
    Addr& _get_next_reduce_woker_addr(){
        return rWorkersAddr[(++rcur)%rWorkerNum];
    }
    
    uint32_t mWorkerNum;    //atomic
    uint32_t rWorkerNum;    //atomic
    
    uint32_t mcur = 0;
    uint32_t rcur = 0;
    std::vector<Addr> mWokersAddr;
    std::vector<Addr> rWorkersAddr;
    
    std::vector<Result> mapResults;
    std::vector<Result> reduceResults;
    std::vector<std::unique_ptr<WorkerClient>> workerClients;
    std::map<std::string,MapTracker> mapTrackers;
    std::map<std::string,ReduceTracker> reduceTrackers;
};

class WorkerClient{
    
};
}
