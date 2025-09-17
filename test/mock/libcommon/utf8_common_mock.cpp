#include "libmosquitto_common_mock.hpp"


int mosquitto_validate_utf8(const char *str, int len)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_validate_utf8(
			str, len);
}
