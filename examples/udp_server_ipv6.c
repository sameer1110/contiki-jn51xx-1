#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "dev/uart0.h"

#include <string.h>

#define DEBUG DEBUG_PRINT
#include "net/uip-debug.h"

#define UIP_IP_BUF ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

#define MAX_PAYLOAD_LEN 120

static struct uip_udp_conn *server_conn,*server_conn1;

PROCESS(udp_server_process, "UDP server process");
AUTOSTART_PROCESSES(&udp_server_process);

static void
uip_handler(void)
{
  static int i;
   if(uip_newdata()) {
  // ((char *)uip_appdata)[uip_datalen()] = 0;
    for (i = 0; i < uip_datalen(); i++)
    {
      uart0_writeb(((uint8_t *)uip_appdata)[i]);

    }
 }
}

PROCESS_THREAD(udp_server_process, ev, data)
{
  
 // static struct etimer et;
  PROCESS_BEGIN();
  PROCESS_PAUSE();
  server_conn1=udp_broadcast_new(UIP_HTONS(10001),NULL);
  udp_bind(server_conn1, UIP_HTONS(10001));
  server_conn = udp_new(NULL,UIP_HTONS(10000), NULL);
  uip_udp_bind(server_conn, UIP_HTONS(10000));
   while(1)
  {
    PROCESS_YIELD_UNTIL(ev == tcpip_event);
    uip_handler();
  }
  PROCESS_END();
}



