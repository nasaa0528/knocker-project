#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "knocker_core.h"

#ifndef FALSE
#  define FALSE 0
#endif
#ifndef TRUE
#  define TRUE 1
#endif

/* COMMAND LINE ARGUMENTS DEFINITION  */
/* ********************************** */
  /* host to scan */
#define HOST_SHORT_OPT "-H"
#define HOST_LONG_OPT  "--host"

  /* port number to start with */
#define START_PORT_SHORT_OPT "-SP"
#define START_PORT_LONG_OPT  "--start-port"

	/*for scan type choosing*/
#define SCAN_TYPE "-ST"

	/*for source IP (source ip for sendto())*/
#define SOURCE_IP "-SoIP"

	/*for IP range*/
#define IP_RANGE_OPT  "-IPR"
  /* port number to scan to */
#define END_PORT_SHORT_OPT "-EP"
#define END_PORT_LONG_OPT  "--end-port"

	/*Help menu*/
#define HELP_SHORT_OPT    "-h"
#define HELP_LONG_OPT     "--help"

/*declaring parameters*/
	char *RANGE;
	char *SCN_TP;
	char *SOURCE;
char *HOSTNAME_STRING;
char *SERVICENAME_STRING;
int START_PORT_NUMBER = 0;
int END_PORT_NUMBER = 0;

/*declaring functions*/
int set_scan_type (const char *hostname);
void unset_scan_type (void);
int set_source_ip (const char *hostname);
void unset_source_ip (void);
int set_range (const char *hostname);
void unset_range (void);
int set_hostname_string (const char *hostname);
void unset_hostname_string (void);
int parse_args (int argc, char *argv[]);
int check_port_number (int port);
void print_version_info (void);
void print_help_info ( void );
void quit (int state);

/*set and unset functions*/
int set_scan_type (const char *hostname)
	{
	  SCN_TP = malloc (strlen (hostname) + 1);
	  strcpy (SCN_TP, hostname);
	  return 0;
	}
void unset_scan_type (void)
	{
	  if (SCN_TP != NULL)
	    free (SCN_TP);
	  SCN_TP = NULL;
	}
int set_source_ip (const char *hostname)
	{
	  SOURCE = malloc (strlen (hostname) + 1);
	  strcpy (SOURCE, hostname);
	  return 0;
	}
void unset_source_ip (void)
	{
	  if (SOURCE != NULL)
	    free (SOURCE);
	  SOURCE = NULL;
	}
int set_range (const char *hostname)
	{
	  RANGE = malloc (strlen (hostname) + 1);
	  strcpy (RANGE, hostname);
	  return 0;
	}
	void unset_range (void)
	{
	  if (RANGE != NULL)
	    free (RANGE);
	  RANGE = NULL;
	}
int set_hostname_string (const char *hostname)
{
  HOSTNAME_STRING = malloc (strlen (hostname) + 1);
  strcpy (HOSTNAME_STRING, hostname);
  return 0;
}
void unset_hostname_string (void)
{
  if (HOSTNAME_STRING != NULL)
    free (HOSTNAME_STRING);
  HOSTNAME_STRING = NULL;
}
int set_servicename_string (int lenght)
{
  SERVICENAME_STRING = malloc (lenght + 1);
  return 0;
}
void unset_servicename_string (void)
{
  if (SERVICENAME_STRING != NULL)
    free (SERVICENAME_STRING);
  SERVICENAME_STRING = NULL;
}
int is_port_number_valid ( int port )
{
  if ( port < 0 )
    return FALSE;
  if ( port > KNOCKER_MAX_PORT_NUMBER)
    return FALSE;
  return TRUE;
}
/*quit function*/
void quit (int state)
{

  unset_hostname_string ();
  unset_servicename_string();
  unset_range();
  unset_scan_type ();
  unset_source_ip ();
  exit (state);
}
/*help function*/
void print_help_info (void)
{
  fprintf (stdout, "%s, the net portscanner updated by Nasantogtokh A.\n", PACKAGE);
  fprintf (stdout, "\n");
fprintf (stdout, "you can find XMAS, FIN and NULL\n");
  fprintf (stdout, "Usage: %s %s <SCAN_TYPE> %s <YOUR_IP> %s <TARGET_IP> %s <START_PORT> %s <END_PORT>\n", PACKAGE, SCAN_TYPE, SOURCE_IP,  HOST_SHORT_OPT, START_PORT_SHORT_OPT, END_PORT_SHORT_OPT);
  fprintf (stdout, "Example: %s %s XMAS %s 192.168.84.149 %s 192.168.1.1 %s 1 %s 1024 OR  \n", PACKAGE, SCAN_TYPE, SOURCE_IP,  HOST_SHORT_OPT, START_PORT_SHORT_OPT, END_PORT_SHORT_OPT);
fprintf (stdout, "Example: %s %s FIN %s 192.168.84.149 %s 192.168.1.1 %s 1 %s 1024\n", PACKAGE, SCAN_TYPE, SOURCE_IP,  IP_RANGE_OPT, START_PORT_SHORT_OPT, END_PORT_SHORT_OPT);
  fprintf (stdout, "\n");
}



int parse_args (int argc, char *argv[])
{
  int i;

  if (argv[1] == NULL)
    {
      fprintf (stderr, "%s: no arguments given\n", PACKAGE);
      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
	       HELP_LONG_OPT);
      quit (1);
    }

  for (i = 1; i <= argc - 1; i++)
    {
/*PACKAGE checking*/
     if((!strcmp (argv[i], HELP_SHORT_OPT))
         || (!strcmp (argv[i], HELP_LONG_OPT)))
        {
	  print_help_info();
	  quit(0);
	}
/*Host options checking and inputting host name*/
      else if ((!strcmp (argv[i], HOST_SHORT_OPT))
	       || (!strcmp (argv[i], HOST_LONG_OPT)))
	{
	  if (++i == argc)
	    {
	      fprintf (stderr, "%s: error, no host to scan given\n", PACKAGE);
	      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
		       HELP_LONG_OPT);
	      quit (1);
	    }
	  set_hostname_string (argv[i]);
	}
/*Source IP options checking and inputting source IP*/
   else if ((!strcmp (argv[i], SOURCE_IP)))
	{
	  if (++i == argc)
	    {
	      fprintf (stderr, "%s: error, no source IP given\n", PACKAGE);
	      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
		       HELP_LONG_OPT);
	      quit (1);
	    }
	set_source_ip (argv[i]);
	}
/*scan type options checking and inputting scan type*/
   else if ((!strcmp (argv[i], SCAN_TYPE)))
	{
	  if (++i == argc)
	    {
	      fprintf (stderr, "%s: error, no scan type given\n", PACKAGE);
	      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
		       HELP_LONG_OPT);
	      quit (1);
	    }
	set_scan_type (argv[i]);
	}
/*range options checking and inputting ip range. For example 192.168.1.1-255*/
		else if (!strcmp (argv[i], IP_RANGE_OPT))
	{
	  if (++i == argc)
	    {
	      fprintf (stderr, "%s: error, no start ip range given\n", PACKAGE);
	      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
		       HELP_LONG_OPT);
	      quit (1);
	    }

	  set_range (argv[i]);
	}			
		/*start port options checking and inputting*/
      else if ((!strcmp (argv[i], START_PORT_SHORT_OPT))
	       || (!strcmp (argv[i], START_PORT_LONG_OPT)))
	{
	  if (++i == argc)
	    {
	      fprintf (stderr,
		       "%s: error, no port number, where to start the scan from, given\n",
		       PACKAGE);
	      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
		       HELP_LONG_OPT);
	      quit (1);
	    }

	  START_PORT_NUMBER = atoi (argv[i]);
		/*checking port number value*/
	  if (is_port_number_valid(START_PORT_NUMBER) != TRUE)
	    {
	      fprintf (stderr,"%s: error, invalid start port number `%d' given\n", PACKAGE, START_PORT_NUMBER);
              quit(1);
	    }
	}
	/*end port number options checking and inputting*/
      else if ((!strcmp (argv[i], END_PORT_SHORT_OPT))
	       || (!strcmp (argv[i], END_PORT_LONG_OPT)))
	{
	  if (++i == argc)
	    {
	      fprintf (stderr,
		       "%s: error, no port number, where to scan to, given\n",
		       PACKAGE);
	      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
		       HELP_LONG_OPT);
	      quit (1);
	    }
	  END_PORT_NUMBER = atoi (argv[i]);
/*checking end port number value*/
	  if (is_port_number_valid(END_PORT_NUMBER) != TRUE)
	    {
	      fprintf (stderr,"%s: error, invalid end port number `%d' given\n", PACKAGE, END_PORT_NUMBER);
              quit(1);
	    }
	}
       else
        {
           fprintf (stderr, "%s: invalid arguments given\n", PACKAGE);
           fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE,
	       HELP_LONG_OPT);
           quit (1);
	}


    }				/* end of for loop */

  return 0;
}

/*starting main function*/
int main (int argc, char *argv[])
{
/*declaring parameters*/
  int open_ports    = 0;
  int scanned_ports = 0;
  int a[20], i, low[4], high[4],l,h,coma=0;
  if(geteuid()!=0)
    printf("YOU MUST BE ROOT, \n IF YOU ARE NOT IN ROOT YOU CANNOT SCAN THE PORTS !!!!");
printf("DEBUG:   CHECKING INPUT PARAMETERS\n");

  parse_args (argc, argv);
printf("DEBUG:   WE CHECKED INPUT PARAMETERS\n");

  set_servicename_string (20);
printf("DEBUG:   WORKED SER_SERVICENAME\n");
	if (RANGE!=NULL)
	{
printf("SCANNING FOR A RANGE\n");
/*IP RANGE LOOP*/
		for ( i = 0; i < 20 ; i++ )
			{
			a[i]=RANGE[i];	//"range"-n buh utgiig too helbereer "a"-ruu huulj avah;
			}
				for(i = 0; i < 20; i++)
				{
					if (a[i]==46) //hamgiin suuliin "."-temdegtiin index-g ni "coma"-ruu hadgalah; 
					{	
					++coma;
						if(coma==3)
						coma=i;
					}
					
						if (a[i]==45) 	//"-" temdegtees hoish 3 uragsh 3 temdegtiing "low" bolon "high" ruu huulj avah
						{
						low[0]=a[i-3];
						low[1]=a[i-2];
						low[2]=a[i-1];
						high[0]=a[i+1];
						high[1]=a[i+2];
						high[2]=a[i+3];												
						}
				}
		if ( low [0] != 46 && low [1] !=46 && low [2] !=46 ) /* "low" bolon "high"-g zadalj "l" bolon "h" int helbereer oruulah  */
			{
			l=(low[2]-48)+(low[1]-48)*10+(low[0]-48)*100;
			}
		else if (low[0]==46 && low[1]!=46 && low[2]!=46 )
			{
			l=(low[1]-48)*10+(low[2]-48);
			}
		else if (low[0]!=46 && low[1]==46 && low[2]!=46 )
			{
			l=low[2]-48;
			}
		if ( high [1] !=0 && high[2]!=0 )
			{
			h=(high[0]-48)*100+(high[1]-48)*10+high[2]-48;
			}
		else if ( high [1] !=0 && high[2]==0 )
			{
			h=(high[0]-48)*10+high[1]-48;
			}
		else if ( high [1] == 0 && high[2]==0 )
			{
			h=high[0]-48;
			}
		if(l<0 || h<0 || l>255 || h>255){ //hervee ip hayagiin range buruu bval aldaa shideed gargana;
		fprintf(stderr, "THIS IS NOT IP ADDRESS !!! \n");
		quit(0);
		}
				RANGE[coma+4]=RANGE[coma+5]=RANGE[coma+6]=0;
				for(l; l<=h; l++){    /* RANGE-g "l"-ees "h" hurtel davtaj tuunii utgiig ni RANGE-d olgoh */
				if (l>=100)
				{
				RANGE[coma+1]=l/100+48;
				RANGE[coma+2]=(l-l/100*100)/10+48;
				RANGE[coma+3]=(l-l/100*100-(l-l/100*100)/10*10)+48;
				}
				else if (l>=10 && l<100){
				RANGE[coma+3]=0;
				RANGE[coma+1]=l/10+48;
				RANGE[coma+2]=l-(l/10)*10+48;
				}
				else if(l>=1 && l<10){
				RANGE[coma+3]=RANGE[coma+2]=0;
				RANGE[coma+1]=l+48;
				}

				fprintf(stdout, "RANGE OF IP : %s   \n",RANGE);

 				if ( (START_PORT_NUMBER == 0 ) && ( END_PORT_NUMBER == 0 ) )
				    {
			       int port;

			       fprintf(stdout, "Scanning host: %s from port: %d to port: %d\n", RANGE, 1,  KNOCKER_DEFAULT_PORT_RANGE);

			       for (port = 1; port < KNOCKER_DEFAULT_PORT_RANGE; port++)
			          {
				printf("NOW SCANNING PORT :  %d\n", port);
			            if (knocker_portscan_by_hostname (port, inet_addr(SOURCE), inet_addr(RANGE), SCN_TP, 1000) == PORT_IS_OPEN)
				      {
					open_ports++;
				        knocker_get_service_by_port (SERVICENAME_STRING, port);
 			               fprintf(stdout, "%d/tcp, %s, --> open | filtered\n", port, SERVICENAME_STRING);
				      }

				  }
			       scanned_ports = port;
			    }

			  else if ( START_PORT_NUMBER > END_PORT_NUMBER )
			    {
			       int port;

 			      fprintf(stdout, "Scanning host: %s from port: %d to port: %d\n\n", RANGE, START_PORT_NUMBER, END_PORT_NUMBER);

 			      for (port = START_PORT_NUMBER; port > END_PORT_NUMBER; port--)
   			       {
				if (knocker_portscan_by_hostname (port, inet_addr(SOURCE), inet_addr(RANGE), SCN_TP, 1000) == PORT_IS_OPEN)
				      {
			        open_ports++;
				        knocker_get_service_by_port (SERVICENAME_STRING, port);
 		               fprintf(stdout, "%d/tcp, %s --> open | filtered\n", port, SERVICENAME_STRING);
			      }

				  }
 			      scanned_ports = START_PORT_NUMBER - END_PORT_NUMBER ;
 			   }
 			 else
   			 {
			       int port;
				
			       fprintf(stdout, "Scanning host: %s from port: %d to port: %d\n\n", RANGE, START_PORT_NUMBER, END_PORT_NUMBER);

 			      for (port = START_PORT_NUMBER; port < END_PORT_NUMBER; port++)
			          {
				printf("Port davtaj bn \n");
				if (knocker_portscan_by_hostname (port, inet_addr(SOURCE), inet_addr(RANGE), SCN_TP, 1000) == PORT_IS_OPEN)
				      {
printf("Neelttei port oldloo \n");
				        open_ports++;
				        knocker_get_service_by_port (SERVICENAME_STRING, port);
			                fprintf(stdout, "%d/tcp, %s --> open | filtered\n", port, SERVICENAME_STRING);
				      }

					  }
			       scanned_ports =  END_PORT_NUMBER - START_PORT_NUMBER;
 			   }

 			 fprintf (stdout, "\n");
 			 fprintf (stdout, "%s port scan on host %s completed.\n", PACKAGE, RANGE);
 			 fprintf (stdout, "Total scanned ports: %d (%d - %d)\n", scanned_ports, START_PORT_NUMBER, END_PORT_NUMBER );
 			 fprintf (stdout, "Total open ports found: %d\n", open_ports);
  	      			fprintf (stdout, "\n");
			fprintf(stdout, "===============================================================	\n===============================================================\n");
				}
			}

else {
  fprintf (stdout, "\n");

  if ( (START_PORT_NUMBER == 0 ) && ( END_PORT_NUMBER == 0 ) )
    {
       /* default portscan */
       int port;

       fprintf(stdout, "Scanning host: %s from port: %d to port: %d\n\n", HOSTNAME_STRING, 1,  KNOCKER_DEFAULT_PORT_RANGE);

       for (port = 1; port < KNOCKER_DEFAULT_PORT_RANGE; port++)
          {
            if (knocker_portscan_by_hostname (port, inet_addr(SOURCE), inet_addr(HOSTNAME_STRING), SCN_TP, 1000) == PORT_IS_OPEN)
	      {
	        open_ports++;
	        knocker_get_service_by_port (SERVICENAME_STRING, port);
                fprintf(stdout, "%d/tcp, %s, --> open | filtered\n", port, SERVICENAME_STRING);
	      }

	  }
       scanned_ports = port;
    }

  else if ( START_PORT_NUMBER > END_PORT_NUMBER )
    {
       /* reverse scan */
       int port;

       fprintf(stdout, "Scanning host: %s from port: %d to port: %d\n\n", HOSTNAME_STRING, START_PORT_NUMBER, END_PORT_NUMBER);

       for (port = START_PORT_NUMBER; port > END_PORT_NUMBER; port--)
          {
            if (knocker_portscan_by_hostname (port, inet_addr(SOURCE), inet_addr(HOSTNAME_STRING), SCN_TP, 1000) == PORT_IS_OPEN)
	      {
	        open_ports++;
	        knocker_get_service_by_port (SERVICENAME_STRING, port);
                fprintf(stdout, "%d/tcp, %s --> open | filtered\n", port, SERVICENAME_STRING);
	      }

	  }
       scanned_ports = START_PORT_NUMBER - END_PORT_NUMBER ;
    }
  else
    {
       /* scan from START_PORT_NUMBER to END_PORT_NUMBER */
       int port;

       fprintf(stdout, "Scanning host: %s from port: %d to port: %d\n\n", HOSTNAME_STRING, START_PORT_NUMBER, END_PORT_NUMBER);

       for (port = START_PORT_NUMBER; port < END_PORT_NUMBER; port++)
          {
            if (knocker_portscan_by_hostname (port, inet_addr(SOURCE), inet_addr(HOSTNAME_STRING), SCN_TP, 1000) == PORT_IS_OPEN)
	      {
	        open_ports++;
	        knocker_get_service_by_port (SERVICENAME_STRING, port);
                fprintf(stdout, "%d/tcp, %s --> open | filtered\n", port, SERVICENAME_STRING);
	      }

	  }
       scanned_ports =  END_PORT_NUMBER - START_PORT_NUMBER;
    }

  fprintf (stdout, "\n");
  fprintf (stdout, "%s port scan on host %s completed.\n", PACKAGE, HOSTNAME_STRING);
  fprintf (stdout, "Total scanned ports: %d (%d - %d)\n", scanned_ports, START_PORT_NUMBER, END_PORT_NUMBER );
  fprintf (stdout, "Total open ports found: %d\n", open_ports);
  fprintf (stdout, "\n");


}
  quit (0);			/* exit the program */

  return 0;			/* avoid compilation warning */
}
