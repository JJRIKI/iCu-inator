#include <stdio.h>
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
#define CMD "netsh wlan show interfaces  | grep BSSID | awk '{print $3}' | tr -d ':\r'" //add more stuff to get the name of the ap from the BSSID
#define pilot "https://pilot.westmont.edu:28900?i=jbek&uptime=60"

int ssockfd;     /* socket for PORT; global for close_down() */

int main()
{
    FILE * mycmd = popen(CMD, "r");
    char buf[250];

    fgets(buf, size   of(buf), mycmd);
    //printf(buf);
    pclose(mycmd);

    char foo[250] = "awk '/";
    strcat(foo, buf);
    strtok(foo, "\n");
    strcat(foo, "/{print NR, $1}' bssids.txt");
    //printf("%s\n", foo);

    FILE * mycmd2 = popen(foo, "r");
    char buf2[250];

    fgets(buf2, sizeof(buf2), mycmd2);

    int i = 0;
    char *p = strtok (buf2, " ");
    char *array[3];
    while (p != NULL) {
        array[i++] = p;
        p = strtok (NULL, " ");
    }
    //printf("%s\n", array[1]);

    int j = 0;
    char *q = strtok (array[1], ".");
    char *array2[3];
    while (q != NULL) {
        array2[j++] = q;
        q = strtok (NULL, ".");
    }
    //printf("%s\n", array2[1]);


    int k = 0;
    char *r = strtok (array2[1], "-");
    char *array3[3];
    while (r != NULL) {
      array3[k++] = r;
      r = strtok (NULL, "-");
    }
    char array4[10];
    strtok(array4, "\n");
    strcat(array4, array3[1]);
    strtok(array4, "\n");
    strcat(array4, "-");
    strtok(array4, "\n");    
    strcat(array4, array3[2]);
    printf("%s\n", array4);

    pclose(mycmd2);


    char buf [500];
    int sd, client_len;
    struct sockaddr_in client;

    signal(SIGINT, close_down);    /* use close_down() to terminate */

    printf("Listen starting on port %d\n", PORT);
    ssockfd = obtain_socket(PORT);
    while(1) {
        client_len = sizeof(client);
        sd = accept(ssockfd, (struct sockaddr *) &client, &client_len);
    /*
    recv(ssockfd,  buf, sizeof(buf), 0);
    if(strcmp(buf, "Who are you?\n")){
      printf("YO");
      continue;
    
    }
    else {
      printf("HERE\n");
      send(sd, "Blake", sizeof("Blake"), 0);
    }

    */

    printf("BOOFED\n");

    char boof[SIZE];
    int no;

    while ((no = read(sd, boof, SIZE)) > 0){
        continue;
        printf("BOOFED\n");

    }

    printf(boof);
    

    show_message(sd);


    char name[100] = "Blake ";
    strcat(name, array4);
    send(sd, name, sizeof(name), 0); //send the bssid
    
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
  bzero((char *)&serv_addr, sizeof(serv_addr));
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
  int no;

  while ((no = read(sd, buf, SIZE)) > 0)
    write(1, buf, no);    /* write to stdout */
}


void close_down(int sigtype)
/* Close socket connection to PORT when ctrl-C is typed */
{
  close(ssockfd);
  printf("Listen terminated\n");
  exit(0);
}