<!--
.. title: Password file Plugin
.. slug: password-file
.. date: 2026-01-30 09:00:00 UTC
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

## Introduction

Available since version 2.1.

This plugin provides the same functionality as the `password_file` option, and
should be the preferred way of using an password file.

The [dynamic-security plugin](/documentation/dynamic-security/) provides a more
powerful approach to authentication and authorisation.

## Usage

Generate password files using the [mosquitto_passwd](/man/mosquitto_passwd-1.html) utility.

# Config

Windows:
```
global_plugin C:\Program Files\Mosquitto\mosquitto_password_file.dll
plugin_opt_password_file <my password file path>
```

Other:
```
global_plugin /path/to/mosquitto_password_file.so
plugin_opt_password_file <my password file path>
```
