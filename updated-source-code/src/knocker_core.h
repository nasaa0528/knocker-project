#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <signal.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

/* if no port numbers are given scan from 1 to KNOCKER_DEFAULT_PORT_RANGE */
#define KNOCKER_DEFAULT_PORT_RANGE 1024
/* maximum port number to scan to */
#define KNOCKER_MAX_PORT_NUMBER 65535

enum
{ PORT_IS_CLOSED, PORT_IS_OPEN };

unsigned short in_cksum(unsigned short *ptr, int nbytes);
int knocker_portscan_by_hostname (unsigned short port, unsigned int src_addr, unsigned int dst_addr, char *mode, int speed);
int knocker_get_service_by_port (char *service, int port);
