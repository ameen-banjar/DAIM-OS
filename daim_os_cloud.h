/*  DAIM OS Cloud protocol platform agnostic C header file
    Definitions of DAIM OS Cloud protocol (communication between a DAIM OS switch and the DAIM cloud) */

#ifndef DAIM_OS_CLOUD_H
#define DAIM_OS_CLOUD_H

#include <stdint.h>

#define DAIM_OS_VERSION 0x01

#define DESC_STR_LEN 256
#define SERIAL_NUM_LEN 32
#define MAC_ADDR_LEN 6

#pragma pack(push, 1)   /* disable structure padding */

/* enumeration for DAIM OS cloud messages */
enum daim_cl_msg_type {
    DCP_REQUEST_ID,         /* message from DAIM switch to cloud */
    DCP_OFFER_ID,           /* message from DAIM cloud to switch */
    DCP_ACCEPT_ID,          /* message from DAIM switch to cloud */
    DCP_RENEW_ID,           /* message from DAIM cloud to switch */
    DCP_UPLOAD_LINKS,       /* message from DAIM switch to cloud */
    DCP_ACK_LINKS,          /* message from DAIM cloud to switch */
    DCP_UPLOAD_HOSTS,       /* message from DAIM switch to cloud */
    DCP_ACK_HOSTS,          /* message from DAIM cloud to switch */
    DCP_REQUEST_LINKS,      /* message from DAIM switch to cloud */
    DCP_REPLY_LINKS,        /* message from DAIM cloud to switch */
    DCP_REQUEST_HOSTS,      /* message from DAIM switch to cloud */
    DCP_REPLY_HOSTS         /* message from DAIM cloud to switch */
};

/* structure for a single host physical port */
struct daim_host_port {
    uint8_t mac_addr[MAC_ADDR_LEN];		/* MAC address of the port */
    uint64_t port_speed;                /* maximum port speed as reported from the hardware */
};

/* structure for a host used for uploading host data to the cloud */
struct daim_host {
    uint64_t id;                    /* host id as assigned by DAIM OS */
    uint16_t switch_port;	        /* The DAIM OS host port entity connected to */
    uint64_t no_of_ports;           /* number of ports */
    struct daim_host_port ports[];  /* ports array */
};

/* structure for a single link used for uploading link data to the cloud */
struct daim_switch_link {
    uint16_t left_port;     /* DAIM switch port the link connected to */
    uint64_t right_id;      /* id of the DAIM switch the link connected in the other end */
    uint16_t right_port;    /* port of the DAIM switch the link connected to on the other end */
    uint8_t matric;         /* link capability 0 minimum, 100 maximum */
};

/* DAIM OS cloud message data header structure for cloud message data structures */
struct daim_cl_msg_data_header {
    uint64_t len;   /* length of cloud message data structure */
};

/*
    structure for switch id request to the cloud
    to be used with message types DCP_REQUEST_ID and DCP_RENEW_ID
*/
struct daim_cl_msg_data_request_id {
    uint64_t previous_id;               /* previous id of the DAIM switch */
    uint32_t transaction_id;            /* facilitate pairing between messages */
    uint8_t mac_addr[MAC_ADDR_LEN];     /* MAC address of the DAIM switch */
};

/*
    structure for messages for offering and acknowledgment of id between DAIM cloud and switch
    to be used with message types DCP_OFFER_ID and DCP_ACCEPT_ID
*/
struct daim_cl_msg_data_id {
    uint32_t transaction_id;    /* facilitate pairing between messages */
    uint64_t id;                /* id offered to the DAIM switch / id acknowledged by the DAIM switch */
};

/*
    structure for uploading links to the cloud
    to be used with message type DCP_UPLOAD_LINKS
*/
struct daim_cl_msg_data_up_links {
    uint32_t transaction_id;            /* facilitate pairing between messages */
    uint64_t id;                        /* id of the DAIM switch */
    uint64_t num_of_links;              /* number of links */
    struct daim_switch_link links[];    /* links array */
};

/*
    structure for message for acknowledgment of links by the cloud to the switch
    to be used with message type DCP_ACK_LINKS
*/
struct daim_cl_msg_data_ack_links {
    uint32_t transaction_id;            /* facilitate pairing between messages */
    uint64_t id;                        /* id of the DAIM switch */
    uint64_t num_of_links;              /* number of links */
};

/*
    structure for uploading hosts to the cloud
    to be used with message type DCP_UPLOAD_HOSTS
*/
struct daim_cl_msg_data_up_hosts {
    uint32_t transaction_id;            /* facilitate pairing between messages */
    uint64_t id;                        /* id of the DAIM switch */
    uint64_t num_of_hosts;              /* number of hosts */
    struct daim_host hosts[];           /* hosts array */
};

/*
    structure for message for acknowledgment of hosts by the cloud to the switch
    to be used with message type DCP_ACK_HOSTS
*/
struct daim_cl_msg_data_ack_hosts {
    uint32_t transaction_id;            /* facilitate pairing between messages */
    uint64_t id;                        /* id of the DAIM switch */
    uint64_t num_of_hosts;              /* number of hosts */
};

/*
    structure for links and hosts requests by the DAIM switch to the the cloud
    to be used with message types DCP_REQUEST_HOSTS and DCP_REQUEST_LINKS
*/
struct daim_cl_msg_data_request_data {
    uint32_t transaction_id;            /* facilitate pairing between messages */
};

/*
    structure for DAIM switch for decoding links data from the cloud
    to be used with message type DCP_REPLY_LINKS
*/
struct daim_cl_msg_data_reply_links {
    uint32_t transaction_id;            /* facilitate pairing between messages */
    uint64_t num_of_links;              /* number of links */
    struct daim_switch_link links[];    /* links array */
};

/*
    structure for DAIM switch for decoding hosts data from the cloud
    to be used with message type DCP_REPLY_HOSTS
*/
struct daim_cl_msg_data_reply_hosts {
    uint32_t transaction_id;            /* facilitate pairing between messages */
    uint64_t num_of_hosts;              /* number of hosts */
    struct daim_host hosts[];           /* hosts array */
};

/* DAIM OS cloud header message structure */
struct daim_cl_message {
    uint8_t version;    /* DAIM OS version */
    uint8_t type;       /* one of the DCP_ constants */
    uint8_t data[];     /* buffer formatted with one of daim_cl_msg_data_* structures */
};

#endif /* daim_os_cloud.h */
