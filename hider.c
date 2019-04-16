#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <sys/signal.h>

#define PORT 28900
#define SIZE 512

#define CMD "netsh wlan show interfaces  | grep BSSID | awk '{print $3}' | tr -d ':\r'"
//#define pilot "https://pilot.westmont.edu:28900?i=jbek&uptime=60"
//GET "/?who are you HTTP/1.0\r\\n\r\n"

char * getAP();
void timer();
void victim();
int obtain_socket();
void show_message(int sd);
void close_down(int sigtype);
int ssockfd;

char * getAP(char * name);
void timer();


int main(int argc, char * argv[]) {

	char name[100];
	char * AP = getAP(name);
	//printf("%s\n", AP);

	pthread_t die;
	pthread_create(&die, NULL, victim, AP);
	pthread_join(die, NULL);

	pthread_t report;
	pthread_create(&report, NULL, timer, 0);
	pthread_join(report, NULL);

	return 0;
}


char * getAP( char * name) {
	FILE * mycmd = popen(CMD, "r");	
	char buf[250];

	fgets(buf, sizeof(buf), mycmd);
	pclose(mycmd);

	char foo[250] = "awk '/";
	strcat(foo, buf);
	strtok(foo, "\n");
	strcat(foo, "/{print NR, $1}' bssids.txt");

	FILE * mycmd2 = popen(foo, "r");
	char buf2[250];

	fgets(buf2, sizeof(buf2), mycmd2);
	pclose(mycmd2);

	int i = 0;
    char *p = strtok (buf2, " ");
    char *array[3];
    while (p != NULL) {
        array[i++] = p;
        p = strtok (NULL, " ");
    }

    int j = 0;
    char *q = strtok (array[1], ".");
    char *array2[3];
    while (q != NULL) {
        array2[j++] = q;
        q = strtok (NULL, ".");
    }
	
	char *array3;
	strcpy(name, "Dempsey "); //here
	strcpy(array3, array2[1]);

    strtok(array3, "\n");    
    strcat(name, array3);

    return name;  
}

void victim(char * AP){

int sd, client_len;
  struct sockaddr_in client;
  


  signal(SIGINT, close_down);    /* use close_down() to terminate */

  printf("Listen starting on port %d\n", PORT);
  ssockfd = obtain_socket();
  while(1) {
    client_len = sizeof(client);
    sd = accept(ssockfd, (struct sockaddr *) &client, &client_len);
      
    printf("%s\n", AP);

    send(sd, AP, sizeof(AP), 0);
    
    show_message(sd);

    //send(sd, "Blake", sizeof("Blake"), 0);


    close(sd);
  }
}

void timer() {
	char web[100] = "GET /?i=jbek&uptime=60 HTTP/1.0\r\n\r\n";

	int i = 0;
	do {

		int sockpilot, ret;
		struct sockaddr_in serverpilot;

		sockpilot = socket(AF_INET, SOCK_STREAM, 0);

		inet_pton(AF_INET, (char *) "10.115.20.250", &serverpilot.sin_addr);
		serverpilot.sin_family = AF_INET;
		serverpilot.sin_port = htons(PORT);

		ret = connect(sockpilot, (const struct sockaddr *)&serverpilot, sizeof(serverpilot));
		i++;

		write(sockpilot, web, strlen(web));

		sleep(60);

	} while(1);

}

int obtain_socket(){
  int sockfd;
  struct sockaddr_in serv_addr;

  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

 
  (char *)&serv_addr, sizeof(serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(PORT);

  
  bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  
  listen(sockfd, 5);
  
  return(sockfd);
}


void show_message(int sd)

{
  char buf[SIZE];
  char whoAreU[512] = "Who are you?\n";

  int no;

  while ((no = read(sd, buf, SIZE)) > 0)
    write(1, buf, no);      
  
}
void close_down(int sigtype)
/* Close socket connection to PORT when ctrl-C is typed */
{
  close(ssockfd);
  printf("Listen terminated\n");
}