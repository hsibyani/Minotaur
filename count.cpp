
#include "zhelpers.hpp"
//#include "zmq.hpp"
#include <string>
#include <map>
#include "helper.hpp"
#include "utils.hpp"

void* count(void *arg)
{
    struct Arguments * param = (Arguments*) arg;
    zmq::context_t context(1);
    zmq::socket_t receiver = key_receiver_conn(param, context, "127.0.0.1", 6000);
    
    std::cout << "Starting the count worker " << std::endl;
    //  Process tasks forever
    std::map<std::string, int> count_map;
    while (1) {

        zmq::message_t message;
        std::string word; 
        receiver.recv(&message);
        std::cout << "Message Received " << std::endl;
        std::string smessage(static_cast<char*>(message.data()), message.size());
        std::istringstream iss(smessage);
        iss >> word;
        //std::cout << word << std::endl;
        iss >> word;
        //std::cout << word << std::endl;
        if (count_map.find(word) != count_map.end()){
            count_map[word]+=1;
        }else{
            count_map[word] = 1;
        }
        std::map<std::string, int > ::iterator it;
        // Printing the counts
        for ( it = count_map.begin(); it != count_map.end(); it++ )
        {
            std::cout << it->first  // string (key)
                      << ':'
                      << it->second   // string's value 
                      << std::endl ;
        }

    }
    return NULL;
}
