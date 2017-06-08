#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512

void diep(char *s)
  {
    perror(s);
    exit(1);
  }

int main(int argc, char *argv[])
{
printf("____________________\n");
printf("|                   |\n");
printf("| Simple UDP Client |\n");
printf("|     © 2017 by     |\n");
printf("|  Mike Gazzaruso   |\n");
printf("|___________________|\n\n");
  if (argc != 4)
  {
    printf("Utilizzo: %s <IP_SERVER> <IP_PORT> <MESSAGE>\n", argv[0]);
    printf("MESSAGE must be MAX %i bytes\n\n", BUFLEN);
    exit(1);
  }
  struct sockaddr_in si_other;
  int s, i, slen=sizeof(si_other);
  char buf[BUFLEN];
  memset(buf, '\0', sizeof(char)*BUFLEN );

  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    diep("socket");

  memset((char *) &si_other, 0, sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(strtol(argv[2], NULL, 10));
  if (inet_aton(argv[1], &si_other.sin_addr)==0)
  {
    fprintf(stderr, "inet_aton() failed\n");
    exit(1);
  }

    printf("Sending packet \"%s\"\n", argv[3]);
    sprintf(buf, "%s", argv[3]);
    if (sendto(s, buf, BUFLEN, 0, &si_other, slen)==-1)
      diep("sendto()");

  close(s);
  return 0;
}

