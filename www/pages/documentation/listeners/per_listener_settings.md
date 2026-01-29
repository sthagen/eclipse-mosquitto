<!--
.. title: Replacing the per_listener_settings option
.. slug: per-listener-settings
.. date: 2026-01-29 09:00:00 UTC
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->


[TOC]

## Introduction

The `per_listener_settings` option was introduced in version 1.5 as a way to
allow security options such as `allow_anonymous` and `password_file` to be
applied on a per-listener basis, rather than globally as was the only option
before. It was however a poorly thought out idea that has lead to a great deal
of confusion, and since version 2.1 is deprecated. It will be removed in
version 3.0.

This document sets out how to remove the use of this option whilst keeping the
same functionality in your configuration. These changes require version 2.1.

## Authentication

* Replace the `acl_file` option with the [mosquitto_acl_file](/documentation/plugins/acl-file/) plugin.
* Replace the `password_file` option with the [mosquitto_password_file](/documentation/plugins/password-file/) plugin.
* Replace the use of `allow_anonymous` with the listener specific
`listener_allow_anonymous`. If `listener_allow_anonymous` is set for a
listener, this overrides any value set by `allow_anonymous`.
* Replace `auto_id_prefix` with `listener_auto_id_prefix`.
`allow_zero_length_clientid` has no replacement.

## Plugins

Prior to 2.1, plugins could be loaded with the `plugin` or `global_plugin`
options, where `plugin` would be applied to all plugins or a single plugin,
depending on the `per_listener_setting` value, and `global_plugin` would always
apply to all listeners.

`global_plugin` should still be used to load a plugin across all listener.

To use a plugin on some listeners only, use `plugin_load`, which loads a plugin
into the broker, and `plugin_use` which applies it to a listener.

For example:

```
plugin_load dynsec /usr/lib/mosquitto_dynamic_security.so
plugin_opt_config_file /mosquitto/data/dynamic-security.json

listener 1883
plugin_use dynsec

listener 1884
listener_allow_anonymous true

listener 1885
plugin_use dynsec
```

This configuration loads the dynamic-security plugin and uses it with the
listeners on ports 1883 and 1885. The listener on port 1884 does not have the
plugin applied, and also allows anonymous connections (so is very insecure,
anything connecting to that port can publish/subscribe to anything).

