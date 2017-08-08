#include "zhelpers.hpp"
//#include "zmq.hpp"
#include <string>
#include <functional>
#include "utils.hpp"
#include "sSplitExec.hpp"
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

void* sSplitter(void *arg, std::vector<std::string> senderIP, std::vector<int> senderPort, 
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
        
        std::cout << "MESSAGE" << std::endl;
        std::cout << smessage << std::endl;
        std::istringstream iss(smessage);

        int n = param->next_stage;
        std::cout << "n" << std::endl;
        std::cout << n << std::endl;
//        int n = 1;

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
