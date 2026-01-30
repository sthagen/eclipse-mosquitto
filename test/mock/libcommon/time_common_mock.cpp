#include "libmosquitto_common_mock.hpp"


void mosquitto_time_init(void)
{
	LibMosquittoCommonMock::get_mock().mosquitto_time_init();
}


time_t mosquitto_time(void)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_time();
}


void mosquitto_time_ns(time_t *s, long *ns)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_time_ns(
			s, ns);
}


long mosquitto_time_cmp(time_t t1_s, long t1_ns, time_t t2_s, long t2_ns)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_time_cmp(
			t1_s, t1_ns, t2_s, t2_ns);
}
