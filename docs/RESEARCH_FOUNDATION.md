# DAIM-OS Research Foundation

## Source

This document maps the repository to Ameen Reda Banjar's PhD dissertation,
*Autonomic Management of Software Defined Networks: DAIM can provide the
environment for building autonomy in distributed electronic environments - using
OpenFlow networks as the case study*, University of Technology Sydney, Spring
2016.

Public records:

- [Dissertation record and full-text access on ProQuest](https://www.proquest.com/openview/8808b30ae9e4ed019823530394450930/1?cbl=2026366&diss=y)
- [Ameen Banjar's Google Scholar profile](https://scholar.google.com/citations?user=kjW-MxkAAAAJ&hl=en)

The direct `media.proquest.com` download URL is intentionally not used because it
is a temporary signed delivery link; the ProQuest record above is the stable public
reference.

Page references below use the printed dissertation page numbers.

## Definition of DAIM

DAIM means **Distributed Active Information Model**. The dissertation defines it
as an information model for autonomic network solutions: network devices collect
and share information, make local and network-wide decisions, and adapt to
changing requirements. DAIM distributes selected control functions into network
forwarding devices and uses agents, modules, and requirements data to support
local decision-making (Abstract; Sections 1.4 and 3.1).

The model is described as a distributed combination of a network operating system
and a control plane. In the OpenFlow case study, this moves part of the controller's
computational work closer to each switch while retaining information exchange and
network-wide coordination (Section 3.1, pp. 75-77).

DAIM is not the same as cloud computing. Its network entities remain distributed,
independent computing environments rather than being presented as one pooled
computational infrastructure (Section 3.1.1, p. 77).

## Primary research objective

The dissertation states one primary objective: to develop a new approach to
autonomic network management using the DAIM model. It proposes distributing
part of an SDN/OpenFlow control plane so that the system can respond to changing
requirements and threats while improving scalability, robustness, configuration
consistency, and operational efficiency (Section 1.3.1, p. 12).

The intended autonomic capabilities are:

1. Self-locating - discover neighbouring nodes and resources.
2. Self-configuring - change device configuration dynamically at run time.
3. Self-healing - evaluate network state and initiate corrective action.
4. Self-optimising - improve allocation and utilisation against policies and
   business requirements.
5. Self-protecting - detect malicious behaviour and take autonomous action.
6. Context-awareness - analyse events and packets to support the other autonomic
   capabilities.

These are defined in Section 3.1.3 (pp. 78-79).

## Main research contributions

Chapter 8 lists twelve numbered contribution groups:

1. Analysis of distributed management requirements for next-generation networks.
2. Review of autonomic computing and autonomic communication for self-managed
   networks.
3. Review and analysis of SDN and OpenFlow architecture, abstractions, and
   research challenges.
4. Comparative evaluation of OpenFlow simulation and emulation tools.
5. OpenFlow studies covering simulation accuracy, ICN-based multi-controller
   scaling, mobility management, and an alternative Mobile IP mechanism.
6. The DAIM model for distributed control and autonomic management at switch
   level.
7. A reference implementation developed in three phases across simulation,
   emulation, and physical environments.
8. A socket-based communication module between an OpenFlow controller and
   switch without modifying OpenFlow messages.
9. Topology-discovery mechanisms using augmented LLDP and DAIM messages.
10. Communication, storage, and control modules supporting configuration,
    optimisation, protection, and recovery.
11. Identification of implementation factors and discrepancies that informed the
    DAIM-OS specification.
12. Functional and performance evaluation using OMNeT++, Mininet, Raspberry
    Pi, Cbench, ping, and Iperf, including comparisons with NOX and POX.

The fifth group contains four distinct technical sub-contributions. It is therefore
reasonable to describe the dissertation as having **12 numbered contribution
groups or 15 countable contribution items**, provided that this counting convention
is stated explicitly (Chapter 8, pp. 231-234).

## DAIM-OS contribution represented here

DAIM-OS is the forwarding-device abstraction produced from the DAIM research.
The dissertation specifies a high-level API for network service applications and
modules for packet forwarding, configuration, optimisation, protection, and
healing. This repository represents three public boundaries of that specification:

- `daim_os_api.h`: tables, packet matches and actions, application callbacks, and
  application-facing operations.
- `daim_os_sys_api.h`: the device-manager or middleware interface to switch ports
  and controls.
- `daim_os_cloud.h`: the proof-of-concept protocol for sharing switch identifiers,
  links, and hosts with the DAIM cloud.

## Evidence and limitations

The dissertation reports exercises in OMNeT++, Mininet, and Raspberry Pi, and
latency and throughput comparisons involving NOX and POX. These exercises
support the feasibility of the DAIM model and informed the DAIM-OS design.

They must not be interpreted as validation of a complete DAIM-OS implementation.
The dissertation explicitly states that implementation of the complete
specification was outside its scope. It also identifies these limitations (Section
7.3, pp. 229-230):

- the complete DAIM-OS software stack was not implemented or benchmarked;
- simultaneous access to DAIM tables by multiple applications was not thoroughly
  analysed;
- internal module algorithms and mechanisms were intentionally left open;
- physical experiments used a small OpenFlow network.

Accordingly, this repository is a **C interface specification and research
artifact**, not a production network operating system.
