/* 
 * File:   app.cpp
 * Author: mb
 *
 * Created on May 16, 2017, 4:49 PM
 */

#include <cstdlib>
#include<iostream>
#include "Server.h"
#include "Client.h"
#include <pthread.h>
#include <unistd.h>
#include "utils.hpp"


//using namespace std;

void * spout (void *arg);
void * splitter (void *arg);
void * count(void *arg);
/*
 * 
 */
int main(int argc, char** argv) {
    
    const int count_threads = 1;
    const int split_threads = 1;
    const int spout_threads = 1;
    
    pthread_t spout_t[spout_threads];
    pthread_t split_t[split_threads];
    pthread_t count_t[count_threads];
    std::cout << "Starting the components…" << std::endl;
    
//    struct Arguments arg;
    for (int j=0; j<spout_threads; j++){
        Arguments *arg = new Arguments;
        arg->id = j;
        arg->next_stage = split_threads;
        arg->prev_stage = 0;
        pthread_create(&spout_t[j], NULL, spout, (void*)arg);  
        sleep(1);
        //delete arg;
    }
    for (int j=0; j<split_threads; j++){
        Arguments *arg = new Arguments;
        arg->id = j;
        arg->next_stage = count_threads;
        arg->prev_stage = spout_threads;
        pthread_create(&split_t[j], NULL, splitter, (void*)arg);
        sleep(1);
        //delete arg;
    }
    for (int j=0; j<count_threads; j++){
        Arguments *arg = new Arguments;
        arg->id = j;
        arg->next_stage = 0;
        arg->prev_stage = split_threads;
        pthread_create(&count_t[j], NULL, count, (void*)arg);
        sleep(1);
        //delete arg;
    }
    std::cout << "Started the components…" << std::endl;
    while(true){
        continue;
    }
    return 0;
}

