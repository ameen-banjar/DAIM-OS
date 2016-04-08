/*  DAIM OS platform agnostic C header file
    Definitions of DAIM OS tables structures
    Definitions of DAIM OS table API functions */

#ifndef DAIM_OS_H
#define DAIM_OS_H

#include <stdint.h>

#define DAIM_OS_VERSION 0x01

#define DESC_STR_LEN 256
#define SERIAL_NUM_LEN 32
#define MAC_ADDR_LEN 6
#define ARP_PACKET_LEN 28
#define DAIM_ETH_II_DATA 0x0700

typedef void (*sighandler) (uint16_t, void *);

#pragma pack(push, 1)   /* disable structure padding */

/* enumeration for DAIM OS tables */
enum daim_table {
    DAIM_INFO_TABLE = 0xa1,
    DAIM_SWITCH_TABLE = 0xa2,
    DAIM_SWITCH_PORT_TABLE = 0xa3,
    DAIM_ENTITY_TABLE = 0xa4,
    DAIM_ENTITY_PORT_TABLE = 0xa5,
    DAIM_ENTITY_ARP_TABLE = 0xa6,
    DAIM_LINK_TABLE = 0xa7,
	DAIM_PACKET_FORWARDING_TABLE = 0xa8,
	DAIM_SWITCH_CONFIG_TABLE = 0xa9,
	DAIM_SWITCH_PORT_CONFIG_TABLE = 0xaa,
	DAIM_ENTITY_CONFIG_TABLE = 0xab,
	DAIM_LINK_CONFIG_TABLE = 0xac
};

/* DAIM OS features */
enum daim_os_feature {
	DAIM_SWITCH_STATES = 1 << 0,	/* switch table containing statistics and states*/
    DAIM_PORT_STATES = 1 << 1,		/* port tables containing statistics and states*/
    DAIM_ENTITY_STATES = 1 << 2,	/* entity table containing statistics and states*/
    DAIM_LINK_STATES = 1 << 3		/* link table containing statistics and states*/
};

/* Capabilities of DAIM OS switch */
enum daim_switch_capability {
    STP = 1 << 0,  		/* 802.1d spanning tree */
    IP_REASM = 1 << 1   /* Can reassemble IP fragments */
};

/* DAIM OS state on the switch */
enum daim_os_state {
    DAIM_SLEEP = 0xffa,		/* DAIM OS is sleeping */
	DAIM_BUSY = 0xffb,		/* DAIM OS is busy */
    DAIM_ACTIVE = 0xffc		/* DAIM OS is running */
};

/* enumeration for DAIM OS virtual ports */
enum daim_virtual_port {
	PORT_IN_PORT = 0xfffa,	/* send the packet out the input port */
	PORT_FLOOD = 0xfffb,  	/* all physical ports except input port and those disabled by STP */
	PORT_ALL = 0xfffc,		/* all physical ports except input port */
	PORT_APP = 0xfffd,		/* used when packet is delivered from applications or to applications */
	PORT_NONE = 0xfffe		/* not associated with a physical port */
};

/* enumeration for DAIM OS signals to be checked by callback_function */
enum daim_signal_number {
    ENTRY_REMOVED,
    STATE_CHANGE,
    PORT_CHANGE,
    REC_PACK_COUNTER_RESET,
    REC_BYTE_COUNTER_RESET,
    REC_DROP_COUNTER_RESET,
    REC_ERR_COUNTER_RESET,
    REC_FRAME_COUNTER_RESET,
    REC_OVER_COUNTER_RESET,
    REC_CRC_COUNTER_RESET,
    TRA_PACK_COUNTER_RESET,
    TRA_BYTE_COUNTER_RESET,
    TRA_DROP_COUNTER_RESET,
    TRA_ERR_COUNTER_RESET,
    TRA_OVER_COUNTER_RESET,
    COLL_COUNTER_RESET,
    DURATION_COUNTER_RESET,
    COLLECT_BUFFER,
    NO_RULE,
    ENTITY_JOIN,
    ENTITY_LEAVE
};

/* enumeration for daim_table_write op_code */
enum table_write_op {
    ADD = 0xa,              /* add entry to the table */
    DEL = 0xb               /* delete entries from the table */
};

/* different settings for DAIM OS switch */
enum daim_switch_state {
    SWITCH_UP = 1 << 0,		/* the switch is administratively up */
    SWITCH_DOWN = 1 << 1,	/* the switch is administratively down */
	NOR_MOD = 1 << 2,		/* the switch is configured to be a DAIM switch */
    ETH_SW = 1 << 3,        /* the switch is configured to be a traditional network switch */
	ETH_HUB = 1 << 4,		/* the switch is configured to be a traditional network hub */
	ETH_ROU = 1 << 5		/* the switch is configured to be a traditional network router */
};

/* different settings for DAIM switch port */
enum daim_switch_port_state {
    PORT_UP = 1 << 0,				/* the port is administratively up */
    PORT_DOWN = 1 << 1,			    /* the port is administratively down */
	PORT_OPEN = 1 << 2,			    /* the port is open for receiving and transmitting */
    PORT_LINK_DOWN = 1 << 3,        /* no physical link present at the port */
    PORT_ONLY_RECEIVE = 1 << 4,	    /* the port will not forward but only receive packets */
    PORT_ONLY_TRANSMIT = 1 << 5,	/* the port will forward packets and drop received packets */
	PORT_NO_STP = 1 << 6,			/* disable 802.1D spanning tree on the port */
    PORT_NO_RECV = 1 << 7,          /* drop all packets except 802.1D spanning tree packets */
	PORT_NO_RECV_STP = 1 << 8,	    /* drop received 802.1D STP packets */
    PORT_NO_FLOOD = 1 << 9,         /* do not include this port when flooding */
    PORT_HALF_DUPLEX = 1 << 10,     /* the port is administratively configured to be half duplex */
    PORT_FULL_DUPLEX = 1 << 11,     /* the port is administratively configured to be full duplex */
	PORT_ONLY_APP = 1 << 12			/* the port will only forward and receive DAIM applications packets */
};

/* different settings for DAIM OS switch link */
enum switch_link_state {
    LINK_UP = 1 << 0,		/* the link is administratively up */
    LINK_DOWN = 1 << 1	    /* the link is administratively down */
};

/* different settings for DAIM OS entity */
enum daim_entity_state {
    ENTITY_UP = 1 << 0,	        /* the entity is administratively up */
    ENTITY_DOWN = 1 << 1,	    /* the entity is administratively down */
    ENTITY_NOR_MOD = 1 << 2,    /* the entity is configured to operate local functions */
    ETH_BRIDGE = 1 << 3         /* the entity is configured as Ethernet bridge */
};

/* value describing DAIM switch entity belonging */
enum daim_entity_location {
    LOCAL_ENTITY = 0xf1,	/* the entity is local to DAIM OS switch */
    REMOTE_ENTITY = 0xf2	/* the entity is not local to DAIM OS switch */
};

/* different DAIM OS entities */
enum daim_entity_type {
    HOST_ENTITY = 0xf3,	    /* the entity is a host computer */
    DAIM_ENTITY = 0xf4,	    /* the entity is a DAIM switch */
	OTHER_ENTITY = 0xf5	    /* the entity is a forwarding device */
};

/* enumeration for entity port states */
enum daim_entity_port_state {
    ENTITY_PORT_UP = 1 << 0,                /* the port is administratively up */
    ENTITY_PORT_DOWN = 1 << 1,              /* the port is administratively down */
	ENTITY_PORT_OPEN = 1 << 2,              /* the port is open for receiving and transmitting */
    ENTITY_PORT_LINK_DOWN = 1 << 3,         /* no physical link present at the port */
    ENTITY_PORT_ONLY_RECEIVE = 1 << 4,      /* the port will not forward but only receive packets */
    ENTITY_PORT_ONLY_TRANSMIT = 1 << 5,     /* the port will forward packets and drop received packets */
	ENTITY_PORT_NO_STP = 1 << 6,            /* disable 802.1D spanning tree on the port */
    ENTITY_PORT_NO_RECV = 1 << 7,           /* drop all packets except 802.1D spanning tree packets */
	ENTITY_PORT_NO_RECV_STP = 1 << 8,       /* drop received 802.1D STP packets */
    ENTITY_PORT_HALF_DUPLEX = 1 << 10,      /* the port is administratively configured to be half duplex */
    ENTITY_PORT_FULL_DUPLEX = 1 << 11       /* the port is administratively configured to be full duplex */
};

/* value for packet forwarding action type */
enum daim_packet_action_type {
    PACKET_OUTPUT,           /* output to switch port */
    PACKET_SET_VLAN_VID,     /* set the 802.1q VLAN id */
    PACKET_SET_VLAN_PCP,     /* set the 802.1q VLAN priority */
    PACKET_STRIP_VLAN,       /* strip the 802.1q header */
    PACKET_SET_DL_SRC,       /* set Ethernet source address */
    PACKET_SET_DL_DST,       /* set Ethernet destination address */
    PACKET_SET_NW_SRC,       /* set IP source address */
    PACKET_SET_NW_DST,       /* set IP destination address */
    PACKET_SET_NW_TOS,       /* set IP ToS (DSCP field, 6 bits) */
    PACKET_SET_TP_SRC,       /* set TCP/UDP source port */
    PACKET_SET_TP_DST        /* set TCP/UDP destination port */
};

/* structure for data parameter for no rule signal callback function */
struct no_rule_packet_info {
    uint16_t in_port;                           /* input DAIM switch port */
    uint8_t mac_src[MAC_ADDR_LEN];              /* source Ethernet address */
    uint8_t mac_dst[MAC_ADDR_LEN];              /* destination Ethernet address */
    uint16_t ethernet_type;                     /* Ethernet frame type */
    uint32_t ip_source;                         /* source IP address */
    uint32_t ip_destination;                    /* destination IP address */
    uint8_t  ip_netmask_source;                 /* source IP netmask */
    uint8_t  ip_netmask_destination;            /* destination IP netmask */
    uint16_t ip_port_source;                    /* TCP/UDP source port */
    uint16_t tp_port_destination;               /* TCP/UDP destination port */
    uint8_t ip_proto;                           /* IP protocol */
    uint16_t vlan_id;                           /* input VLAN id */
    uint8_t vlan_pcp;                           /* input VLAN priority */
    uint8_t ip_tos;                             /* IP ToS (actually DSCP field, 6 bits) */
};

/* actions are 64-bit aligned */

/* action structure for PACKET_OUTPUT */
struct packet_action_output {
    uint16_t type;          /* PACKET_OUTPUT */
    uint16_t port;          /* switch output port */
    uint8_t pad[4];  
};

/* all ones is to indicate no VLAN id was set */
#define PACKET_VLAN_NONE 0xffff

/* action structure for PACKET_SET_VLAN_VID */
struct packet_action_vlan_vid {
    uint16_t type;          /* PACKET_SET_VLAN_VID */
    uint16_t vlan_vid;      /* VLAN id */
    uint8_t pad[4];
};

/* action structure for PACKET_SET_VLAN_PCP */
struct packet_action_vlan_pcp {
    uint16_t type;          /* OFPAT_SET_VLAN_PCP */
    uint8_t vlan_pcp;       /* VLAN priority */
    uint8_t pad[5];
};

/* action structure for PACKET_STRIP_VLAN */
struct packet_action_str_vlan {
    uint16_t type;          /* PACKET_STRIP_VLAN */
    uint8_t pad[6];
};

/* action structure for PACKET_SET_DL_SRC/DST */
struct packet_action_dl_addr {
    uint16_t type;                  /* PACKET_SET_DL_SRC/DST */
    uint8_t dl_addr[MAC_ADDR_LEN];  /* Ethernet address */
};

/* action structure for PACKET_SET_NW_SRC/DST */
struct packet_action_nw_addr {
    uint16_t type;          /* PACKET_SET_TW_SRC/DST */
    uint32_t nw_addr;       /* IP address */
};

/* action structure for PACKET_SET_TP_SRC/DST */
struct packet_action_tp_port {
    uint16_t type;          /* PACKET_SET_TP_SRC/DST */
    uint16_t tp_port;       /* TCP/UDP port */
    uint8_t pad[4];
};

/* action structure for PACKET_SET_NW_TOS */
struct packet_action_nw_tos {
    uint16_t type;      /* PACKET_SET_TW_SRC/DST */
    uint8_t nw_tos;     /* IP ToS (DSCP field, 6 bits) */
    uint8_t pad[5];
};

/* action header structure which is common to all action structures */
struct packet_action_header {
    uint16_t type;      /* one of PACKET_* */
    uint8_t pad[6];
};

/* structure defining the buffer of a packet used for sending and receiving data from a DAIM application */
struct packet_buffer {
    uint64_t len;       /* size of the raw packet data as pointed by buffer */
    uint8_t *buffer;    /* raw packet to be sent from the DAIM OS switch application / raw packet to be collected by the DAIM OS switch application */
};

/* DAIM OS information tables */

/* DAIM OS description table (read only) */
struct daim_info_table_entry {
	uint16_t daim_state;						/* one of the value from daim_os_state */
	uint16_t features; 							/* bitmap of daim_os_feature */
    uint8_t vendor_description[DESC_STR_LEN];   /* description of DAIM OS vendor */
    uint8_t daim_specification_version;			/* DAIM OS specification version */
    uint16_t daim_release_date[3];				/* DAIM OS version release year */
};

/* DAIM OS switch description table (read only) */
struct switch_table_entry {
    uint64_t id;									    /* unique id of the DAIM OS switch */
    uint8_t mac_addr[MAC_ADDR_LEN];		                /* MAC address of the DAIM OS switch device */
    uint8_t manufacturer_description[DESC_STR_LEN];	    /* description of DAIM OS switch manufacturer */
    uint8_t hardware_description[DESC_STR_LEN];		    /* description of DAIM OS switch hardware */
    uint8_t software_description[DESC_STR_LEN];		    /* description of DAIM OS switch software stack */
    uint8_t serial_number[SERIAL_NUM_LEN];				/* serial number for DAIM OS switch */
    uint32_t vendor_id;								    /* vendor id of DAIM OS switch */
    uint32_t product_id;							    /* product id of DAIM OS switch */
    uint16_t ports;									    /* number of ports in the DAIM OS switch */
	uint16_t switch_state;       					    /* bitmap of daim_switch_state */
	uint16_t switch_capabilities;       			    /* bitmap of daim_switch_capability */
    uint64_t received_packets;			                /* number of total packets received */
    uint64_t received_bytes;			                /* number of total bytes received */
    uint64_t transmitted_packets;		                /* number of total packets transmitted */
    uint64_t transmitted_bytes;			                /* number of total bytes transmitted */
};

/* DAIM OS switch port description table (read only) */
struct switch_port_table_entry {
    uint8_t mac_addr[MAC_ADDR_LEN];		/* MAC address of the DAIM OS switch port */
    uint16_t port_number;				/* DAIM OS switch port number */
    uint16_t port_state;				/* bitmap combination of daim_switch_port_state */
    uint64_t port_speed;                /* maximum port speed as reported from the hardware */
    uint64_t port_mtu;                  /* largest maximum transmission unit as reported from the hardware */
    uint64_t received_packets;			/* number of total packets received in the port */
    uint64_t received_bytes;			/* number of total bytes received in the port */
    uint64_t receive_drops;				/* number of total incoming packets dropped in the port */
	uint64_t receive_errors;			/* total number of receive errors */
	uint64_t receive_frame_err;   		/* total number of frame alignment errors */
    uint64_t receive_over_err;			/* total number of packets overruns */
    uint64_t receive_crc_err;			/* total number of CRC errors */
    uint64_t transmitted_packets;		/* number of total packets transmitted through the port */
    uint64_t transmitted_bytes;			/* number of total bytes transmitted through the port */
    uint64_t transmit_drops;			/* number of total outgoing packets dropped in the port */
	uint64_t transmit_errors;			/* total number of transmit errors */
    uint64_t transmit_over_err;			/* total number of packets overruns */
    uint64_t collisions;				/* number of total packet collisions in the port */
    uint64_t duration; 					/* duration of the port from most recent up statue */
};

/* DAIM OS entity description table (read only) */
struct entity_table_entry {
	uint64_t id;                		    /* entity id as assigned by DAIM OS */
    uint8_t description[DESC_STR_LEN];		/* description for DAIM OS entity */
	uint16_t entity_state;         		    /* bitmap of daim_entity_state */
    uint8_t location; 					    /* one of the daim_entity_location */
    uint8_t type; 					        /* one of the daim_entity_type */
    uint16_t switch_port;				    /* The DAIM OS switch port entity connected to */
    uint64_t received_packets;			    /* number of total packets received by the entity */
    uint64_t received_bytes;			    /* number of total bytes received by the entity */
    uint64_t duration; 					    /* duration of the entity existence in seconds */
};

/* DAIM OS entity port description table (read only) */
struct entity_port_table_entry {
	uint64_t ent_id;                	/* entity id the port belongs to */
    uint8_t mac_addr[MAC_ADDR_LEN];		/* MAC address of the port */
    uint32_t ip_addr;                   /* IP address of the port*/
    uint8_t  ip_netmask;                /* IP netmask of the port*/
    uint16_t port_state;				/* bitmap combination of daim_entity_port_state */
    uint64_t port_speed;                /* port speed as configured by the entity */
    uint64_t received_packets;			/* number of total packets received in the port */
    uint64_t received_bytes;			/* number of total bytes received in the port */
    uint64_t duration; 					/* duration of the port from most recent up state */
};

/* DAIM OS entity ARP request table (read only) */
struct entity_arp_table_entry {
    uint8_t mac_addr[MAC_ADDR_LEN];                 /* MAC address of the DAIM OS entity */
    uint8_t arp_request_message[ARP_PACKET_LEN];    /* ARP request message of corresponding entity */
}; 

/* DAIM OS switch link description table (read only) */
struct switch_link_table_entry {
    uint64_t id;                        /* link id as assigned by DAIM OS */
    uint8_t description[DESC_STR_LEN];	/* description for link */
    uint64_t left_id;                   /* left switch id */
    uint16_t left_port;                 /* switch port link connected to on the left side */
    uint64_t right_id;                  /* right switch id */
    uint16_t right_port;                /* switch port link connected to on the right side */
    uint16_t link_state;                /* bitmap combination of switch_link_state flags */
    uint64_t link_speed;                /* maximum link bandwidth as reported from the hardware */
    uint64_t received_packets;          /* number of total packets transmitted through the link */
    uint64_t received_bytes;            /* number of total bytes transmitted through the link */
    uint64_t duration;                  /* duration of the link from the last up state */
};

/* DAIM OS Network Management tables */

/* DAIM OS packet forwarding table (read and write) */
struct packet_forwarding_table_entry {
    uint16_t in_port;                           /* input DAIM switch port */
    uint8_t mac_src[MAC_ADDR_LEN];              /* source Ethernet address */
    uint8_t mac_dst[MAC_ADDR_LEN];              /* destination Ethernet address */
    uint16_t ethernet_type;                     /* Ethernet frame type */
    uint32_t ip_source[2];                      /* source IP address. first address defines exact match, if second address is present, it defines a range from the first address to the second address */
    uint32_t ip_destination[2];                 /* destination IP address */
    uint8_t  ip_netmask_source;                 /* source IP netmask */
    uint8_t  ip_netmask_destination;            /* destination IP netmask */
    uint16_t tcp_port_source[2];                /* TCP/UDP source port */
    uint16_t tcp_port_destination[2];           /* TCP/UDP destination port */
    uint8_t ip_proto;                           /* IP protocol or lower 8 bits of ARP opcode */
    uint16_t vlan_id;                           /* Input VLAN id */
    uint8_t vlan_pcp;                           /* Input VLAN priority */
    uint8_t ip_tos;                             /* IP ToS (actually DSCP field, 6 bits) */
    uint64_t idle_timeout;                      /* flow rule idle timeout in seconds */
    uint64_t hard_timeout;                      /* flow rule timeout in seconds */
    uint64_t packet_count;                      /* Number of packets processed */
    uint64_t byte_count;                        /* Number of bytes processed */
    uint32_t duration;                          /* total time flow rule is in the table in seconds */
    uint8_t weight;                             /* flow priority 0 minimum, 100 maximum */
    struct packet_buffer packet;                /* raw packet to forward or available for collection */
    uint16_t num_of_actions;                    /* number of actions in actions array */
    struct packet_action_header actions[];      /* actions from packet_action_* */  
};

/* DAIM OS switch configuration table (read and write) */
struct switch_config_table_entry {
    uint16_t switch_state;			/* bitmap of daim_switch_state */
    uint64_t up_time;				/* duration of the switch in seconds before shutting down */
    uint64_t run_out;				/* number of bytes to shut down the switch */
};

/* DAIM OS switch port configuration table (read and write) */
struct switch_port_config_table_entry {
	uint8_t mac_addr[MAC_ADDR_LEN];		/* MAC address of the port */
    uint16_t port_number;           	/* DAIM OS switch port number */
    uint16_t port_state;             	/* bitmap of daim_switch_port_state */
    uint64_t port_speed;            	/* expected or configured port speed */
    uint64_t port_mtu;                  /* expected or configured maximum transmission unit */
    uint64_t up_time;            		/* duration of the port in seconds before shutting down */
    uint64_t run_out;               	/* number of bytes to shut down the port */
};

/* DAIM OS entity configuration table (read and write) */
struct entity_config_table_entry {
	uint64_t id;                		/* entity id as assigned by DAIM OS */
    uint8_t description[DESC_STR_LEN];	/* description for DAIM OS entity */
	uint16_t entity_state;         		/* bitmap daim_entity_state */
    uint64_t up_time;            		/* duration of the DAIM OS entity in seconds before shutting down */
    uint64_t run_out;               	/* number of bytes to shut down the entity */
};

/* DAIM OS switch link configuration table (read and write) */
struct switch_link_config_table_entry {
    uint64_t id;                            /* link id as assigned by DAIM OS and DAIM cloud */
    uint8_t description[DESC_STR_LEN];		/* description for the link */
    uint16_t link_state;                    /* one of the switch_link_state */     
    uint64_t link_speed;                    /* expected or configured bandwidth of the link */
    uint8_t weight;                         /* link priority 0 minimum, 100 maximum */
    uint8_t com_cost;                       /* communication cost for the link 0 minimum, 100 maximum */
    uint64_t up_time;                    	/* duration of the link in seconds before shutting down */
    uint64_t run_out;                       /* number of bytes to shut down the link */
};

#pragma pack(pop)

/* DAIM OS API function prototypes (DAIM applications to DAIM OS) */

/*
    initialises everything needed to support a DAIM application' requests
    returns zero if successful
    one is returned on failure
*/
extern uint16_t daim_init ();

/*
    cleans up all the resources associated with a DAIM application
*/
extern void daim_quit ();

/* 
    writes an entry to one of the DAIM OS network management tables found in daim_table
    table argument can be one of the daim_table
    entry argument is formatted buffer according to respective table entry structure
    size is the size of the entry buffer in bytes
    op_code specifies one of the write operation in table_write_op 
    returns zero if successful
    one is returned on failure
*/
extern uint16_t daim_table_write (uint8_t table, void *entry, uint32_t size, uint8_t op_code);

/*
    reads an entry from one of the DAIM OS tables listed in daim_table and returns a buffer of the respective table entry formatted according to the respective table entry structure
    if the function is successful then entry indicator is incremented
    entry argument used for reading specific entries
    size is the size of the entry buffer in bytes
    returned buffer should be deallocated after use
    returns null if error occurs, i.e. end of a table, no matching entries found
*/
extern void *daim_table_read (uint8_t table, void *entry, uint32_t size);


/*
    resets all the entry indicators to the beginning of the table as specified in the table argument
    table argument is one of the DAIM OS tables listed in daim_table
*/
extern void daim_table_rewind (uint8_t table);

/*
    attach a callback function for a specified DAIM OS signal emission
    sig_type argument is one of the daim_signal_number
    handler is a function of void callback_function (uint16_t sig_num, void *data) type
    sig_num can be found in daim_signal_number
*/
extern void daim_signal (uint16_t sig_type, sighandler handler);

#endif /* daim_os_api.h */
