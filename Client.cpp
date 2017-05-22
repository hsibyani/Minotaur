//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include "zmq.hpp"
#include <string>
#include <iostream>

void* client (void* i)
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        zmq::message_t request (5);
        memcpy (request.data (), "Hello", 5);
        std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        int size = socket.recv (&reply);
        //std::cout << "Length: " << size << std::endl;
        std::string rpl = std::string(static_cast<char*>(reply.data()), reply.size());
        //std::string * rep = new std::string((char *) reply.data(), size);
        std::cout << "At Client: Received "<< rpl<<" " << request_nbr << std::endl;
    }
    return NULL;
}