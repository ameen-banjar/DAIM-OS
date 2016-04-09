/*  DAIM OS platform agnostic C header file
    Definitions of DAIM OS System API functions */

#ifndef DAIM_OS_SYS_H
#define DAIM_OS_SYS_H

#include <stdint.h>

#define DAIM_OS_VERSION 0x01

#define DESC_STR_LEN 256
#define SERIAL_NUM_LEN 32
#define MAC_ADDR_LEN 6

#pragma pack(push, 1)   /* disable structure padding */

/* error codes for System API (network device software interface for DAIM OS) */
#define EPERM		-1		/* operation not permitted */
#define EIO			-2		/* I/O error */
#define EBUSY		-3		/* device or resource busy */
#define EINVAL		-4		/* invalid argument */
#define EPFERR		-5		/* port frame alignment error */
#define EPOERR		-6		/* port packet receive overrun */
#define EPCERR		-7		/* port CRC error */
#define EPTOERR		-8		/* port transmit packet overrun */
#define EPCOERR 	-9		/* packet collection in the port */
#define EPNULL      -10     /* port does not exist */

/* request_code enumeration for daim_switch_ioctl */
enum daim_switch_management {
	IOCTL_SWITCH_INFO,
	IOCTL_SWITCH_POWER,
	IOCTL_PORT_STATE,
	IOCTL_PORT_CONTROL
};

/* Capabilities of DAIM OS switch */
enum daim_switch_capability {
    STP = 1 << 0,  		/* 802.1d spanning tree */
    IP_REASM = 1 << 1   /* Can reassemble IP fragments */
};

/* to be used for encoding or decoding power in switch_port_control and switch_port_state structure */
enum device_power {
    ON = 0xfa,
    OFF = 0xfb
};

/* to be used for encoding or decoding link in switch_port_state structure */
enum port_link {
    LINK_UP = 0xfa,
    LINK_DOWN = 0xfb
};

/* to be used for encoding or decoding stp in switch_port_control and switch_port_state structure */
enum port_stp {
    STP_ENABLED = 0xfa,
    STP_DISABLED = 0xfb
};

/* to be used for encoding or decoding duplex in switch_port_control and switch_port_state structure */
enum port_duplex {
    FULL_DUPLEX = 0xfa,
    HALF_DUPLEX = 0xfb
};

/* structure for a single port */
struct switch_port {
    uint16_t port_no;
    uint8_t mac_addr[MAC_ADDR_LEN];
};

/* structure for data argument to be used with IOCTL_SWITCH_INFO request_code */
struct switch_info {
	uint8_t mac_addr[MAC_ADDR_LEN];		                /* MAC address of the DAIM OS switch device or zero when not available */
	uint8_t manufacturer_description[DESC_STR_LEN];	    /* description of DAIM OS switch manufacturer */
    uint8_t hardware_description[DESC_STR_LEN];		    /* description of DAIM OS switch hardware */
	uint8_t software_description[DESC_STR_LEN];			/* description of DAIM OS switch device manager aka hardware operating system */
    uint8_t serial_number[SERIAL_NUM_LEN];				/* serial number for DAIM OS switch */
	uint32_t vendor_id;								    /* vendor id of DAIM OS switch */
	uint32_t product_id;							    /* product id of DAIM OS switch */
	uint16_t ports;									    /* number of ports in the DAIM OS switch */
	uint16_t switch_capabilities;					    /* bitmap of daim_switch_capability flags */
    struct switch_port ports[];                         /* ports array */
};

/* structure for data argument to be used with IOCTL_PORT_STATE request_code */
struct switch_port_state {
	uint8_t mac_addr[MAC_ADDR_LEN];
	uint8_t power;									
	uint8_t link;
	uint8_t stp;
	uint8_t duplex;
	uint64_t speed;
};

/* structure for data argument to be used with IOCTL_PORT_CONTROL request_code */
struct switch_port_control {
	uint8_t mac_addr[MAC_ADDR_LEN];
	uint8_t power;
	uint8_t stp;
	uint8_t duplex;
	uint64_t speed;
};

/* System API for DAIM OS (network device software interface for DAIM OS) */

/*
    reads from a device port specified in port_num and stores buffer into the *buffer
    size specifies the number of bytes to read
    if size is set to -1, function stores the entire buffer into the *buffer
    on success, the number of bytes read is returned
    returns negative if error occurs
*/
extern int daim_port_read (uint8_t mac_addr[MAC_ADDR_LEN], void *buffer, uint64_t size);

/*
    writes the buffer pointed by *buffer to a device port specified in port_num
    size specifies the number of bytes to write from the *buffer
    on success, the number of bytes written is returned
    returns negative if error occurs
*/
extern int daim_port_write (uint8_t mac_addr[MAC_ADDR_LEN], const void *buffer, uint64_t size);

/*
    manipulates the underlying DAIM OS switch parameters
    request_code determines type of request to the device
    data is a pointer to the memory holding request data for passing to the device or is a pointer to buffer for holding request data from the device
    on success, zero is returned
    returns negative if error occurs
*/
extern int daim_switch_ioctl (uint64_t request_code, void *data);

#endif /* daim_os_sys_api.h */
