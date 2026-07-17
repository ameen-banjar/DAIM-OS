#include "daim_os_api.h"
#include "daim_os_cloud.h"
#include "daim_os_sys_api.h"

_Static_assert(sizeof(struct packet_action_header) == 8,
               "packet action headers must be 64-bit aligned");
_Static_assert(sizeof(struct packet_action_output) == 8,
               "packet output actions must be 64-bit aligned");
_Static_assert(sizeof(struct packet_action_nw_addr) == 8,
               "network address actions must be 64-bit aligned");

int main(void)
{
    return 0;
}
