
#include "zhelpers.hpp"
#include <string>
#include <map>
#include "utils.hpp"
#include "Enclave.hpp"

void* count(void *arg, std::string receiverIP, int port)
{
    struct Arguments * param = (Arguments*) arg;
    zmq::context_t context(1);
    zmq::socket_t receiver = key_receiver_conn(param, context, receiverIP, port);
    
    std::cout << "Starting the count worker " << std::endl;
    //  Process tasks forever
    while(1) {
        zmq::message_t message;
        receiver.recv(&message);
        std::cout << "Message Received " << std::endl;
        std::string smessage(static_cast<char*> (message.data()), message.size());
        count_enclave_execute(smessage);
    }
    return NULL;
}
