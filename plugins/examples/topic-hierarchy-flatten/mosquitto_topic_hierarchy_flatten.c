/*
Copyright (c) 2020-2025 Roger Light <roger@atchoo.org>

All rights reserved. This program and the accompanying materials
are made available under the terms of the Eclipse Public License 2.0
and Eclipse Distribution License v1.0 which accompany this distribution.

The Eclipse Public License is available at
   https://www.eclipse.org/legal/epl-2.0/
and the Eclipse Distribution License is available at
  http://www.eclipse.org/org/documents/edl-v10.php.

SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause

Contributors:
   Roger Light - initial implementation and documentation.
*/

/*
 * This is an *example* plugin which looks at messages coming in and if their
 * topic matches a topic filter, makes the payload available on another topic,
 * flattening the hierarchy if the topic filter includes a wildcard.
 *
 * The input topic filter and output topic can be configured in the plugin
 * config. The "plugin_opt_republish" option can be set to true/false. If set
 * to true, then the original incoming messages are unaffected and a new
 * message is published for each matching message. If set to false, the
 * original message has its topic replaced with the output topic.
 *
 * Compile with:
 *   gcc -I<path to mosquitto-repo/include> -fPIC -shared mosquitto_topic_hierarchy_flatten.c -o mosquitto_topic_hierarchy_flatten.so
 *
 * Use in config with:
 *
 *   plugin /path/to/mosquitto_topic_hierarchy_flatten.so
 *   plugin_opt_input_topic_filter my/+/topics
 *   plugin_opt_output_topic the/single/output/topic
 *   plugin_opt_republish true
 *
 * Note that this only works on Mosquitto 2.1 or later.
 */
#include <stdio.h>
#include <string.h>

#include "mosquitto.h"

#define PLUGIN_NAME "topic-hierarchy-flatten"

#define UNUSED(A) (void)(A)

MOSQUITTO_PLUGIN_DECLARE_VERSION(5);

struct plugin_data {
	mosquitto_plugin_id_t *pid;
	char *input_topic_filter;
	char *output_topic;
	bool republish;
};


static int callback_message_in(int event, void *event_data, void *userdata)
{
	struct mosquitto_evt_message *ed = event_data;
	struct plugin_data *data = userdata;
	bool result;
	int rc;

	UNUSED(event);

	mosquitto_topic_matches_sub(data->input_topic_filter, ed->topic, &result);

	if(result){
		if(data->republish){
			mosquitto_property *props = NULL;
			if(ed->properties){
				rc = mosquitto_property_copy_all(&props, ed->properties);
				if(rc){
					return rc;
				}
			}
			rc = mosquitto_broker_publish_copy(NULL, data->output_topic, (int)ed->payloadlen,
					ed->payload, ed->qos, ed->retain, props);
			if(rc){
				mosquitto_property_free_all(&props);
				return rc;
			}
		}else{
			ed->topic = mosquitto_strdup(data->output_topic);
			if(!ed->topic){
				return MOSQ_ERR_NOMEM;
			}
		}
	}

	return MOSQ_ERR_SUCCESS;
}


int mosquitto_plugin_init(mosquitto_plugin_id_t *identifier, void **userdata, struct mosquitto_opt *opts, int opt_count)
{
	struct plugin_data *data = mosquitto_calloc(1, sizeof(struct plugin_data));
	if(!data){
		return MOSQ_ERR_NOMEM;
	}
	*userdata = data;
	data->republish = true;

	for(int i=0; i<opt_count; i++){
		if(!strcmp(opts[i].key, "input_topic_filter")){
			data->input_topic_filter = mosquitto_strdup(opts[i].value);
			if(!data->input_topic_filter){
				return MOSQ_ERR_NOMEM;
			}
		}else if(!strcmp(opts[i].key, "output_topic")){
			data->output_topic = mosquitto_strdup(opts[i].value);
			if(!data->output_topic){
				return MOSQ_ERR_NOMEM;
			}
		}else if(!strcmp(opts[i].key, "republish")){
			data->republish = !strcmp(opts[i].value, "true");
		}
	}

	if(!data->input_topic_filter){
		data->input_topic_filter = mosquitto_strdup("input/#");
		if(!data->input_topic_filter){
			return MOSQ_ERR_NOMEM;
		}
	}

	if(!data->output_topic){
		data->output_topic = mosquitto_strdup("output");
		if(!data->output_topic){
			return MOSQ_ERR_NOMEM;
		}
	}

	mosquitto_log_printf(MOSQ_LOG_INFO, PLUGIN_NAME ": Input topic filter is '%s'", data->input_topic_filter);
	mosquitto_log_printf(MOSQ_LOG_INFO, PLUGIN_NAME ": Output topic is '%s'", data->output_topic);
	mosquitto_log_printf(MOSQ_LOG_INFO, PLUGIN_NAME ": Republish is %s", data->republish?"true":"false");

	data->pid = identifier;
	return mosquitto_callback_register(data->pid, MOSQ_EVT_MESSAGE_IN, callback_message_in, NULL, data);
}


/* mosquitto_plugin_cleanup() is optional in 2.1 and later. Use it only if you have your own cleanup to do */
int mosquitto_plugin_cleanup(void *userdata, struct mosquitto_opt *opts, int opt_count)
{
	struct plugin_data *data = userdata;
	UNUSED(opts);
	UNUSED(opt_count);

	if(data){
		mosquitto_callback_unregister(data->pid, MOSQ_EVT_MESSAGE_IN, callback_message_in, NULL);

		mosquitto_FREE(data->input_topic_filter);
		mosquitto_FREE(data->output_topic);
		mosquitto_FREE(data);
	}

	return MOSQ_ERR_SUCCESS;
}
