f
low
* 
r
 = bsearch(&n, nptr, count, 
sizeo
f
(
f
low), (
int
(*)(
const
void
*, 
const
void
*))
f
lowCmp);
if
 (r) { 
    r->numTPkt++; 
    r->infoptr[r->infonum].avgSize = ((r->infoptr[r->infonum].avgSize * r->infoptr[r-
>infonum].numPkt) + ntohs(ip->ip_len))/(r->infoptr[r->infonum].numPkt+1); 
    r->infoptr[r->infonum].numPkt++; 
    r->infoptr[r->infonum].totalHeaderSize += size_ip + size_tcp; 
    r->infoptr[r->infonum].totalSize += ntohs(ip->ip_len); 
    r->infoptr[r->infonum].numSendPkt++; 
    r->infoptr[r->infonum].totalSendSize+=ntohs(ip->ip_len); 
    r->infoptr[r->infonum].totalSendHeaderSize+= size_ip + size_tcp; 
    dp[0]=r->infoptr[r->infonum].numPkt; 
    dp[1]=r->infoptr[r->infonum].avgSize; 
    dp[2]=r->infoptr[r->infonum].totalHeaderSize; 
    dp[3]=r->infoptr[r->infonum].totalSize; 
    dp[4]=r->infoptr[r->infonum].numSendPkt; 
    dp[5]=r->infoptr[r->infonum].totalSendHeaderSize; 
    dp[6]=r->infoptr[r->infonum].totalSendSize; 
    dp[7]=r->infoptr[r->infonum].numReceivePkt; 
    dp[8]=r->infoptr[r->infonum].totalReceiveHeaderSize; 
    dp[9]=r->infoptr[r->infonum].totalReceiveSize; 
    r->infoptr[r->infonum].bt_dfi = dfi_class(dp); 
    addIp(r->ipAddr1, r->infoptr[r->infonum].bt_dfi, r->infoptr[r->infonum].bt_dpi_packet); 
    addIp(r->ipAddr2, r->infoptr[r->infonum].bt_dfi, r->infoptr[r->infonum].bt_dpi_packet); 
if
 ((tcp->th_flags & TH_FIN) == TH_FIN) {   
// a flow ends 
      r->infonum++; 
    } 
  } 
else
 { 
    strcpy(n.ipAddr1, inet_ntoa(ip->ip_dst)); 
    strcpy(n.ipAddr2, inet_ntoa(ip->ip_src)); 
    n.port1=ntohs(tcp->th_dport); 
    n.port2=ntohs(tcp->th_sport); 
    r = bsearch(&n, nptr, count, 
sizeof
(flow), (
int
(*)(
const
void
*, 
const
void
*))flowCmp); 
if
 (r) { 
      r->numTPkt++; 
      r->infoptr[r->infonum].avgSize = ((r->infoptr[r->infonum].avgSize * r->infoptr[r-
>infonum].numPkt) + ntohs(ip->ip_len))/(r->infoptr[r->infonum].numPkt+1); 
      r->infoptr[r->infonum].numPkt++; 
      r->infoptr[r->infonum].totalHeaderSize += size_ip + size_tcp; 
      r->infoptr[r->infonum].totalSize += ntohs(ip->ip_len); 
      r->infoptr[r->infonum].numReceivePkt++; 
      r->infoptr[r->infonum].totalReceiveSize+=ntohs(ip->ip_len); 
      r->infoptr[r->infonum].totalReceiveHeaderSize+= size_ip + size_tcp; 
      dp[0]=r->infoptr[r->infonum].numPkt; 
      dp[1]=r->infoptr[r->infonum].avgSize; 
      dp[2]=r->infoptr[r->infonum].totalHeaderSize; 
      dp[3]=r->infoptr[r->infonum].totalSize; 
      dp[4]=r->infoptr[r->infonum].numSendPkt; 
      dp[5]=r->infoptr[r->infonum].totalSendHeaderSize; 
      dp[6]=r->infoptr[r->infonum].totalSendSize; 
      dp[7]=r->infoptr[r->infonum].numReceivePkt; 
      dp[8]=r->infoptr[r->infonum].totalReceiveHeaderSize; 
      dp[9]=r->infoptr[r->infonum].totalReceiveSize; 
      r->infoptr[r->infonum].bt_dfi = dfi_class(dp); 
      addIp(r->ipAddr1, r->infoptr[r->infonum].bt_dfi, r->infoptr[r->infonum].bt_dpi_packet); 
      addIp(r->ipAddr2, r->infoptr[r->infonum].bt_dfi, r->infoptr[r->infonum].bt_dpi_packet); 
if
 ((tcp->th_flags & TH_FIN) == TH_FIN) { 
// a flow ends 
        r->infonum++; 
      } 
    } 
else
 {  
// a new flow 
      addFlow(count, ip->ip_src ,tcp->th_sport ,ip->ip_dst, tcp->th_dport, size_ip + size_tcp, 
ntohs(ip->ip_len), 1); 
      count++; 
    } 
  } 
return
; 
} 
