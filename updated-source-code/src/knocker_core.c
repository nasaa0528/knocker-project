#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "knocker_core.h"
//#define SYN "SYN"
#define FIN "FIN"
#define XMAS "XMAS"
#define NUL "NULL"

/*Well known port names*/
int knocker_get_service_by_port (char *service, int port)
{
  struct servent *service_info;

  service_info = getservbyport (htons (port), "tcp");

  if (!service_info)
    {
      strcpy (service, "unknown");
      return -1;
    }
  else
    {
      strcpy (service, service_info->s_name);
    }

  return 0;
}
/*checksum*/
unsigned short in_cksum(unsigned short *ptr, int nbytes)
{
        register long           sum;            /* assumes long == 32 bits */
        u_short                 oddbyte;
        register u_short        answer;         /* assumes u_short == 16 bits */

        /*
         * Our algorithm is simple, using a 32-bit accumulator (sum),
         * we add sequential 16-bit words to it, and at the end, fold back
         * all the carry bits from the top 16 bits into the lower 16 bits.
         */

        sum = 0;
        while (nbytes > 1)  {
                sum += *ptr++;
                nbytes -= 2;
        }

                                /* mop up an odd byte, if necessary */
        if (nbytes == 1) {
                oddbyte = 0;            /* make sure top half is zero */
                *((u_char *) &oddbyte) = *(u_char *)ptr;   /* one byte only */
                sum += oddbyte;
        }

        /*
         * Add back carry outs from top 16 bits to low 16 bits.
         */

        sum  = (sum >> 16) + (sum & 0xffff);    /* add high-16 to low-16 */
        sum += (sum >> 16);                     /* add carry */
        answer = ~sum;          /* ones-complement, then truncate to 16 bits */
        return(answer);
}

int knocker_portscan_by_hostname (unsigned short port, unsigned int src_addr, unsigned int dst_addr, char *mode, int speed)
{

   int bla;

   /* for select() */
   fd_set readfs;
   struct timeval tv;
   

   /* tcp header */
   struct tcphdr send_tcp;

   /* packet */
   struct recv_tcp
   {
      struct iphdr ip;
      struct tcphdr tcp;
      unsigned char data[65535];
   }  recv_tcp;

   /* ip header */
   struct pseudo_header
   {
      unsigned int source_address;
      unsigned int dest_address;
      unsigned char placeholder;
      unsigned char protocol;
      unsigned short tcp_length;
      struct tcphdr tcp;
   } pseudo_header;

   int sock;
   struct sockaddr_in sin;
   static int add = 0;
   add++;                               /* yeah, ids dedectd this shit... */

   send_tcp.source = getpid() + add;    /* source port */
   send_tcp.dest = htons(port);         /* dest port */
   send_tcp.seq = getpid() + add;       /* seq number */
   send_tcp.ack_seq = 0;
   send_tcp.res1 = 0;
   send_tcp.doff = 5;
   send_tcp.fin = 0;
   send_tcp.syn = 0;
   send_tcp.rst = 0;
   send_tcp.psh = 0;
   send_tcp.ack = 0;			/* ack number */
   send_tcp.urg = 0;
   send_tcp.window = htons(512);	/* window size */
   send_tcp.check = 0;
   send_tcp.urg_ptr = 0;


if(!strcmp (mode, NUL)){
send_tcp.syn=0;
}
else if(!strcmp (mode, FIN)){
send_tcp.fin = 1;
}
else if(!strcmp (mode, XMAS)){
send_tcp.fin = 1;
send_tcp.psh = 1;
send_tcp.urg = 1;
}
//else fprintf(stderr, "WRONG TYPE OF INPUT PLEASE TRY AGAIN ");
/* ip header */
   pseudo_header.source_address = src_addr;  /* my ip */
   pseudo_header.dest_address = dst_addr;    /* dest ip */
   pseudo_header.placeholder = 0;
   pseudo_header.protocol = IPPROTO_TCP;     /* tcp/ip */
   pseudo_header.tcp_length = htons(20);

   bcopy(&send_tcp, &pseudo_header.tcp, 20);
   send_tcp.check = in_cksum((unsigned short *)&pseudo_header, 32);

   /* where is the socket? */
   sin.sin_family = AF_INET;
   sin.sin_port = htons(port);
   sin.sin_addr.s_addr = dst_addr;

   sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
   if(sock < 0)
   {
      printf("couldnt open socket\n");
      exit(1);
   }



   /* set timer and prepare for select() */
   tv.tv_sec=0;
   tv.tv_usec=speed;
   FD_ZERO(&readfs);
   FD_SET(sock, &readfs);


   /* send paket */
   sendto(sock, &send_tcp, 20, 0, (struct sockaddr *)&sin, sizeof(sin));

   /* "sniff" answer */
   while(1)
   {
      bla=select(sock+1, &readfs, NULL, NULL, &tv);
      if(bla)
        read(sock, (struct recv_tcp *)&recv_tcp, 65535); /* new data */
      else
        return PORT_IS_OPEN;                                       /* port open */
      /* is this our packet? */
      if(recv_tcp.tcp.dest == (getpid() + add))
      {
         /* yes! */
         close(sock);

         if(recv_tcp.tcp.rst == 1) {           
	return PORT_IS_CLOSED;
}
         else 
           return PORT_IS_CLOSED;
      }
   } 
}
