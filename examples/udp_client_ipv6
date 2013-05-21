#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "dev/uart0.h"
#include <AppHardwareApi.h>
#include <string.h>


#define DEBUG DEBUG_PRINT
#include "net/uip-debug.h"

#define MAX_PAYLOAD_LEN 40

#define UIP_IP_BUF ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

static struct uip_udp_conn *client_conn,*client_conn1;
static unsigned char ch;
static unsigned char null_buff[50]={0};
static unsigned char *buff=&null_buff;
static int count=0;
/*---------------------------------------------------------------------------*/
PROCESS(udp_client_process, "UDP client process");
AUTOSTART_PROCESSES(&udp_client_process);
/*---------------------------------------------------------------------------*/
int copy_uart0_data(unsigned char c)
{
*buff=c;
ch=*buff;
count++;
process_poll(&udp_client_process);
return 1;

}
/*------------------------------------------------------------------*/
PROCESS_THREAD(udp_client_process, ev, data)
{
  PROCESS_BEGIN();
  PRINTF("UDP client process started\n");
  
  PROCESS_PAUSE();

  client_conn1 = udp_new(NULL,UIP_HTONS(10001), NULL);
  udp_bind(client_conn1, UIP_HTONS(10001));
  client_conn = udp_broadcast_new(UIP_HTONS(10000), NULL);
  udp_bind(client_conn, UIP_HTONS(10000));

  uart0_set_input(copy_uart0_data);
  
while(1) {

       PROCESS_YIELD_UNTIL(ev == PROCESS_EVENT_POLL);
// if(sizeof(buff)!=50){
//count=50;
uip_udp_packet_send(client_conn,&ch,1);
//printf("%s",(char *)*buff);
//static unsigned char null_buff[50]={0};
//buff=&null_buff;
printf("\nCount : %d",count);

  }
  PROCESS_END();
}
