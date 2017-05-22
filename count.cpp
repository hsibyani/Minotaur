
#include "zhelpers.hpp"
//#include "zmq.hpp"
#include <string>
#include <map>
#include "helper.hpp"

void* count(void *arg)
{
    struct arguments * param = (arguments*) arg;
    zmq::context_t context(1);

    std::cout << "Starting the count worker " << std::endl;
    //  Socket to receive messages on
    zmq::socket_t receiver(context, ZMQ_SUB);

    //receiver.bind("tcp://127.0.0.1:"+std::to_string(6000+param->id));
    receiver.connect("tcp://localhost:5558");
   
    const char * filter = std::to_string(param->id).c_str();
    receiver.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
    //  Socket to send messages to
//    zmq::socket_t sender(context, ZMQ_PUSH);
//    sender.connect("tcp://localhost:5558");

    //  Process tasks forever
    std::map<std::string, int> count_map;
    while (1) {

        zmq::message_t message;
//        int workload;           //  Workload in msecs

        std::string word; 
        receiver.recv(&message);
        std::string smessage(static_cast<char*>(message.data()), message.size());
        std::istringstream iss(smessage);
        iss >> word;
        iss >> word;
        std::cout << word << std::endl;
        if (count_map.find(word) != count_map.end()){
            count_map[word]+=1;
        }else{
            count_map[word] = 1;
        }
        std::map<std::string, int > ::iterator it;
//        for ( it = count_map.begin(); it != count_map.end(); it++ )
//        {
//            std::cout << it->first  // string (key)
//                      << ':'
//                      << it->second   // string's value 
//                      << std::endl ;
//        }

//        std::cout << "Count side " << smessage << std::endl;
//        std::istringstream iss(smessage);
//        
//        while(iss >> word){
//            std::cout << word << std::endl;
//        }
//        iss >> workload;

        //  Do the work
//        s_sleep(workload);

        //  Send results to sink
//        message.rebuild();
//        sender.send(message);

        //  Simple progress indicator for the viewer
//        std::cout << "." << std::flush;
    }
    return NULL;
}
