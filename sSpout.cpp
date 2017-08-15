#include "zmq.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "utils.hpp"
#include "sSpoutExec.hpp"
#include <fstream>
#include <streambuf>
#include <sstream>

//0 for spam, 1 for ham
//0 for training, 1 for analysis
std::string prepareMessage(int hamOrSpam, int trainingOrAnalysis) {
//    std::string spoutMessage;
    std::string fileLocation;
    int fileNumber;
    if(hamOrSpam) { //HAM
        fileNumber = rand() % 3000 + 1;
        fileLocation = "dataset/ham/";
        fileLocation.append(std::to_string(fileNumber));
        fileLocation.append(".txt");

    } else { //SPAM
        fileNumber = rand() % 1000 + 1;
        fileLocation = "dataset/spam/";
        fileLocation.append(std::to_string(fileNumber));
        fileLocation.append(".txt");
    }

    std::ifstream t(fileLocation);
//   std::string spoutMessage((std::istreambuf_iterator<char>(t)),
    //                            std::istreambuf_iterator<char>());
    std::stringstream buffer;

    buffer << t.rdbuf();
    std::string spoutMessage = buffer.str();

    if(trainingOrAnalysis) {
        spoutMessage = "1 " + std::to_string(fileNumber) + " " + spoutMessage;
    } else {
        if(hamOrSpam) {
            spoutMessage = "0 " + spoutMessage;
        } else {
            spoutMessage = "1 " + spoutMessage;
        }
        spoutMessage = "0 " + spoutMessage;
    }

    return spoutMessage;

}

void* sSpout (void *arg, std::string ip, int port)
{
    zmq::context_t context (1);
    struct Arguments * param = (Arguments*) arg;
    zmq::socket_t sender = shuffle_sender_conn(param, context, ip, port);
    std::cout << "Sending tasks to workers…\n" << std::endl;
    zmq::message_t message(2);

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));

    //std::string spoutMessage ("0 1 Hello is it me you are looking for for ?");
    //std::ifstream t("dataset/spam/1.txt");
    //std::string spoutMessage((std::istreambuf_iterator<char>(t)),
//                              std::istreambuf_iterator<char>());
    int n = param->next_stage;
    int j = 0;

    std::string spoutMessage;

    while(1) {
        int hamOrSpam, trainingOrAnalysis;
        hamOrSpam = rand() % 2; //0 for spam, 1 for ham
        trainingOrAnalysis = rand() % 2;//0 for training, 1 for analysis

        spoutMessage = prepareMessage(hamOrSpam, trainingOrAnalysis);
//       spoutMessage = prepareMessage(0,0);
        int count =0;
        while(count < 100000000) {
            count++;
        }
        enclave_execute(&j,&n);

        int len = spoutMessage.length()+std::to_string(j).length() + 2;
        message.rebuild(len);

        char * cstr = new char [spoutMessage.length()+1];
        std::strcpy (cstr, spoutMessage.c_str());

//        std::cout << "Message len: " << std::endl;
//        std::cout << len << std::endl;
//        std::cout << strlen(spoutMessage.c_str()) << std::endl;

        sprintf((char *)message.data(),"%d %s",j,spoutMessage.c_str());
        sender.send(message);
//        std::cout << spoutMessage << std::endl;
        //sleep(1);
    }
    return NULL;
}
