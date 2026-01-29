#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <mosquitto/broker.h>
#include <mosquitto/broker_plugin.h>

MOSQUITTO_PLUGIN_DECLARE_VERSION(5);


static int on_ext_auth_start(int event, void *event_data, void *user_data)
{
	struct mosquitto_evt_extended_auth *ed = event_data;
	(void)user_data;

	if(event != MOSQ_EVT_EXT_AUTH_START){
		abort();
	}

	if(!strcmp((char *)ed->data_in, "allowed-start")){
		ed->data_out = mosquitto_strdup("start-ok");
		ed->data_out_len = (uint16_t)strlen(ed->data_out);
		return MOSQ_ERR_AUTH_CONTINUE;
	}else{
		return MOSQ_ERR_AUTH;
	}
}


static int on_ext_auth_continue(int event, void *event_data, void *user_data)
{
	struct mosquitto_evt_extended_auth *ed = event_data;
	(void)user_data;

	if(event != MOSQ_EVT_EXT_AUTH_CONTINUE){
		abort();
	}

	if(!strcmp((char *)ed->data_in, "allowed-continue")){
		return MOSQ_ERR_SUCCESS;
	}else{
		return MOSQ_ERR_AUTH;
	}
}


int mosquitto_plugin_init(mosquitto_plugin_id_t *identifier, void **user_data, struct mosquitto_opt *auth_opts, int auth_opt_count)
{
	(void)user_data;
	(void)auth_opts;
	(void)auth_opt_count;

	mosquitto_callback_register(identifier, MOSQ_EVT_EXT_AUTH_START, on_ext_auth_start, NULL, NULL);
	mosquitto_callback_register(identifier, MOSQ_EVT_EXT_AUTH_CONTINUE, on_ext_auth_continue, NULL, NULL);

	return MOSQ_ERR_SUCCESS;
}
