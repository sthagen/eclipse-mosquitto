<!--
.. title: Sparkplug Aware Plugin
.. slug: sparkplug-aware
.. date: 2026-01-30 09:00:00 UTC
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

Available since version 2.1.

The [Sparkplug protocol](https://sparkplug.eclipse.org/) provides a unified way
to manage topics, device lifetime, and payload format. It is typically intended
for use in Industrial Internet of Things applications, such as in factories.

The Sparkplug specification makes certain requirements on clients and brokers.
For brokers there are two levels of conformance: Sparkplug Compliant and
Sparkplug Aware.

Any MQTT broker that conforms to the MQTT v3.1.1 or v5.0 protocol meets the
requirements to be Sparkplug Compliant.

A Sparkplug Aware broker also needs to monitor birth messages from Sparkplug
nodes and devices, and republish them to the appropriate topic within
`$sparkplug/certificates/spBv1.0/`

Loading this plugin makes provides Sparkplug Aware support for Mosquitto.

## Config

Windows:
```
global_plugin C:\Program Files\Mosquitto\mosquitto_sparkplug_aware.dll
```

Other:
```
global_plugin /path/to/mosquitto_sparkplug_aware.so
```
