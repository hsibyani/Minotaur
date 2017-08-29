#include <string>
#include <msgpack.hpp>

struct Message{
	std::string value;
	long timeSec;
	long timeNSec;
        MSGPACK_DEFINE(value,timeSec, timeNSec);
};
