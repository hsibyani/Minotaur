#include "zmq.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "utils.hpp"
#include "sSpoutExec.hpp"
#include <fstream>
#include <streambuf>

void* sSpout (void *arg, std::string ip, int port)
{
    zmq::context_t context (1);
    struct Arguments * param = (Arguments*) arg; 
    zmq::socket_t sender = shuffle_sender_conn(param, context, ip, port);
    std::cout << "Sending tasks to workers…\n" << std::endl;
    zmq::message_t message(2);

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    
    std::string spoutMessage ("Hello is it me you are looking for for ?");
    //std::ifstream t("dataset/spam/1.txt");
    //std::string spoutMessage((std::istreambuf_iterator<char>(t)),
//                              std::istreambuf_iterator<char>());    
    int n = param->next_stage;
    int j = 0;
    
    while(1){
         
        enclave_execute(&j,&n);
        
        int len = spoutMessage.length()+std::to_string(j).length()+1;
        message.rebuild(len);
        
        sprintf((char *)message.data(),"%d %s",j,spoutMessage.c_str());
        sender.send(message);
        std::cout << spoutMessage << std::endl;
        //sleep(1);
    }
    return NULL;
}
