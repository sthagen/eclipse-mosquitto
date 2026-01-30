#include "libmosquitto_common_mock.hpp"


int mosquitto_base64_encode(const unsigned char *in, size_t in_len, char **encoded)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_base64_encode(
			in, in_len, encoded);
}


int mosquitto_base64_decode(const char *in, unsigned char **decoded, unsigned int *decoded_len)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_base64_decode(
			in, decoded, decoded_len);
}
