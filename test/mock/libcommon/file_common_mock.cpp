#include "libmosquitto_common_mock.hpp"


FILE *mosquitto_fopen(const char *path, const char *mode, bool restrict_read)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_fopen(
			path, mode, restrict_read);
}


char *mosquitto_trimblanks(char *str)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_trimblanks(str);
}


char *mosquitto_fgets(char **buf, int *buflen, FILE *stream)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_fgets(buf, buflen, stream);
}


int mosquitto_write_file(const char *target_path, bool restrict_read, int (*write_fn)(FILE *fptr, void *user_data), void *user_data, void (*log_fn)(const char *msg))
{
	return LibMosquittoCommonMock::get_mock().mosquitto_write_file(
			target_path, restrict_read, write_fn, user_data, log_fn);
}


int mosquitto_read_file(const char *file, char **buf, size_t *buflen)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_read_file(
			file, buf, buflen);
}
