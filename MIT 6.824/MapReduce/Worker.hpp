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


namespace mapreduce {
class Master;

class Worker{
public:
    Worker(){};
    Worker(Master* master){
        this->master = master;
    }
    bool process_heart();
    bool run_reduce_task();
    bool run_map_task();
    //send location of intermediate file
    void send_completeion();

    int32_t read();
    int32_t local_write();
private:
    Master *master;
};

}

