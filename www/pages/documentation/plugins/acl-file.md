<!--
.. title: ACL file Plugin
.. slug: acl-file
.. date: 2026-01-30 09:00:00 UTC
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

## Introduction

Available since version 2.1.

This plugin provides the same functionality as the `acl_file` option, and
should be the preferred way of using an ACL file.

The [dynamic-security plugin](/documentation/dynamic-security/) provides a more
powerful approach to authentication and authorisation.

## Usage

Control access to topics on the broker using an access control list file. If
this parameter is defined then only the topics listed will have access.  If the
first character of a line of the ACL file is a `#` it is treated as a comment.

Topic access is added with lines of the format:

```
topic [read|write|readwrite|deny] <topic>
```

The access type is controlled using `read`, `write`, `readwrite` or `deny`.
This parameter is optional (unless `<topic>` contains a space character) - if
not given then the access is read/write.  `<topic>` can contain the `+` or `#` 
wildcards as in subscriptions.

The `deny` option can used to explicitly deny access to a topic that would
otherwise be granted by a broader read/write/readwrite statement. Any `deny`
topics are handled before topics that grant read/write access.

The first set of topics are applied to anonymous clients, assuming anonymous
access is allowed. User specific topic ACLs are added after a user line as
follows:

```
user <username>
```

The username referred to here is the same as provided in the CONNECT packet. It
is not the clientid.

If is also possible to define ACLs based on pattern substitution within the
topic.

```
pattern [read|write|readwrite] <topic>
```

The patterns available for substitution are:

* %c to match the client id of the client
* %u to match the username of the client

The substitution pattern must be the only text for that level of hierarchy.

The form is the same as for the topic keyword, but using pattern as the
keyword.

Pattern ACLs apply to all users even if the `user` keyword has previously
been given.

If using bridges with usernames and ACLs, connection messages can be allowed
with the following pattern:

```
pattern write $SYS/broker/connection/%c/state
```


Example:

```
pattern write sensor/%u/data
```

# Config

Windows:
```
global_plugin C:\Program Files\Mosquitto\mosquitto_acl_file.dll
plugin_opt_acl_file <my acl file path>
```

Other:
```
global_plugin /path/to/mosquitto_acl_file.so
plugin_opt_acl_file <my acl file path>
```
