#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/unistd.h>
#include <netdb.h>


int main() {

	char web[100] = "GET /?i=jbek&uptime=60 HTTP/1.0\r\n\r\n"; //ask about this?
	int port = 28900;

	int i = 0;
	do {

		int sockpilot, ret;
		struct hostent * pilot_address = gethostbyname("pilot.westmont.edu");
		struct sockaddr_in serverpilot;

    	sockpilot = socket(AF_INET, SOCK_STREAM, 0);
    	printf("pilot address points to: %s\n", pilot_address->h_addr_list[0]);
    	// inet_pton(AF_INET, pilot_address->h_addr_list[0], &serverpilot.sin_addr);
    	inet_pton(AF_INET, (char *) "10.115.20.250", &serverpilot.sin_addr);
    	serverpilot.sin_family = AF_INET;
    	serverpilot.sin_port = htons(28900);

		if((ret = connect(sockpilot, (const struct sockaddr *)&serverpilot, sizeof(serverpilot))) == 0) {
			printf("connected\n");
		}
		i++;
		printf("%d\n", i);
		write(sockpilot, web, strlen(web)); //stuff here

		sleep(60);

	} while(1);

	return 0;
}