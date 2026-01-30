#include "libmosquitto_common_mock.hpp"


int mosquitto_pub_topic_check(const char *str)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pub_topic_check(
			str);
}


int mosquitto_pub_topic_check2(const char *str, size_t len)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_pub_topic_check2(
			str, len);
}


int mosquitto_sub_topic_check(const char *str)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_sub_topic_check(
			str);
}


int mosquitto_sub_topic_check2(const char *str, size_t len)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_sub_topic_check2(
			str, len);
}


int mosquitto_sub_matches_acl(const char *acl, const char *sub, bool *result)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_sub_matches_acl(
			acl, sub, result);
}


int mosquitto_sub_matches_acl_with_pattern(const char *acl, const char *sub, const char *clientid, const char *username, bool *result)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_sub_matches_acl_with_pattern(
			acl, sub, clientid, username, result);
}


int mosquitto_topic_matches_sub(const char *sub, const char *topic, bool *result)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_topic_matches_sub(
			sub, topic, result);
}


int mosquitto_topic_matches_sub_with_pattern(const char *sub, const char *topic, const char *clientid, const char *username, bool *result)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_topic_matches_sub_with_pattern(
			sub, topic, clientid, username, result);
}


int mosquitto_topic_matches_sub2(const char *sub, size_t sublen, const char *topic, size_t topiclen, bool *result)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_topic_matches_sub2(
			sub, sublen, topic, topiclen, result);
}


int mosquitto_sub_topic_tokenise(const char *subtopic, char ***topics, int *count)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_sub_topic_tokenise(
			subtopic, topics, count);
}


int mosquitto_sub_topic_tokens_free(char ***topics, int count)
{
	return LibMosquittoCommonMock::get_mock().mosquitto_sub_topic_tokens_free(
			topics, count);
}
