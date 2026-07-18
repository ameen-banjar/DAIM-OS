# DAIM-OS
DAIM-OS is a network switch operating system, designed for better management of packets forwarding through a network infrastructure, by providing precise control over network flows in a network.

This repository contains the platform-independent C interface specification for DAIM-OS. It defines the application API, the device-manager System API, and the proof-of-concept DAIM cloud wire protocol described in the DAIM-OS dissertation. It does not contain a complete operating-system implementation.

## Headers

- `daim_os_api.h` defines DAIM tables, packet matching and actions, application callbacks, and the application-facing table API.
- `daim_os_sys_api.h` defines the hardware abstraction used by a device manager or middleware to read and write switch ports and control the switch.
- `daim_os_cloud.h` defines messages used to exchange switch identifiers, links, and hosts with the DAIM cloud.

All wire structures are packed. Multi-byte values require an implementation-defined byte-order conversion at serialization boundaries. Variable-length host messages store consecutive `struct daim_host` records in their `hosts` byte buffer; each record is immediately followed by its `num_of_ports` `struct daim_host_port` records.

## Validation

Run `make check` to compile a translation unit that includes all three public headers and to verify the intended 64-bit packet-action layout.
