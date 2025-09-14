#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <mosquitto/broker.h>
#include <mosquitto/broker_plugin.h>

#define UNUSED(A) (void)(A)

static int handle_tick(int event, void *event_data, void *user_data);
static int handle_connect(int event, void *event_data, void *user_data);
static int handle_disconnect(int event, void *event_data, void *user_data);

static mosquitto_plugin_id_t *plg_id;
static char *last_clientid = NULL;
static int can_kick = 0;


int mosquitto_plugin_version(int supported_version_count, const int *supported_versions)
{
	UNUSED(supported_version_count);
	UNUSED(supported_versions);

	return 5;
}


int mosquitto_plugin_init(mosquitto_plugin_id_t *identifier, void **user_data, struct mosquitto_opt *auth_opts, int auth_opt_count)
{
	UNUSED(user_data);
	UNUSED(auth_opts);
	UNUSED(auth_opt_count);

	plg_id = identifier;

	mosquitto_callback_register(plg_id, MOSQ_EVT_BASIC_AUTH, handle_connect, NULL, NULL);
	mosquitto_callback_register(plg_id, MOSQ_EVT_DISCONNECT, handle_disconnect, NULL, NULL);
	mosquitto_callback_register(plg_id, MOSQ_EVT_CLIENT_OFFLINE, handle_disconnect, NULL, NULL);
	mosquitto_callback_register(plg_id, MOSQ_EVT_TICK, handle_tick, NULL, NULL);

	return MOSQ_ERR_SUCCESS;
}


int mosquitto_plugin_cleanup(void *user_data, struct mosquitto_opt *auth_opts, int auth_opt_count)
{
	UNUSED(user_data);
	UNUSED(auth_opts);
	UNUSED(auth_opt_count);

	mosquitto_callback_unregister(plg_id, MOSQ_EVT_CONNECT, handle_connect, NULL);
	mosquitto_callback_unregister(plg_id, MOSQ_EVT_DISCONNECT, handle_disconnect, NULL);
	mosquitto_callback_unregister(plg_id, MOSQ_EVT_CLIENT_OFFLINE, handle_disconnect, NULL);
	mosquitto_callback_unregister(plg_id, MOSQ_EVT_TICK, handle_tick, NULL);
	mosquitto_FREE(last_clientid);

	return MOSQ_ERR_SUCCESS;
}


int handle_tick(int event, void *event_data, void *user_data)
{
	UNUSED(event);
	UNUSED(event_data);
	UNUSED(user_data);

	mosquitto_log_printf(MOSQ_LOG_INFO, "plugin tick %p %d", last_clientid, can_kick);
	if(last_clientid && can_kick){
		if(can_kick == 1){
			mosquitto_log_printf(MOSQ_LOG_INFO, "plugin kick %s", last_clientid);
			mosquitto_kick_client_by_clientid(last_clientid, false);
			mosquitto_FREE(last_clientid);
			can_kick--;
		}else{
			can_kick--;
		}
	}

	return MOSQ_ERR_SUCCESS;
}


int handle_connect(int event, void *event_data, void *user_data)
{
	struct mosquitto_evt_basic_auth *ed = event_data;
	UNUSED(event);
	UNUSED(user_data);

	const char *id = mosquitto_client_id(ed->client);
	mosquitto_log_printf(MOSQ_LOG_INFO, "plugin connect %s", id);
	mosquitto_FREE(last_clientid);
	last_clientid = mosquitto_strdup(id);

	return MOSQ_ERR_SUCCESS;
}


int handle_disconnect(int event, void *event_data, void *user_data)
{
	UNUSED(event);
	UNUSED(event_data);
	UNUSED(user_data);

	mosquitto_log_printf(MOSQ_LOG_INFO, "plugin disconnect %d", event);
	can_kick = 5;
	return MOSQ_ERR_SUCCESS;
}
