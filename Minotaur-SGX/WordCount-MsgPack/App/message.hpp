#include <string>
#include <msgpack.hpp>

struct Message{
	std::string value;
	std::string gcm_tag;
	long latency;
	long timeSec;
	long timeNSec;
        MSGPACK_DEFINE(value,gcm_tag,latency, timeSec, timeNSec);
};
