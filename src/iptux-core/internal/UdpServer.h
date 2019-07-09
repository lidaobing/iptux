#ifndef IPTUX_UDP_SERVER_H
#define IPTUX_UDP_SERVER_H

#include <string>

namespace iptux {

class UdpService {
 public:
  UdpService(const std::string& ip, int port, void* callback);
  ~UdpService();

  void start();
  void stop();

  [[deprecated]]
  int getUdpSock();

  void sendMessage(const std::string& ip, int port, const std::string& message);
 private:
  struct Impl;
  std::unique_ptr<Impl> pImpl;
};

}


#endif
