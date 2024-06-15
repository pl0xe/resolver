#include "resolver.h"

int main() {

  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;
  int port = 4444;
  char ipstr[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // IP v4/v6 agnostic
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo("google.com", NULL, &hints, &servinfo);

  if ( status != 0 ) {
    fprintf(stderr, "[!] getaddrinfo error : %s\n", gai_strerror(status));
    exit(1);
  }
  
  struct addrinfo *info;
  for (info = servinfo; info != NULL; info = info->ai_next) {
    void *addr;
    char *ipver;

    if (info->ai_family == AF_INET) {
      // handles IPv4 Addressing
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)info->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else {
      // handles IPv6 Addressing
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)info->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    // convert IP to string
    inet_ntop(info->ai_family, addr, ipstr, sizeof ipstr);
    printf("\t%s: %s\n", ipver, ipstr);
  }

  freeaddrinfo(servinfo);

  return 0;
}





