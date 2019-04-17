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
#include <sys/signal.h>

#define port 28900

#define CMD "netsh wlan show interfaces  | grep BSSID | awk '{print $3}' | tr -d ':\r'"


char * getAP(char * name);
void timer();


 int main(int argc, char * argv[]) {

    char * name[100];
 	char * AP = getAP(name);
	printf("%s\n",AP);

 	pthread_t report;
	pthread_create(&report, NULL, timer, 0);
	pthread_join(report, NULL);
	return 0;
}


 char * getAP(char * name) {
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


 void timer() {
	char web[100] = "GET /?i=jbek&uptime=60 HTTP/1.0\r\n\r\n";

 	int i = 0;
	do {

 		int sockpilot, ret;
		struct sockaddr_in serverpilot;

 		sockpilot = socket(AF_INET, SOCK_STREAM, 0);

 		inet_pton(AF_INET, (char *) "10.115.20.250", &serverpilot.sin_addr);
		serverpilot.sin_family = AF_INET;
		serverpilot.sin_port = htons(port);

 		ret = connect(sockpilot, (const struct sockaddr *)&serverpilot, sizeof(serverpilot));
		i++;

 		write(sockpilot, web, strlen(web));

 		sleep(60);

 	} while(1);

 } 