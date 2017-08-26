#include <string>
#include <msgpack.hpp>

struct Message{
	std::string value;
	std::string gcm_tag;
	long time;
        MSGPACK_DEFINE(value,gcm_tag,time);
};
