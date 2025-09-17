#include "libmosquitto_common_mock.hpp"


const char *mosquitto_strerror(int mosq_errno)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_strerror(
			mosq_errno);
}


const char *mosquitto_connack_string(int connack_code)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_connack_string(
			connack_code);
}


const char *mosquitto_reason_string(int reason_code)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_reason_string(
			reason_code);
}


int mosquitto_string_to_command(const char *str, int *cmd)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_string_to_command(
			str, cmd);
}
