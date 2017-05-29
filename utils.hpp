/* 
 * File:   utils.hpp
 * Author: mb
 *
 * Created on May 29, 2017, 1:25 PM
 */

#ifndef UTILS_HPP
#define	UTILS_HPP



#endif	/* UTILS_HPP */

zmq::socket_t key_receiver_conn(Arguments * param, zmq::context_t & context, std::string ip, int port);
zmq::socket_t key_sender_conn(Arguments * param, zmq::context_t & context, std::string ip, int port);
zmq::socket_t shuffle_receiver_conn(Arguments * param, zmq::context_t & context, std::string ip, int port);
zmq::socket_t shuffle_sender_conn(Arguments * param, zmq::context_t & context, std::string ip, int port);