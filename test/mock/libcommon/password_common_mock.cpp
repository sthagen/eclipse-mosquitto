#include "libmosquitto_common_mock.hpp"


int mosquitto_pw_new(struct mosquitto_pw **pw, enum mosquitto_pwhash_type hashtype)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pw_new(
			pw, hashtype);
}


int mosquitto_pw_hash_encoded(struct mosquitto_pw *pw, const char *password)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pw_hash_encoded(
			pw, password);
}


int mosquitto_pw_verify(struct mosquitto_pw *pw, const char *password)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pw_verify(
			pw, password);
}


void mosquitto_pw_set_valid(struct mosquitto_pw *pw, bool valid)
{
	LibMosquittoCommonMock::get_mock().mosquitto_pw_set_valid(
			pw, valid);
}


bool mosquitto_pw_is_valid(struct mosquitto_pw *pw)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pw_is_valid(pw);
}


int mosquitto_pw_decode(struct mosquitto_pw *pw, const char *password)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pw_decode(
			pw, password);
}


const char *mosquitto_pw_get_encoded(struct mosquitto_pw *pw)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pw_get_encoded(pw);
}


int mosquitto_pw_set_param(struct mosquitto_pw *pw, int param, int value)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pw_set_param(
			pw, param, value);
}


void mosquitto_pw_cleanup(struct mosquitto_pw *pw)
{
	LibMosquittoCommonMock::get_mock().mosquitto_pw_cleanup(pw);
}
