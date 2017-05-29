#include "zhelpers.hpp"
//#include "zmq.hpp"
#include <string>
#include <functional>
#include "helper.hpp"
#include "utils.hpp"

void* splitter(void *arg)
{
    struct Arguments * param = (Arguments*) arg;
    zmq::context_t context(1);
    //zmq::context_t context = zmq_ctx_new();
    zmq::socket_t sender = key_sender_conn(param, context, "127.0.0.1", 6000);
    std::cout << "Splitter: Received the sender socket " << std::endl;

    zmq::socket_t receiver = shuffle_receiver_conn(param, context, "127.0.0.1", 5000);
    
    std::cout << "Starting the splitter worker " << std::endl;

    std::cout << "Reading messages, splitter" << std::endl;
    //  Process tasks forever
    while (1) {

        zmq::message_t message;
        
        std::string word; 
        receiver.recv(&message);
        std::string smessage(static_cast<char*>(message.data()), message.size());

        std::istringstream iss(smessage);
        
        int n = param->next_stage;
        unsigned int j = 0;
        iss >> word;
        while(iss >> word){
            std::hash<std::string> hasher;
            auto hashed = hasher(word);
            j = hashed % n;
            //std::cout<< hashed << " " << n << std::endl;
            int len = word.length()+std::to_string(j).length()+1;
            message.rebuild(len);
         
            sprintf((char *)message.data(),"%d %s",j,word.c_str());
            sender.send(message);
            std::cout<<j <<word.c_str()<< std::endl;
        }
    }
    return NULL;
}
