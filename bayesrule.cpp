#include "zhelpers.hpp"
//#include "zmq.hpp"
#include <string>
#include <functional>
#include "utils.hpp"
#include "bayesruleExec.hpp"
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

//void* bayesrule(void *arg, std::string receiverIP, int port){
void* bayesrule(void *arg, std::vector<std::string> senderIP, std::vector<int> senderPort,
        std::vector<std::string> receiverIP, std::vector<int> receiverPort) {

    std::cout << "in bayes" << std::endl;
    struct Arguments * param = (Arguments*) arg;
    zmq::context_t context(1);
    zmq::socket_t receiver = key_receiver_conn(param, context, receiverIP.front(), receiverPort.front());
//        zmq::socket_t receiver = key_receiver_conn(param, context, receiverIP, port);

        //zmq::socket_t receiver = shuffle_receiver_conn(param, context, receiverIP, receiverPort);

    std::cout << "Bayesrule: Received the sender socket " << std::endl;

    std::cout << "Starting the bayesrule worker " << std::endl;

    std::cout << "Reading messages, bayesrule" << std::endl;
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

        std::cout << "BEGIN" << std::endl;
        std::cout << smessage << std::endl;
        enclave_execute_br(smessage, n, &retmessage, &retlen_a, &retlen);
        std::cout << "END" << std::endl;

        std::cout << retlen << std::endl;
        for (int k = 0; k < retlen; k++) {
            message.rebuild(retlen_a[k]);

            //std::cout << retlen_a[k] << std::endl;
            snprintf((char *) message.data(), retlen_a[k], "%s", retmessage->array[k]);
            std::cout << retmessage->array[k] << std::endl;
        }

    }
    return NULL;
}
