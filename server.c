#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
      
#include <unistd.h>           /* read(), write(), close() */
#include <errno.h>
#include <sys/signal.h>

int obtain_socket(int port);
void show_message(int sd);
void close_down(int sigtype);


#define PORT 28900          /* default port for server */
#define SIZE 512           /* max length of character string */
#define CMD 'grabWap'




int ssockfd;     /* socket for PORT; global for close_down() */
char userid[20];

int main()
{
  int sd, client_len;
  struct sockaddr_in client;
  

  printf("Enter UserID: \n");
  scanf("%s", userid); 

  signal(SIGINT, close_down);    /* use close_down() to terminate */

  printf("Started listening on port %d\n", PORT);
  ssockfd = obtain_socket(PORT);
  while(1) {
    client_len = sizeof(client);
    sd = accept(ssockfd, (struct sockaddr *) &client, &client_len);
      
    send(sd, "Blake", sizeof("Blake"), 0);
    
    show_message(sd);

    //send(sd, "Blake", sizeof("Blake"), 0);


    close(sd);
  }
  return 0;
}


int obtain_socket(int port)
/* Perform the first four steps of creating a server:
   create a socket, initialise the address data structure,
   bind the address to the socket, and wait for connections. 
*/
{
  int sockfd;
  struct sockaddr_in serv_addr;

  /* open a TCP socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  /* initialise socket address */
  (char *)&serv_addr, sizeof(serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);

  /* bind socket to address */
  bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  /* set socket to listen for incoming connections */
  /* allow a queue of 5 */
  listen(sockfd, 5);
  
  return(sockfd);
}




void show_message(int sd)
/* Print the incoming text to stdout */
{
  char buf[SIZE];
  char whoAreU[512] = "Who are you?\n";

  int no;

  while ((no = read(sd, buf, SIZE)) > 0)
    write(1, buf, no);    /* write to stdout */




  if (whoAreU == buf){
    //printf("TODO: implement name of access point/switch to which you are currently directly attached");
      
    // helper to access cmd line and hopefully use bssid list to grab current wap info

      char* bssids = "bssids.txt";
      char *ssockfd = ssockfd;
      int i = 0;
      
      FILE *grabWap = popen("/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport | grep BSSID | awk '{print $2}''", "r");
      fgets(buf, sizeof(buf), grabWap);

      grabWap = fopen(bssids, "r");
      if (grabWap == NULL){
        printf("Could not access bssids", bssids);

        fclose(bssids);
        
      }

      while(bssids[i]) {
          if(strcmp(bssids[i], ssockfd) == 0) {
              printf("Here is the name of the WAP!\n");
              break;
           }
           i++;
      }

      pclose(grabWap);

      printf("%s \n", userid);
  }
}


void close_down(int sigtype)
/* Close socket connection to PORT when ctrl-C is typed and exits to shell */
{

  printf("Stopped listening\n");
  close(ssockfd);
  exit(0);

}