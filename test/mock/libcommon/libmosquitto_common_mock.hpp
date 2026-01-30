#pragma once

#include <gmock/gmock.h>
#include <mosquitto.h>

#include "c_function_mock.hpp"

class LibMosquittoCommonMock : public CFunctionMock<LibMosquittoCommonMock> {
	public:
		LibMosquittoCommonMock();
		virtual ~LibMosquittoCommonMock();

		/* base64_common.c */
		MOCK_METHOD(int, mosquitto_base64_encode, (const unsigned char *in, size_t in_len, char **encoded));
		MOCK_METHOD(int, mosquitto_base64_decode, (const char *in, unsigned char **decoded, unsigned int *decoded_len));

		/* cjson_common.c */
		MOCK_METHOD(cJSON *, mosquitto_properties_to_json, (const mosquitto_property *properties));

		/* file_common.c */
		MOCK_METHOD(FILE *, mosquitto_fopen, (const char *path, const char *mode, bool restrict_read));
		MOCK_METHOD(char *, mosquitto_trimblanks, (char *str));
		MOCK_METHOD(char *, mosquitto_fgets, (char **buf, int *buflen, FILE *stream));
		MOCK_METHOD(int, mosquitto_write_file, (const char* target_path, bool restrict_read,
					int (*write_fn)(FILE* fptr, void* user_data), void* user_data, void (*log_fn)(const char* msg)));
		MOCK_METHOD(int, mosquitto_read_file, (const char *file, char **buf, size_t *buflen));

		/* memory_common.c */
		MOCK_METHOD(void, mosquitto_memory_set_limit, (size_t lim));
		MOCK_METHOD(unsigned long, mosquitto_memory_used, ());
		MOCK_METHOD(unsigned long, mosquitto_max_memory_used, ());
		MOCK_METHOD(void *, mosquitto_malloc, (size_t size));
		MOCK_METHOD(void *, mosquitto_realloc, (void *ptr, size_t size));
		MOCK_METHOD(void, mosquitto_free, (void *mem));
		MOCK_METHOD(void *, mosquitto_calloc, (size_t nmemb, size_t size));
		MOCK_METHOD(char *, mosquitto_strdup, (const char *s));
		MOCK_METHOD(char *, mosquitto_strndup, (const char *s, size_t n));

		/* mqtt_common.c */
		MOCK_METHOD(unsigned int, mosquitto_varint_bytes, (uint32_t word));

		/* password_common.c */
		MOCK_METHOD(int, mosquitto_pw_new, (struct mosquitto_pw **pw, enum mosquitto_pwhash_type hashtype));
		MOCK_METHOD(int, mosquitto_pw_hash_encoded, (struct mosquitto_pw *pw, const char *password));
		MOCK_METHOD(int, mosquitto_pw_verify, (struct mosquitto_pw *pw, const char *password));
		MOCK_METHOD(void, mosquitto_pw_set_valid, (struct mosquitto_pw *pw, bool valid));
		MOCK_METHOD(bool, mosquitto_pw_is_valid, (struct mosquitto_pw *pw));
		MOCK_METHOD(int, mosquitto_pw_decode, (struct mosquitto_pw *pw, const char *password));
		MOCK_METHOD(const char *, mosquitto_pw_get_encoded, (struct mosquitto_pw *pw));
		MOCK_METHOD(int, mosquitto_pw_set_param, (struct mosquitto_pw *pw, int param, int value));
		MOCK_METHOD(void, mosquitto_pw_cleanup, (struct mosquitto_pw *pw));

		/* property_common.c */
		MOCK_METHOD(void, mosquitto_property_free, (mosquitto_property **property));
		MOCK_METHOD(void, mosquitto_property_free_all, (mosquitto_property **property));
		MOCK_METHOD(unsigned int, mosquitto_property_get_length, (const mosquitto_property *property));
		MOCK_METHOD(unsigned int, mosquitto_property_get_length_all, (const mosquitto_property *property));
		MOCK_METHOD(int, mosquitto_property_check_command, (int command, int identifier));
		MOCK_METHOD(const char *, mosquitto_property_identifier_to_string, (int identifier));
		MOCK_METHOD(int, mosquitto_string_to_property_info, (const char *propname, int *identifier, int *type));
		MOCK_METHOD(int, mosquitto_property_add_byte, (mosquitto_property **proplist, int identifier, uint8_t value));
		MOCK_METHOD(int, mosquitto_property_add_int16, (mosquitto_property **proplist, int identifier, uint16_t value));
		MOCK_METHOD(int, mosquitto_property_add_int32, (mosquitto_property **proplist, int identifier, uint32_t value));
		MOCK_METHOD(int, mosquitto_property_add_varint, (mosquitto_property **proplist, int identifier, uint32_t value));
		MOCK_METHOD(int, mosquitto_property_add_binary, (mosquitto_property **proplist, int identifier, const void *value, uint16_t len));
		MOCK_METHOD(int, mosquitto_property_add_string, (mosquitto_property **proplist, int identifier, const char *value));
		MOCK_METHOD(int, mosquitto_property_add_string_pair, (mosquitto_property **proplist, int identifier, const char *name, const char *value));
		MOCK_METHOD(int, mosquitto_property_check_all, (int command, const mosquitto_property *properties));
		MOCK_METHOD(int, mosquitto_property_identifier, (const mosquitto_property *property));
		MOCK_METHOD(int, mosquitto_property_type, (const mosquitto_property *property));
		MOCK_METHOD(mosquitto_property *, mosquitto_property_next, (const mosquitto_property *proplist));
		MOCK_METHOD(const mosquitto_property *, mosquitto_property_read_byte, (const mosquitto_property *proplist, int identifier, uint8_t *value, bool skip_first));
		MOCK_METHOD(const mosquitto_property *, mosquitto_property_read_int16, (const mosquitto_property *proplist, int identifier, uint16_t *value, bool skip_first));
		MOCK_METHOD(const mosquitto_property *, mosquitto_property_read_int32, (const mosquitto_property *proplist, int identifier, uint32_t *value, bool skip_first));
		MOCK_METHOD(const mosquitto_property *, mosquitto_property_read_varint, (const mosquitto_property *proplist, int identifier, uint32_t *value, bool skip_first));
		MOCK_METHOD(const mosquitto_property *, mosquitto_property_read_binary, (const mosquitto_property *proplist, int identifier, void **value, uint16_t *len, bool skip_first));
		MOCK_METHOD(const mosquitto_property *, mosquitto_property_read_string, (const mosquitto_property *proplist, int identifier, char **value, bool skip_first));
		MOCK_METHOD(const mosquitto_property *, mosquitto_property_read_string_pair, (const mosquitto_property *proplist, int identifier, char **name, char **value, bool skip_first));
		MOCK_METHOD(int, mosquitto_property_remove, (mosquitto_property **proplist, const mosquitto_property *property));
		MOCK_METHOD(int, mosquitto_property_copy_all, (mosquitto_property **dest, const mosquitto_property *src));
		MOCK_METHOD(uint8_t, mosquitto_property_byte_value, (const mosquitto_property *property));
		MOCK_METHOD(uint16_t, mosquitto_property_int16_value, (const mosquitto_property *property));
		MOCK_METHOD(uint32_t, mosquitto_property_int32_value, (const mosquitto_property *property));
		MOCK_METHOD(uint32_t, mosquitto_property_varint_value, (const mosquitto_property *property));
		MOCK_METHOD(const void *, mosquitto_property_binary_value, (const mosquitto_property *property));
		MOCK_METHOD(uint16_t, mosquitto_property_binary_value_length, (const mosquitto_property *property));
		MOCK_METHOD(const char *, mosquitto_property_string_value, (const mosquitto_property *property));
		MOCK_METHOD(uint16_t, mosquitto_property_string_value_length, (const mosquitto_property *property));
		MOCK_METHOD(const char *, mosquitto_property_string_name, (const mosquitto_property *property));
		MOCK_METHOD(uint16_t, mosquitto_property_string_name_length, (const mosquitto_property *property));
		MOCK_METHOD(unsigned int, mosquitto_property_get_remaining_length, (const mosquitto_property *props));

		/* random_common.c */
		MOCK_METHOD(int, mosquitto_getrandom, (void *bytes, int count));

		/* strings_common.c */
		MOCK_METHOD(const char *, mosquitto_strerror, (int mosq_errno));
		MOCK_METHOD(const char *, mosquitto_connack_string, (int connack_code));
		MOCK_METHOD(const char *, mosquitto_reason_string, (int reason_code));
		MOCK_METHOD(int, mosquitto_string_to_command, (const char *str, int *cmd));

		/* time_common.c */
		MOCK_METHOD(void, mosquitto_time_init, ());
		MOCK_METHOD(time_t, mosquitto_time, ());
		MOCK_METHOD(void, mosquitto_time_ns, (time_t *s, long *ns));
		MOCK_METHOD(long, mosquitto_time_cmp, (time_t t1_s, long t1_ns, time_t t2_s, long t2_ns));

		/* topic_common.c */
		MOCK_METHOD(int, mosquitto_pub_topic_check, (const char *str));
		MOCK_METHOD(int, mosquitto_pub_topic_check2, (const char *str, size_t len));
		MOCK_METHOD(int, mosquitto_sub_topic_check, (const char *str));
		MOCK_METHOD(int, mosquitto_sub_topic_check2, (const char *str, size_t len));
		MOCK_METHOD(int, mosquitto_sub_matches_acl, (const char *acl, const char *sub, bool *result));
		MOCK_METHOD(int, mosquitto_sub_matches_acl_with_pattern, (const char *acl, const char *sub, const char *clientid, const char *username, bool *result));
		MOCK_METHOD(int, mosquitto_topic_matches_sub, (const char *sub, const char *topic, bool *result));
		MOCK_METHOD(int, mosquitto_topic_matches_sub_with_pattern, (const char *sub, const char *topic, const char *clientid, const char *username, bool *result));
		MOCK_METHOD(int, mosquitto_topic_matches_sub2, (const char *sub, size_t sublen, const char *topic, size_t topiclen, bool *result));
		MOCK_METHOD(int, mosquitto_sub_topic_tokenise, (const char *subtopic, char ***topics, int *count));
		MOCK_METHOD(int, mosquitto_sub_topic_tokens_free, (char ***topics, int count));

		/* utf8_common.c */
		MOCK_METHOD(int, mosquitto_validate_utf8, (const char *str, int len));

};
