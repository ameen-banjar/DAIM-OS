# DAIM-OS
DAIM-OS is a network switch operating system, designed for better management of packets forwarding through a network infrastructure, by providing precise control over network flows in a network.

This repository contains the platform-independent C interface specification for DAIM-OS. It defines the application API, the device-manager System API, and the proof-of-concept DAIM cloud wire protocol described in the DAIM-OS dissertation. It does not contain a complete operating-system implementation.

## What is DAIM?

DAIM stands for **Distributed Active Information Model**. It is a model for autonomic management of distributed networks in which forwarding devices collect and exchange information, make local decisions, and adapt their behaviour to changing requirements. The dissertation positions DAIM as a distributed combination of a network operating system and control plane, with control functions and agents placed closer to each switch instead of depending entirely on one central controller.

DAIM-OS is the proposed forwarding-device abstraction for that model. It hides low-level hardware details behind a high-level API so network applications can inspect state, configure forwarding behaviour, and work toward self-configuration, self-healing, self-optimisation, and self-protection.

The [research foundation](docs/RESEARCH_FOUNDATION.md) documents the dissertation definition, objectives, contributions, validation evidence, scope, and limitations represented by this repository.

## Headers

- `daim_os_api.h` defines DAIM tables, packet matching and actions, application callbacks, and the application-facing table API.
- `daim_os_sys_api.h` defines the hardware abstraction used by a device manager or middleware to read and write switch ports and control the switch.
- `daim_os_cloud.h` defines messages used to exchange switch identifiers, links, and hosts with the DAIM cloud.

All wire structures are packed. Multi-byte values require an implementation-defined byte-order conversion at serialization boundaries. Variable-length host messages store consecutive `struct daim_host` records in their `hosts` byte buffer; each record is immediately followed by its `num_of_ports` `struct daim_host_port` records.

## Validation

Run `make check` to compile a translation unit that includes all three public headers and to verify the intended 64-bit packet-action layout.

## Research source

This specification accompanies Ameen Reda Banjar's 2016 PhD dissertation, *Autonomic Management of Software Defined Networks: DAIM can provide the environment for building autonomy in distributed electronic environments - using OpenFlow networks as the case study*, University of Technology Sydney.

- ORCID: [0000-0002-0871-5153](https://orcid.org/0000-0002-0871-5153)
- Citation metadata: [`CITATION.cff`](CITATION.cff)

## License

DAIM-OS is licensed under the [Apache License 2.0](LICENSE).
