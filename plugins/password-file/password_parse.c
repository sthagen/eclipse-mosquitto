/*
Copyright (c) 2011-2021 Roger Light <roger@atchoo.org>

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

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "mosquitto.h"
#include "password_file.h"


int password_file__parse(struct password_file_data *data)
{
	FILE *pwfile;
	struct mosquitto__unpwd *unpwd = NULL;
	char *username, *password;
	char *saveptr = NULL;
	char *buf;
	int buflen = 256;
	int rc = MOSQ_ERR_INVAL;

	buf = mosquitto_malloc((size_t)buflen);
	if(buf == NULL){
		mosquitto_log_printf(MOSQ_LOG_ERR, "Error: Out of memory.");
		return MOSQ_ERR_NOMEM;
	}

	pwfile = mosquitto_fopen(data->password_file, "rt", true);
	if(!pwfile){
		mosquitto_log_printf(MOSQ_LOG_ERR, "password-file: Error: Unable to open pwfile \"%s\".", data->password_file);
		mosquitto_FREE(buf);
		return MOSQ_ERR_UNKNOWN;
	}

	while(!feof(pwfile)){
		if(mosquitto_fgets(&buf, &buflen, pwfile)){
			unpwd = NULL;

			if(buf[0] == '#'){
				continue;
			}
			if(!strchr(buf, ':')){
				continue;
			}

			username = strtok_r(buf, ":", &saveptr);
			if(username){
				username = mosquitto_trimblanks(username);
				if(strlen(username) > 65535){
					mosquitto_log_printf(MOSQ_LOG_ERR, "password-file: Error: Invalid line in password file '%s', username too long.", data->password_file);
					goto error;
				}
				if(strlen(username) <= 0){
					mosquitto_log_printf(MOSQ_LOG_ERR, "password-file: Error: Empty username in password file '%s'.", data->password_file);
					goto error;
				}

				HASH_FIND(hh, data->unpwd, username, strlen(username), unpwd);
				if(unpwd){
					unpwd = NULL;
					mosquitto_log_printf(MOSQ_LOG_ERR, "password-file: Error: Duplicate user '%s' in password file '%s'.", username, data->password_file);
					goto error;
				}

				unpwd = mosquitto_calloc(1, sizeof(struct mosquitto__unpwd));
				if(!unpwd){
					goto error;
				}

				unpwd->username = mosquitto_strdup(username);
				if(!unpwd->username){
					rc = MOSQ_ERR_NOMEM;
					goto error;
				}
				password = strtok_r(NULL, ":", &saveptr);
				if(password){
					password = mosquitto_trimblanks(password);

					if(strlen(password) > 65535){
						mosquitto_log_printf(MOSQ_LOG_ERR, "password-file: Error: Invalid line in password file '%s', password too long.", data->password_file);
						goto error;
					}

					if(mosquitto_pw_new(&unpwd->pw, MOSQ_PW_DEFAULT)
							|| mosquitto_pw_decode(unpwd->pw, password)){

						mosquitto_log_printf(MOSQ_LOG_ERR, "password-file: Error: Unable to decode line in password file '%s'.", data->password_file);
						goto error;
					}

					HASH_ADD_KEYPTR(hh, data->unpwd, unpwd->username, strlen(unpwd->username), unpwd);
				}else{
					mosquitto_log_printf(MOSQ_LOG_ERR, "password-file: Error: Invalid line in password file '%s': %s", data->password_file, buf);
					goto error;
				}
			}
		}
	}
	fclose(pwfile);
	mosquitto_FREE(buf);

	return MOSQ_ERR_SUCCESS;
error:
	if(unpwd){
		mosquitto_pw_cleanup(unpwd->pw);
		mosquitto_FREE(unpwd->username);
		mosquitto_FREE(unpwd);
	}
	mosquitto_FREE(buf);
	fclose(pwfile);
	return rc;
}


void password_file__cleanup(struct password_file_data *data)
{
	struct mosquitto__unpwd *u, *tmp = NULL;

	if(!data){
		return;
	}

	HASH_ITER(hh, data->unpwd, u, tmp){
		HASH_DEL(data->unpwd, u);
		mosquitto_pw_cleanup(u->pw);
		mosquitto_FREE(u->username);
		mosquitto_FREE(u);
	}
}


int password_file__reload(int event, void *event_data, void *userdata)
{
	struct password_file_data *data = userdata;

	UNUSED(event);
	UNUSED(event_data);

	password_file__cleanup(data);
	return password_file__parse(data);
}
