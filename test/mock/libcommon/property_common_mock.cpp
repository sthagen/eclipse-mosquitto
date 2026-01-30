#include "libmosquitto_common_mock.hpp"


void mosquitto_property_free(mosquitto_property **property)
{
	LibMosquittoCommonMock::get_mock().mosquitto_property_free(
			property);
}


void mosquitto_property_free_all(mosquitto_property **property)
{
	LibMosquittoCommonMock::get_mock().mosquitto_property_free_all(
			property);
}


unsigned int mosquitto_property_get_length(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_get_length(
			property);
}


unsigned int mosquitto_property_get_length_all(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_get_length_all(
			property);
}


int mosquitto_property_check_command(int command, int identifier)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_check_command(
			command, identifier);
}


const char *mosquitto_property_identifier_to_string(int identifier)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_identifier_to_string(
			identifier);
}


int mosquitto_string_to_property_info(const char *propname, int *identifier, int *type)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_string_to_property_info(
			propname, identifier, type);
}


int mosquitto_property_add_byte(mosquitto_property **proplist, int identifier, uint8_t value)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_add_byte(
			proplist, identifier, value);
}


int mosquitto_property_add_int16(mosquitto_property **proplist, int identifier, uint16_t value)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_add_int16(
			proplist, identifier, value);
}


int mosquitto_property_add_int32(mosquitto_property **proplist, int identifier, uint32_t value)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_add_int32(
			proplist, identifier, value);
}


int mosquitto_property_add_varint(mosquitto_property **proplist, int identifier, uint32_t value)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_add_varint(
			proplist, identifier, value);
}


int mosquitto_property_add_binary(mosquitto_property **proplist, int identifier, const void *value, uint16_t len)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_add_binary(
			proplist, identifier, value, len);
}


int mosquitto_property_add_string(mosquitto_property **proplist, int identifier, const char *value)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_add_string(
			proplist, identifier, value);
}


int mosquitto_property_add_string_pair(mosquitto_property **proplist, int identifier, const char *name, const char *value)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_add_string_pair(
			proplist, identifier, name, value);
}


int mosquitto_property_check_all(int command, const mosquitto_property *properties)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_check_all(
			command, properties);
}


int mosquitto_property_identifier(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_identifier(
			property);
}


int mosquitto_property_type(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_type(
			property);
}


mosquitto_property *mosquitto_property_next(const mosquitto_property *proplist)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_next(
			proplist);
}


const mosquitto_property *mosquitto_property_read_byte(const mosquitto_property *proplist, int identifier, uint8_t *value, bool skip_first)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_read_byte(
			proplist, identifier, value, skip_first);
}


const mosquitto_property *mosquitto_property_read_int16(const mosquitto_property *proplist, int identifier, uint16_t *value, bool skip_first)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_read_int16(
			proplist, identifier, value, skip_first);
}


const mosquitto_property *mosquitto_property_read_int32(const mosquitto_property *proplist, int identifier, uint32_t *value, bool skip_first)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_read_int32(
			proplist, identifier, value, skip_first);
}


const mosquitto_property *mosquitto_property_read_varint(const mosquitto_property *proplist, int identifier, uint32_t *value, bool skip_first)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_read_varint(
			proplist, identifier, value, skip_first);
}


const mosquitto_property *mosquitto_property_read_binary(const mosquitto_property *proplist, int identifier, void **value, uint16_t *len, bool skip_first)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_read_binary(
			proplist, identifier, value, len, skip_first);
}


const mosquitto_property *mosquitto_property_read_string(const mosquitto_property *proplist, int identifier, char **value, bool skip_first)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_read_string(
			proplist, identifier, value, skip_first);
}


const mosquitto_property *mosquitto_property_read_string_pair(const mosquitto_property *proplist, int identifier, char **name, char **value, bool skip_first)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_read_string_pair(
			proplist, identifier, name, value, skip_first);
}


int mosquitto_property_remove(mosquitto_property **proplist, const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_remove(
			proplist, property);
}


int mosquitto_property_copy_all(mosquitto_property **dest, const mosquitto_property *src)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_copy_all(
			dest, src);
}


uint8_t mosquitto_property_byte_value(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_byte_value(
			property);
}


uint16_t mosquitto_property_int16_value(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_int16_value(
			property);
}


uint32_t mosquitto_property_int32_value(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_int32_value(
			property);
}


uint32_t mosquitto_property_varint_value(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_varint_value(
			property);
}


const void *mosquitto_property_binary_value(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_binary_value(
			property);
}


uint16_t mosquitto_property_binary_value_length(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_binary_value_length(
			property);
}


const char *mosquitto_property_string_value(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_string_value(
			property);
}


uint16_t mosquitto_property_string_value_length(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_string_value_length(
			property);
}


const char *mosquitto_property_string_name(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_string_name(
			property);
}


uint16_t mosquitto_property_string_name_length(const mosquitto_property *property)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_string_name_length(
			property);
}


unsigned int mosquitto_property_get_remaining_length(const mosquitto_property *props)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_property_get_remaining_length(
			props);
}
