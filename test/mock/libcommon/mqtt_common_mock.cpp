#include "libmosquitto_common_mock.hpp"


unsigned int mosquitto_varint_bytes(uint32_t word)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_varint_bytes(word);
}
