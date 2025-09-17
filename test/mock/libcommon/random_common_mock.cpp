#include "libmosquitto_common_mock.hpp"


int mosquitto_getrandom(void *bytes, int count)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_getrandom(
			bytes, count);
}
