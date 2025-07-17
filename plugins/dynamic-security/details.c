/*
Copyright (c) 2025 Roger Light <roger@atchoo.org>

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

#include "config.h"

#include <cjson/cJSON.h>
#include <stdio.h>
#include <uthash.h>

#include "dynamic_security.h"
#include "json_help.h"


int dynsec_details__process_get(struct dynsec__data *data, struct mosquitto_control_cmd *cmd)
{
	cJSON *tree, *j_data;
	const char *admin_clientid, *admin_username;

	tree = cJSON_CreateObject();
	if(tree == NULL
			|| cJSON_AddStringToObject(tree, "command", "getDetails") == NULL
			|| (j_data = cJSON_AddObjectToObject(tree, "data")) == NULL
			|| (cmd->correlation_data && cJSON_AddStringToObject(tree, "correlationData", cmd->correlation_data) == NULL)
			|| cJSON_AddIntToObject(j_data, "clientCount", (int)HASH_CNT(hh, data->clients)) == NULL
			|| cJSON_AddIntToObject(j_data, "groupCount", (int)HASH_CNT(hh, data->groups)) == NULL
			|| cJSON_AddIntToObject(j_data, "roleCount", (int)HASH_CNT(hh, data->roles)) == NULL
			|| cJSON_AddIntToObject(j_data, "changeIndex", data->changeindex) == NULL
			){

		cJSON_Delete(tree);
		mosquitto_control_command_reply(cmd, "Internal error");
		return MOSQ_ERR_NOMEM;
	}
	cJSON_AddItemToArray(cmd->j_responses, tree);

	admin_clientid = mosquitto_client_id(cmd->client);
	admin_username = mosquitto_client_username(cmd->client);
	mosquitto_log_printf(MOSQ_LOG_INFO, "dynsec: %s/%s | getDetails",
			admin_clientid, admin_username);

	return MOSQ_ERR_SUCCESS;
}
