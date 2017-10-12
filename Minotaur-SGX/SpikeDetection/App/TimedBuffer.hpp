// classes example
#include <iostream>
#include <msgpack.hpp>
#include <map>
#include "zhelpers.hpp"
#include "zmq.hpp"
#include <time.h>
#include "utils.hpp"
using namespace std;

class TimedBuffer {
    std::map<int, std::vector<std::string>> data_vector, gcm_vector;
    unsigned long startMicro;
    zmq::context_t* context = new zmq::context_t(1);
    zmq::socket_t* sender = new zmq::socket_t(*context, ZMQ_PAIR);
    zmq::message_t* message;
public:
    TimedBuffer(zmq::context_t * context, zmq::socket_t * s);
    void check_and_send();
    void add_msg(int, std::string, std::string);

};
