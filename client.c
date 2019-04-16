#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/unistd.h>


//#define PORT_NUM 28900
int getWords(char *base, char *target[10][20]) {

	printf(base);

	int n = 0, i, j = 0;
	for(i = 0; 1; i++) {
		printf("GUCK\n");
		if(base[i]!= ' ') {
			target[n][j++] = base[i];
		}
		else {
			target[n][j++] = '\0';
			n++;
			j=0;
		}
		printf("GUCK2\n");
		if(base[i] == '\0') {
			break;
		}
	}
	return n;
}


void *report(char who) {

	int sockpilot, ret;
	struct hostent * pilot_address = gethostbyname("pilot.westmont.edu");
	struct sockaddr_in serverpilot;

    
    sockpilot = socket(AF_INET, SOCK_STREAM, 0);
    
    
    inet_pton(AF_INET, (char *) "10.115.20.250", &serverpilot.sin_addr);
    
    
    serverpilot.sin_family = AF_INET;
    serverpilot.sin_port = htons(28900);
	
    /*
    char * token = strtok(who, " ");
    char * array[2];
    int i = 0;
	printf(who);
    while (token != NULL) {
    	array[i++] = token;
    	token = strtok(NULL, " ");

    }
	
	*/
	connect(sockpilot, (const struct sockaddr *) &serverpilot, sizeof(serverpilot));
	int i;
	char array[10][20];
	printf(who);
	int b = getWords(who, array);
	char foo[] = "GET /?i=jbek&u=";
	char bar[] = "&where=";
	strcat(foo, array[0]);
	strcat(bar, array[1]);
	strcat(foo, bar);
	strcat(foo, "HTTP/1.0\r\n\r\n");
	write(sockpilot, foo, strlen(foo)); //stuff here

}

void *attacker(int PORT_NUM) {
	char IP_ADDRESS[100];
	//int PORT_NUM = 28900;
	char who[25];
	char hello[25] = "Who are you?\n";

	int sockfd, ret;
    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    FILE* fp = fopen("test.txt", "r");
    
    while(1) {	
    	
    	while(fgets(IP_ADDRESS, 100, fp)) {

    		printf(IP_ADDRESS);

    		inet_pton(AF_INET, IP_ADDRESS, &server.sin_addr);
    		server.sin_family = AF_INET;
    		server.sin_port = htons(28900);

/*
    		printf("test#1\n");

    		connect(sockfd, (const struct sockaddr *)&server, sizeof(server));
    		printf("test#2\n");
    		send(sockfd, hello, sizeof(hello), 0);
    		recv(sockfd, who, sizeof(who), 0);
    		printf(who);
    		report(who);
*/

    		if(ret = connect(sockfd, (const struct sockaddr *) &server, sizeof(server)) == -1) {
    			printf("Not Connected to: %d\n", IP_ADDRESS);
			}
			else {
				send(sockfd, hello, sizeof(hello), 0);
				recv(sockfd, who, sizeof(who), 0);
				report(who);

				memset(who, '\0', sizeof(who));	
			}
			memset(IP_ADDRESS, '\0', sizeof(IP_ADDRESS));
			close(sockfd);
		}
	}
}

int main(int argc, char *argv[]) {
	/*
	char var22313 = "rodkey vostro";
	report(var22313);
	*/

	printf("Hi\n");
	//int PORT_NUM = 28900;
	printf("Hello1\n");
    pthread_t search;
    pthread_t report;
    printf("Hello2\n");
    pthread_create(&search, NULL, attacker, 28900);
    //pthread_create(&report, NULL, report, 0);
    pthread_join(search, NULL);
    //pthread_join(report, NULL);

    return 0;
}