/*
Copyright (c) 2009-2021 Roger Light <roger@atchoo.org>

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

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef WIN32
#include <time.h>
#else
#include <process.h>
#include <winsock2.h>
#define snprintf sprintf_s
#endif

#include <mosquitto.h>
#include "client_shared.h"
#include "pub_shared.h"

/* Global variables for use in callbacks. See sub_client.c for an example of
 * using a struct to hold variables for use in callbacks. */
int mid_sent = -1;
struct mosq_config cfg;


void my_log_callback(struct mosquitto *mosq, void *obj, int level, const char *str)
{
	UNUSED(mosq);
	UNUSED(obj);
	UNUSED(level);

	printf("%s\n", str);
}


int load_stdin(void)
{
	size_t pos = 0, rlen;
	char buf[1024];
	char *aux_message = NULL;

	cfg.pub_mode = MSGMODE_STDIN_FILE;

	while(!feof(stdin)){
		rlen = fread(buf, 1, 1024, stdin);
		aux_message = mosquitto_realloc(cfg.message, pos+rlen);
		if(!aux_message){
			err_printf(&cfg, "Error: Out of memory.\n");
			mosquitto_FREE(cfg.message);
			return 1;
		}else{
			cfg.message = aux_message;
		}
		memcpy(&(cfg.message[pos]), buf, rlen);
		pos += rlen;
	}
	if(pos > MQTT_MAX_PAYLOAD){
		err_printf(&cfg, "Error: Message length must be less than %u bytes.\n\n", MQTT_MAX_PAYLOAD);
		mosquitto_FREE(cfg.message);
		return 1;
	}
	cfg.msglen = (int )pos;

	if(!cfg.msglen){
		err_printf(&cfg, "Error: Zero length input.\n");
		return 1;
	}

	return 0;
}


int load_file(const char *filename)
{
	size_t buflen;
	char *buf;

	cfg.pub_mode = MSGMODE_FILE;

	int rc = mosquitto_read_file(filename, false, &buf, &buflen);
	if(rc){
		err_printf(&cfg, "Error: Unable to read file \"%s\": %s.\n", filename, mosquitto_strerror(rc));
		return 1;
	}

	if(buflen > MQTT_MAX_PAYLOAD){
		err_printf(&cfg, "Error: File must be less than %u bytes.\n\n", MQTT_MAX_PAYLOAD);
		mosquitto_FREE(buf);
		return 1;
	}else if(buflen == 0){
		cfg.message = NULL;
		cfg.msglen = 0;
		return 0;
	}

	cfg.msglen = (int )buflen;
	cfg.message = buf;

	return 0;
}
