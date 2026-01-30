<!--
.. title: Version 2.1.0 released.
.. slug: version-2-1-0-released
.. date: 2026-01-29 16:00:00 UTC
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

Version 2.1.0 of Mosquitto has been released. This is a feature release.

# Broker

## Deprecations

- The `acl_file` option is deprecated in favour of the acl-file plugin, which is
  the same code but moved into a plugin. The `acl_file` option will be removed
  in 3.0.
- The `password_file` option is deprecated in favour of the password-file plugin,
  which is the same code but moved into a plugin. The `password_file` option will
  be removed in 3.0.
- The `per_listener_settings` option is deprecated in favour of the new listener
  specific options. The `per_listener_settings` option will be removed in 3.0.

## Behaviour changes

- `max_packet_size` now defaults to 2,000,000 bytes instead of the 256MB MQTT
  limit. If you are using payloads that will result in a packet larger than
  this, you need to manually set the option to a value that suits your
  application.
- `acl_file` and `password_file` will produce an error on invalid input when
  reloading the config, causing the broker to quit.

## Protocol related

- Add support for broker created topic aliases. Topics are allocated on a
  first come first serve basis.
- Add support for bridges to allow remote brokers to create topic aliases when
  running in MQTT v5 mode.
- Enforce receive maximum on MQTT v5.
- Return protocol error if a client attemps to subscribe to a shared
  subscription and also sets no-local.
- Protocol version numbers reported in the log when a client connects now
  match the MQTT protocol version numbers, not internal Mosquitto values.
- Send DISCONNECT With session-takeover return code to MQTT v5 clients when a
  client connects with the same client id. Closes [#2340].
- The `allow_duplicate_messages` now defaults to `true`.
- Add `accept_protocol_versions` option to allow limiting which MQTT protocol
  versions are allowed for a particular listener.

## TLS related

- Add `--tls-keylog` option which can be used to generate a file that can be
  used by wireshark to decrypt TLS traffic for debugging purposes. Closes [#1818].
- Add `disable_client_cert_date_checks` option to allow expired client
  certificate to be considered valid.
- Add `bridge_tls_use_os_certs` option to allow bridges to be easily configured
  to trust default CA certificates. Closes [#2473].
- Remove support for TLS v1.1 (clients only - it remains available in the
  broker but is now undocumented)
- Use openssl provided function for x509 certificate hostname verification,
  rather than own function.

## Bridge related
- Add `bridge_receive_maximum` option for MQTT v5.0 bridges.
- Add `bridge_session_expiry_interval` option for MQTT v5.0 bridges.
- Bridge reconnection backoff improvements.

## Transport related
- Add the `websockets_origin` option to allow optional enforcement of origin
  when a connection attempts an upgrade to WebSockets.
- Add built-in websockets support that doesn't use libwebsockets. This is the
  preferred websockets implementation.
- Add support for X-Forwarded-For header for built in websockets.
- Add suport for PROXY protocol v1 and v2.

## Platform specific
- Increase maximum connection count on Windows from 2048 to 8192 where
  supported. Closes [#2122].
- Allow multiple instances of mosquitto to run as services on Windows. See
  README-windows.txt.
- Add kqueue support.
- Add support for systemd watchdog.

## General
- Report on what compile time options are enabled. Closes [#2193].
- Performance: reduce memory allocations when sending packets.
- Log protocol version and ciphers that a client negotiates when connecting.
- Password salts are now 64 bytes long.
- Add the `global_plugin` option, which gives global plugin loaded regardless
  of `per_listener_settings`.
- Add `global_max_clients` option to allow limiting client sessions globally
  on the broker.
- Add `global_max_connections` option to allow limiting client connections globally
  on the broker.
- Improve idle performance. The broker now calculates when the next event of
  interest is, and uses that as the timeout for e.g. `epoll_wait()`. This can
  reduce the number of process wakeups by 100x on an idle broker.
- Add more efficient keepalive check.
- Add support for sending the SIGRTMIN signal to trigger log rotation.
  Closes [#2337].
- Add `--test-config` option which can be used to test a configuration file
  before trying to use it in a live broker. Closes [#2521].
- Add support for PUID/PGID environment variables for setting the user/group
  to drop privileges to. Closes [#2441].
- Report persistence stats when starting.
- $SYS updates are now aligned to `sys_interval` seconds, meaning that if set
  to 10, for example, updates will be sent at times matching x0 seconds.
  Previously update intervals were aligned to the time the broker was started.
- Add `log_dest android` for logging to the Android logd daemon.
- Fix some retained topic memory not being cleared immediately after used.
- Add -q option to allow logging to be disabled at the command line.
- Log message if a client attempts to connect with TLS to a non-TLS listener.
- Add `listener_allow_anonymous` option.
- Add `listener_auto_id_prefix` option.
- Allow seconds when defining `persistent_client_expiration`.

## Plugin interface
- Add `mosquitto_topic_matches_sub_with_pattern()`, which can match against
  subscriptions with `%c` and `%u` patterns for client id / username
  substitution.
- Add support for modifying outgoing messages using `MOSQ_EVT_MESSAGE_OUT`.
- Add `mosquitto_client()` function for retrieving a client struct if that
  client is connected.
- Add `MOSQ_ERR_PLUGIN_IGNORE` to allow plugins to register basic auth or acl
  check callbacks, but still act as though they are not registered. A plugin
  that wanted to act as a blocklist for certain usernames, but wasn't carrying
  out authentication could return `MOSQ_ERR_PLUGIN_IGNORE` for usernames not on
  its blocklist. If no other plugins were configured, the client would be
  authenticated. Using `MOSQ_ERR_PLUGIN_DEFER` instead would mean the clients
  would be denied if no other plugins were configured.
- Add `mosquitto_client_port()` function for plugins.
- Add `MOSQ_EVT_CONNECT`, to allow plugins to know when a client has
  successfully authenticated to the broker.
- Add connection-state example plugin to demonstrate `MOSQ_EVT_CONNECT`.
- Add `MOSQ_EVT_CLIENT_OFFLINE`, to allow plugins to know when a client with a
  non-zero session expiry interval has gone offline.
- Plugins on non-Windows platforms now no longer make their symbols globally
  available, which means they are self contained.
- Add support for delayed basic authentication in plugins.
- Plugins using the `MOSQ_EVT_MESSAGE_WRITE` callback can now return
  `MOSQ_ERR_QUOTA_EXCEEDED` to have the message be rejected. MQTT v5 clients
  using QoS 1 or 2 will receive the quota-exceeded reason code in the
  corresponding PUBACK/PUBREC.
- `MOSQ_EVT_TICK` is now passed to plugins when `per_listener_settings` is true.
- Add `mosquitto_sub_matches_acl()`, which can match one topic filter (a
  subscription) against another topic filter (an ACL).
- Registration of the `MOSQ_EVT_CONTROL` plugin event is now handled globally
  across the broker, so only a single plugin can register for a given $CONTROL
  topic.
- Add `mosquitto_plugin_set_info()` to allow plugins to tell the broker their
  name and version.
- Add builtin $CONTROL/broker/v1 control topic with the `listPlugins`
  command. This is disabled by default, but can be enabled with the
  `enable_control_api` option.
- Plugins no longer need to define `mosquitto_plugin_cleanup()` if they do not
  need to do any of their own cleanup. Callbacks will be unregistered
  automatically.
- Add `mosquitto_set_clientid()` to allow plugins to force a client id for a
  client.
- Add `MOSQ_EVT_SUBSCRIBE` and `MOSQ_EVT_UNSUBSCRIBE` events that are called when
  subscribe/unsubscribes actually succeed. Allow modifying topic and qos.
- Add `mosquitto_persistence_location()` for plugins to use to find a valid
  location for storing persistent data.
- Plugins can now use the `next_s` and `next_ms` members of the tick event data
  struct to set a minimum interval that the broker will wait before calling the
  tick callback again.
- MOSQ_EVT_ACL_CHECK event is now passed message properties where possible.

# Plugins
- Add acl-file plugin.
- Add password-file plugin.
- Add persist-sqlite plugin.
- Add sparkplug-aware plugin.

# Dynamic security plugin
- Add ability to deny wildcard subscriptions for a role to the dynsec plugin.
- The dynamic security plugin now only kicks clients at the start of the next
  network loop, to give chance for PUBACK/PUBREC to be sent. Closes [#2474].
- The dynamic security plugin now reports client connections in getClient and
  listClients.
- The dynamic security plugin now generates an initial configuration if none
  is present, including a set of default roles.
- The dynamic security plugin now supports `%c` and `%u` patterns for
  substituting client id and username respectively, in all ACLs except for
  subscribeLiteral and unsubscribeLiteral.
- The dynamic security plugin now supports multiple ways to initialise the
  first configuration file.

# Client library
- Add `MOSQ_OPT_DISABLE_SOCKETPAIR` to allow the disabling of the socketpair
  feature that allows the network thread to be woken from select() by another
  thread when e.g.  `mosquitto_publish()` is called. This reduces the number of
  sockets used by each client by two.
- Add `on_pre_connect()` callback to allow clients to update
  username/password/TLS parameters before an automatic reconnection.
- Callbacks no longer block other callbacks, and can be set from within a
  callback. Closes [#2127].
- Add support for MQTT v5 broker to client topic aliases.
- Add `mosquitto_topic_matches_sub_with_pattern()`, which can match against
  subscriptions with `%c` and `%u` patterns for client id / username
  substitution.
- Add `mosquitto_sub_matches_acl()`, which can match one topic filter (a
  subscription) against another topic filter (an ACL).
- Add `mosquitto_sub_matches_acl_with_pattern()`, which can match one topic
  filter (a subscription) against another topic filter (an ACL), with `%c` and
  `%u` patterns for client id / username substitution.
- Performance: reduce memory allocations when sending packets.
- Reintroduce threading support for Windows. Closes [#1509].
- `mosquitto_subscribe*()` now returns `MOSQ_ERR_INVAL` if an empty string is
  passed as a topic filter.
- `mosquitto_unsubscribe*()` now returns `MOSQ_ERR_INVAL` if an empty string is
  passed as a topic filter.
- Add websockets support.
- `mosquitto_property_read_binary/string/string_pair` will now set the
  name/value parameter to NULL if the binary/string is empty. This aligns the
  behaviour with other property functions. Closes [#2648].
- Add `mosquitto_unsubscribe2_v5_callback_set`, which provides a callback that
  gives access to reason codes for each of the unsubscription requests.
- Add `mosquitto_property_remove`, for removing properties from property
  lists.
- Add `on_ext_auth()` callback to allow handling MQTT v5 extended authentication.
- Add `mosquitto_ext_auth_continue()` function to continue an MQTT v5 extended
  authentication.
- Remove support for TLS v1.1.
- Use openssl provided function for x509 certificate hostname verification,
  rather than own function.

# Clients

## General
- Add `-W` timeout support to Windows.
- The `--insecure` option now disables all server certificate verification.
- Add websockets support.
- Using `-x` now sets the clients to use MQTT v5.0.
- Fix parsing of IPv6 addresses in socks proxy urls.
- Add `--tls-keylog` option which can be used to generate a file that can be
  used by wireshark to decrypt TLS traffic for debugging purposes.
- Remove support for TLS v1.1.

## mosquitto_rr
- Fix `-f` and `-s` options in mosquitto_rr.
- Add `--latency` option to mosquitto_rr, for printing the request/response
  latency.
- Add `--retain-handling` option.

## mosquitto_sub
- Fix incorrect output formatting in mosquitto_sub when using field widths
  with `%x` and `%X` for printing the payload in hex.
- Add float printing option to mosquitto_sub.
- mosquitto_sub payload hex output can now be split by fixed field length.
- Add `--message-rate` option to mosquitto_sub, for printing the count of
  messages received each second.
- Add `--retain-handling` option.

# Apps

## mosquitto_signal
- Add `mosquitto_signal` for helping send signals to mosquitto on Windows.

## mosquitto_ctrl
- Add interactive shell mode to mosquitto_ctrl.
- Add support for `listPlugins` to mosquitto_ctrl.
- Allow mosquitto_ctrl dynsec module to update passwords in files rather than
  having to connect to a broker.

## mosquitto_passwd
- Print messages in mosquitto_passwd when adding/updating passwords.
  Closes [#2544].
- When creating a new file with `-c`, setting the output filename to a dash `-`
  will output the result to stdout.

## mosquitto_db_dump
- Add `--json` output mode do mosquitto_db_dump.

# Build
- Increased CMake minimal required version to 3.14, which is required for the
  preinstalled SQLite3 find module.
- Add an CMake option `WITH_LTO` to enable/disable link time optimization.
- Set C99 as the explicit, rather than implicit, build standard.
- cJSON is now a required dependency.
- Refactored headers for easier discovery.
- Support for openssl < 3.0 removed.

[#1509]: https://github.com/eclipse-mosquitto/mosquitto/issues/1509
[#1818]: https://github.com/eclipse-mosquitto/mosquitto/issues/1818
[#2122]: https://github.com/eclipse-mosquitto/mosquitto/issues/2122
[#2172]: https://github.com/eclipse-mosquitto/mosquitto/issues/2172
[#2193]: https://github.com/eclipse-mosquitto/mosquitto/issues/2193
[#2337]: https://github.com/eclipse-mosquitto/mosquitto/issues/2337
[#2340]: https://github.com/eclipse-mosquitto/mosquitto/issues/2340
[#2441]: https://github.com/eclipse-mosquitto/mosquitto/issues/2441
[#2473]: https://github.com/eclipse-mosquitto/mosquitto/issues/2473
[#2474]: https://github.com/eclipse-mosquitto/mosquitto/issues/2474
[#2521]: https://github.com/eclipse-mosquitto/mosquitto/issues/2521
[#2544]: https://github.com/eclipse-mosquitto/mosquitto/issues/2544
[#2648]: https://github.com/eclipse-mosquitto/mosquitto/issues/2648
