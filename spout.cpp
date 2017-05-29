#include "zmq.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "helper.hpp"
#include "utils.hpp"

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

void* spout (void *arg)
{
    zmq::context_t context (1);
    struct Arguments * param = (Arguments*) arg; 
    zmq::socket_t sender = shuffle_sender_conn(param, context, "127.0.0.1", 5000);
    std::cout << "Sending tasks to workers…\n" << std::endl;
    zmq::message_t message(2);


    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    
    std::string sentence ("Hello is it me you are looking for ?");
    int n = param->next_stage;
    int j = 0;
    while(1){
        j = j% n;
        int len = sentence.length()+std::to_string(j).length()+1;
        message.rebuild(len);
        
        sprintf((char *)message.data(),"%d %s",j,sentence.c_str());
        //std::cout << "Sending "<<sentence << "to" << j<< std::endl;

        j++;
        sender.send(message);
        sleep(1);
    }
    return NULL;
}
