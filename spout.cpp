#include "zmq.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "utils.hpp"
//void execute(zmq::socket_t sender){
//    
//}

// Needs to happen in enclave
int enclave_shuffle_routing(int j, int n){
    j++;
    j = j% n;
    return j;
}

// What needs to happen within the enclave?
void enclave_execute(int* j, int* n){
        *j = enclave_shuffle_routing(*j,*n);
        //return j;
}

void* spout (void *arg)
{
    zmq::context_t context (1);
    struct Arguments * param = (Arguments*) arg; 
    zmq::socket_t sender = shuffle_sender_conn(param, context, "127.0.0.1", 5000);
    std::cout << "Sending tasks to workers…\n" << std::endl;
    zmq::message_t message(2);

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    
    std::string sentence ("Hello is it me you are looking for?");
    int n = param->next_stage;
    int j = 0;
    
    while(1){
         
        enclave_execute(&j,&n);
        
        int len = sentence.length()+std::to_string(j).length()+1;
        message.rebuild(len);
        
        sprintf((char *)message.data(),"%d %s",j,sentence.c_str());
        sender.send(message);
        //sleep(1);
    }
    return NULL;
}
