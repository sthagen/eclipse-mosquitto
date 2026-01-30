<!--
.. title: Documentation
.. slug: documentation
.. date: 2020-07-06 17:25:28 UTC
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

# Man pages

* [mosquitto] - running the Mosquitto broker
* [mosquitto.conf] - the Mosquitto broker configuration file
* [mosquitto_ctrl] - command line utility for managing Mosquitto broker configuration
* [mosquitto_ctrl_dynsec] - `mosquitto_ctrl` batch mode for the dynamic-security plugin
* [mosquitto_ctrl_shell] - `mosquitto_ctrl` interactive shell mode (recommended)
* [mosquitto_passwd] - command line utility for generating Mosquitto password files
* [mosquitto_pub] - command line utility for publishing messages to a broker
* [mosquitto_rr] - command line utility for simple request/response with a broker
* [mosquitto_signal] - command line utility for sending signals to a broker, most useful on Windows
* [mosquitto_sub] - command line utility for subscribing to topics on a broker
* [mosquitto-tls] - brief cheat sheet for creating x509 certificates
* [mqtt] - description of MQTT features

# Listeners

* [Using Mosquitto with HAProxy] - using Mosquitto with HAProxy with or without TLS termination.
* [Replacing the per_listener_settings option](/documentation/listeners/per_listener_settings/)

# Persistence

* [Sqlite](/documentation/persistence/sqlite/)

# Plugins

* [ACL file] - replacement for the `acl_file` option.
* [Password file] - replacement for the `password_file` option.
* [Dynamic Security] - details of using the Dynamic Security authentication and access control plugin.
* [Sparkplug Aware] - make Mosquitto fully compliant with the Sparkplug protocol.

# Other

* [Authentication methods] - details on the different authentication options available.
* [Using the snap package] - specific instructions on installing and configuring the Mosquitto snap package.
* [Migrating from 1.x to 2.0] - details of changes needed to migrate to version 2.0.

# libmosquitto API

* [libmosquitto API documentation]

# Third party

These are some Mosquitto documentation hosted by third parties.

* [Steve's internet guide] - a broad range of documentation and examples
  covering Mosquitto and the Paho Python client, amongst others.
* [docs.cedalo.com] - includes documentation for both Mosquitto and Eclipse
  Streamsheets

[mosquitto]:/man/mosquitto-8.html
[mosquitto.conf]:/man/mosquitto-conf-5.html
[mosquitto_ctrl]:/man/mosquitto_ctrl-1.html
[mosquitto_ctrl_dynsec]:/man/mosquitto_ctrl_dynsec-1.html
[mosquitto_ctrl_shell]:/man/mosquitto_ctrl_shell-1.html
[mosquitto_passwd]:/man/mosquitto_passwd-1.html
[mosquitto_pub]:/man/mosquitto_pub-1.html
[mosquitto_rr]:/man/mosquitto_rr-1.html
[mosquitto_signal]:/man/mosquitto_signal-1.html
[mosquitto_sub]:/man/mosquitto_sub-1.html
[mosquitto-tls]:/man/mosquitto-tls-7.html
[mqtt]:/man/mqtt-7.html


[libmosquitto API documentation]:/api/

[Authentication methods]:/documentation/authentication-methods/
[Using the snap package]:/documentation/using-the-snap/
[Dynamic Security]:/documentation/dynamic-security/
[ACL file]:/documentation/plugins/acl-file/
[Password file]:/documentation/plugins/password-file/
[Sparkplug Aware]:/documentation/plugins/sparkplug-aware/
[Using Mosquitto with HAProxy]:/documentation/listeners/haproxy/
[Migrating from 1.x to 2.0]:/documentation/migrating-to-2-0/

[Steve's internet guide]: http://www.steves-internet-guide.com/
[docs.cedalo.com]: https://docs.cedalo.com/
