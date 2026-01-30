#include "libmosquitto_common_mock.hpp"


void mosquitto_memory_set_limit(size_t lim)
{
	LibMosquittoCommonMock::get_mock().mosquitto_memory_set_limit(lim);
}


unsigned long mosquitto_memory_used(void)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_memory_used();
}


unsigned long mosquitto_max_memory_used(void)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_max_memory_used();
}


void *mosquitto_malloc(size_t size)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_malloc(size);
}


void *mosquitto_realloc(void *ptr, size_t size)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_realloc(ptr, size);
}


void mosquitto_free(void *mem)
{
	LibMosquittoCommonMock::get_mock().mosquitto_free(mem);
}


void *mosquitto_calloc(size_t nmemb, size_t size)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_calloc(nmemb, size);
}


char *mosquitto_strdup(const char *s)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_strdup(s);
}


char *mosquitto_strndup(const char *s, size_t n)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_strndup(s, n);
}
