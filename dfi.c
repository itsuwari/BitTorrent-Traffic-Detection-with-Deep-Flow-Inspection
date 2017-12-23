#include "util.h" 
#include <stdlib.h> 
#include "pcap.h" 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <assert.h> 
#include <math.h> 
/* Global variables */ 
flow*  nptr; 
btip* ipptr; 
static int ipcount = 0; 
static int count = 0; 
static int pcount
 = 0;                   
/* packet counter */ 
const
u_char
 *
payload
 = 0;                    
/* Packet payload */ 
float
C
[400][10]; 
int
CCLASS
[400]; 
int
NUMC
=0; 
double
startcputime
; 
char
 *
argv1
; 
void
got_packet
(
u_char
 *
args
, 
const
struct
pcap_pkthdr
 *
header
, 
const
u_char
 *
packet
); 
void
reportData
() ; 
void
readData
(
FILE
* 
fp
) 
{ 
int
i
=0; 
while
(fscanf(fp, 
"%f %f %f %f %f %f %f %f %f %f %d\n"
, 
               &C[i][0], &C[i][1], &C[i][2], &C[i][3], &C[i][4], 
               &C[i][5], &C[i][6], &C[i][7], &C[i][8], &C[i][9], 
               &CCLASS[i])!=EOF) 
    { 
      i++; 
      assert(i<400); 
    } 
  NUMC = i-1; 
} 
int
main
(
int
argc
, 
char
 **
argv
) 
{ 
pcap_t
 *
fp
; 
FILE
 *
fp1
; 
  startcputime=sysGetCpuTime(); 
char
errbuf
[PCAP_ERRBUF_SIZE]; 
if
(argc != 3) { 
    printf(
"usage: %s pcap_filename cluster_center_data_base"
, argv[0]); 
return
 -1; 
  } 
/* Open the capture file */ 
if
 ((fp = pcap_open_offline(argv[1], errbuf)) == 
NULL
) { 
    fprintf(stderr,
"\nUnable to open the file %s.\n"
, argv[1]); 
return
 -1; 
  } 
  argv1=argv[1]; 
/* Open the center database */ 
if
 ((fp1 = fopen(argv[2], 
"r"
)) == 
NULL
) { 
    fprintf(stderr,
"\nUnable to open the file %s.\n"
, argv[2]); 
return
 -1; 
  } 
  readData(fp1); 
/* allocate space for pkt stat */ 
  nptr = (
flow
*)malloc(MAXPACKETS*
sizeof
(flow)); 
  bzero(nptr, MAXPACKETS*
sizeof
(flow)); 
/* allocate space for btip stat */ 
  ipptr = (
btip
*)malloc(2*MAXPACKETS*
sizeof
(btip)); 
bzero(ipptr, MAXPACKETS*
sizeof
(btip)); 
/* read and dispatch packets until EOF is reached */ 
  pcap_loop(fp, 0, got_packet, 
NULL
); 
  qsort(nptr, count, 
sizeof
(flow), (
int
(*)(
const
void
*, 
const
void
*))flowCmpNumPkt); 
  reportData(); 
  pcap_close(fp); 
return
 0; 
} 
