#include "libmosquitto_common_mock.hpp"


cJSON *mosquitto_properties_to_json(const mosquitto_property *properties)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_properties_to_json(
			properties);
}
