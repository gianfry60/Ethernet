#ifndef ethernet_h
#define ethernet_h

#include <inttypes.h>
//#include "w5100.h"
#include "IPAddress.h"
#include "EthernetClient.h"
#include "EthernetServer.h"
#include "Dhcp.h"

#define MAX_SOCK_NUM 4

enum EthernetLinkStatus {
  Unknown,
  LinkON,
  LinkOFF
};

class EthernetClass {
public:
  static uint8_t _state[MAX_SOCK_NUM];
  static uint16_t _server_port[MAX_SOCK_NUM];
  // Initialise the Ethernet shield to use the provided MAC address and gain the rest of the
  // configuration through DHCP.
  // Returns 0 if the DHCP configuration failed, and 1 if it succeeded
  int begin(uint8_t *mac_address, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);
  void begin(uint8_t *mac_address, IPAddress local_ip);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);
  void init(uint8_t sspin = 10);
  int maintain();

  EthernetLinkStatus linkStatus();

  void MACAddress(uint8_t *mac_address);
  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  IPAddress dnsServerIP();

  void setMACAddress(const uint8_t *mac_address);
  void setLocalIP(const IPAddress local_ip);
  void setSubnetMask(const IPAddress subnet);
  void setGatewayIP(const IPAddress gateway);
  void setDnsServerIP(const IPAddress dns_server);

  friend class EthernetClient;
  friend class EthernetServer;

private:
  IPAddress _dnsServerAddress;
  DhcpClass* _dhcp;
  bool _W5100initialized = false;
};

extern EthernetClass Ethernet;

#endif
