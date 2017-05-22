#include "zhelpers.hpp"
//#include "zmq.hpp"
#include <string>
#include <functional>
#include "helper.hpp"

void* splitter(void *arg)
{
    zmq::context_t context(1);
    struct arguments * param = (arguments*) arg;
    //  Socket to receive messages on
    zmq::socket_t receiver(context, ZMQ_SUB);
//    receiver.connect("tcp://127.0.0.1:5557");
    for (int i = 0; i<param->prev_stage;i++){
        receiver.connect("tcp://127.0.0.1:"+std::to_string(5000+i));
    }
    
    const char * filter = std::to_string(param->id).c_str();
    receiver.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

    //  Socket to send messages to
    zmq::socket_t sender(context, ZMQ_PUB);
//    for (int i = 0; i<param->next_stage;i++){
//        sender.connect("tcp://127.0.0.1:"+std::to_string(6000+i));
//    }
    sender.connect("tcp://localhost:5558");

    //  Process tasks forever
    while (1) {

        zmq::message_t message;
//        int workload;           //  Workload in msecs

        std::string word; 
        receiver.recv(&message);
        std::string smessage(static_cast<char*>(message.data()), message.size());

        std::istringstream iss(smessage);
        
        int n = param->next_stage;
        int j = 0;
        iss >> word;
        while(iss >> word){
            //std::cout << word << std::endl;
            std::hash<std::string> hasher;
            auto hashed = hasher(word);
            j = hashed % n;
            int len = word.length()+std::to_string(j).length()+1;
            message.rebuild(len);
         
            sprintf((char *)message.data(),"%d %s",j,word.c_str());
            sender.send(message);
            std::cout<< word << std::endl;
        }
//        iss >> workload;

        //  Do the work
//        s_sleep(workload);

        //  Send results to sink


        //  Simple progress indicator for the viewer
//        std::cout << "." << std::flush;
    }
    return NULL;
}
