#ifdef __TARGET__

/* getIfAddr.c - retrieve IP address of network interface address*/

/* Copyright 1984 - 2005 Wind River Systems, Inc. */
#include "copyright_wrs.h"

#include <vxWorks.h>
#include <stdio.h>

#include <netconf.h>
#include <netinet/in.h>
#include <net/socketvar.h>
#include <net/domain.h>
#include <sys/socket.h>
#include <hostLib.h>
#include <net/if.h>
#include <net/if_var.h>
#include <net/if_dl.h>
#include <netinet/in_var.h>
#include <ipProto.h>
#include <m2Lib.h>
#include <end.h>
#include <private/muxLibP.h>
#include <inetLib.h>
#ifdef INET6
#include <netdb.h>
#include <net/utils/ifconfig.h>
#endif

#ifdef VIRTUAL_STACK
#include <netinet/vsLib.h>
#include <netinet/vsData.h>
#include <vs/vsIf.h>
#include <netinet/vsIp.h>
#ifdef INET6
#include <vs/vsIp6.h>
#endif
#endif

/* externs */

/* forward functions */

#ifdef INET6
	static char    addr_buf[INET6_ADDRSTRLEN];        /*for getnameinfo()*/
#endif
	static char 	addrString [INET_ADDR_LEN];

	static char 	errString[]="error";

/*
 * getWdbIfAddr - get the first IP address associated with a network interface.
 * 
 * 	This code returns the string of IP address for the interface specified.
 *  
 * Returns:
 *  Success - This code returns the string to the interface IP address.
 *  Error   - returns "error"
 * 
 *  Note: derived from the contents of ifShow().
 * 
 *  The memory containing the IP address is statically declared in this source file.
 */

char *getIfAddr ( char *ifName )
{
    FAST struct ifnet 		*ifp;
    FAST struct ifaddr 		*ifa;
    FAST struct in_ifaddr 	*ia = 0;
    FAST int				nameLen;
    int						ifUnit;
    IP_DRV_CTRL				*pDrvCtrl = NULL;
#ifdef INET6
	struct sockaddr_in6		*sin;
    struct sockaddr_in6		sin6;
    UINT32					scopeid;
    int						error;
#endif

	if (ifName == NULL)		/*check if a name was specified */
	{
		printErr(" getIfAddr Error: interface not specified\n");
		return errString; 
	} else {
		printErr(" getIfAddr: ifName=%s\n", ifName);
	}
	

    for (ifp = ifnet_head.tqh_first; ifp != NULL; ifp = ifp->if_link.tqe_next)
	{
		nameLen = strlen (ifp->if_name);

		if (ifName != NULL)		/* if a name was specified */
		{
			if (strncmp (ifName, ifp->if_name, nameLen) != 0)
			{
				continue;		/* no match - wrong name */
			}

			/*
			 * If the user specified unit ID in ifName compare the unit number
			 */
			if (nameLen < strlen (ifName))
			{
				sscanf (&ifName [nameLen], "%d", &ifUnit);
				if (ifp->if_unit != ifUnit)
				{
					continue;		/* no match - wrong unit ID */
				}
			}
		}


		for(ifa = ifp->if_addrhead.tqh_first;ifa != NULL; ifa = ifa->ifa_link.tqe_next)
		{
			if (ifa->ifa_addr->sa_family == AF_INET)
			{			
				inet_ntoa_b (((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, addrString);
				printErr("getIfAddr: addrString=\"%s\"\n", addrString);
				return addrString;
			}
#ifdef INET6
			else if (ifa->ifa_addr->sa_family == AF_INET6)
			{
				sin = (struct sockaddr_in6 *) ifa->ifa_addr;
				/* use the temporary variable for display */

				bcopy ((char *) sin,(char *) &sin6, sizeof(struct sockaddr_in6));
				if (IN6_IS_ADDR_LINKLOCAL(&sin->sin6_addr) && *(u_short *)&sin->sin6_addr.s6_addr[2] != 0) 
				{
					u_short index;
					index = *(u_short *)&sin->sin6_addr.s6_addr[2];
					sin6.sin6_addr.s6_addr[2] = sin6.sin6_addr.s6_addr[3] = 0; 
					if (sin6.sin6_scope_id == 0)
					{
						sin6.sin6_scope_id = ntohs(index);
					}
				}

				scopeid = sin6.sin6_scope_id;

				error = getnameinfo((struct sockaddr *)&sin6,
							sin6.sin6_len, addr_buf,
							sizeof(addr_buf), NULL, 0,
							NI_NUMERICHOST|NI_WITHSCOPEID);
				if (error != 0)
				{
					inet_ntop(AF_INET6, (void *)(struct sockaddr_in6 *)&(sin6.sin6_addr), addr_buf,sizeof(addr_buf));
				}
				printf("getIfAddr: addr_buf=\"%s\"\n", addr_buf);
				return addr_buf;
			}
#endif 
		}
	}
	
	printErr("getIfAddr Error: \"%s\" - No such interface\n", ifName);
	return errString;
}
#endif
