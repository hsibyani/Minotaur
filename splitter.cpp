#include "zhelpers.hpp"
//#include "zmq.hpp"
#include <string>
#include <functional>
#include "utils.hpp"

//TODO: Need to do something with the zmq::socket

//void osend(const char * rmessage, void* sender) {
//    zmq::socket_t s = (zmq::socket_t) sender;
//    zmq::message_t message;
//    int len = sizeof (rmessage);
//    message.rebuild(len);
//    //std::cout << rmessage << std::endl;
//    sprintf((char *) message.data(), "%s", rmessage);
//    s.send(message);
//
//}

void enclave_execute(std::string smessage, int n, void *sender, StringArray** retmessage, int ** retlen, int * nc) {
    std::string word;
    std::istringstream iss(smessage);

    unsigned int j = 0;
    iss >> word;
    int count = std::distance(std::istream_iterator<std::string>(iss >> std::ws), std::istream_iterator<std::string>());
    //std::cout << count << std::endl;

    //std::cout << "Allocating memory" << std::endl;
    *nc = count; 
    *retmessage = (StringArray *) malloc(sizeof(StringArray));
    (*retmessage)->array = (char**) malloc(count * sizeof (char *));
    //retlen = (int **) malloc(sizeof(int*)); 
    *retlen = (int *)malloc(count * sizeof (int));
    //std::cout<< sizeof((*retmessage)->array) << std::endl;
//    for (int x=0; x<count; x++){
//        std::cout << "Allocating space" << std::endl;
//        (*retmessage)->array[x] = (char *) malloc(count * sizeof(char));
//        std::cout << (*retmessage)->array[x] << std::endl;
//    }
        //std::cout<<"1" << (*retmessage)->array[x]<<std::endl;
    //std::cout<< "Total elements " << count << std::endl;
    
    iss.clear();
    iss.seekg(0);
    
    iss >> word;
    int i = 0;
    while (iss >> word) {
        std::hash<std::string> hasher;
        auto hashed = hasher(word);
        j = hashed % n;
        //std::cout << *retlen[i] << std::endl;
//        std::cout << sizeof(int) << std::endl;
//        std::cout << (*retlen)+i << std::endl;
        *((*retlen)+i) = word.length() + std::to_string(j).length() + 2;
        //*(*retlen+6) = 10;
        //std::cout << *retlen[10] << std::endl;
        
        (*retmessage)->array[i] = (char *) malloc(*((*retlen)+i) * sizeof(char));
        //std::cout << (*retmessage)->array[1] << std::endl;
        //std::cout << "Copy string to return message" << std::endl;
        snprintf((*retmessage)->array[i], *((*retlen)+i), "%d %s", j, word.c_str());
        //std::cout << (*retmessage)->array[i] << std::endl;
        //std::cout<< sizeof((*retmessage)->array) << std::endl;
        i = i+1;
        //osend(message, sender);
    }
}

void* splitter(void *arg, std::vector<std::string> senderIP, std::vector<int> senderPort, 
        std::vector<std::string> receiverIP, std::vector<int> receiverPort) {
    struct Arguments * param = (Arguments*) arg;
    zmq::context_t context(1);
    //zmq::context_t context = zmq_ctx_new();
    zmq::socket_t sender = key_sender_conn(param, context, senderIP, senderPort);
    std::cout << "Splitter: Received the sender socket " << std::endl;

    zmq::socket_t receiver = shuffle_receiver_conn(param, context, receiverIP, receiverPort);

    std::cout << "Starting the splitter worker " << std::endl;

    std::cout << "Reading messages, splitter" << std::endl;
    //  Process tasks forever
    while (1) {

        zmq::message_t message;

        std::string word;
        receiver.recv(&message);
        std::string smessage(static_cast<char*> (message.data()), message.size());
        
        //std::cout << smessage << std::endl;
        std::istringstream iss(smessage);

        int n = param->next_stage;

        StringArray * retmessage = NULL;
        int * retlen_a = NULL;
        int retlen = 0;


        enclave_execute(smessage, n, &sender, &retmessage, &retlen_a, &retlen);

        std::cout << retlen << std::endl;
        for (int k = 0; k < retlen; k++) {
            message.rebuild(retlen_a[k]);

            //std::cout << retlen_a[k] << std::endl;
            snprintf((char *) message.data(), retlen_a[k], "%s", retmessage->array[k]);
            sender.send(message);
            std::cout << retmessage->array[k] << std::endl;
        }

    }
    return NULL;
}
