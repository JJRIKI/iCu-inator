#include <sys/time.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#define CMD "netsh wlan show interfaces  | grep BSSID | awk '{print $3}' | tr -d ':\r'" //add more stuff to get the name of the ap from the BSSID
#define pilot "https://pilot.westmont.edu:28900?i=jbek&uptime=60"
/*
#define bssids_LINE "awk '/3485840e36d5/{print NR, $1}' bssids.txt"
#define bssids_LINE "awk '/netsh wlan show interfaces  | grep BSSID | awk '{print $3}' | tr -d ':\r' |3485840e36d5/{print NR, $1}' bssids.txt"
*/
/*
int get_AP_from_BSSID_FILE() {

	char ap[];
	char returnAP[];
	memset(returnAP, '\0', sizeof(ap));

	FILE * bssid = fopen("bssids.txt" "r");
	FILE * mycmd = popen(CMD, "r");
	char buf[250];
	fgets(buf, sizeof(buf), mycmd);
	pclose(mycmd);

	while(fgets(ap, 100, bssid)) {
		if(strcmp(buf, ap)) {
			strcpy(returnAP, ap);
		}
		memset(ap, '\0', sizeof(ap));
	}

	return returnAP;
}
*/

/*
char * BSSID(char *buffer, char *symb) {
    int i = 0;
    char *p = strtok(buffer, (const char *__restrict) symb);
    char *array[3];
    while (p != NULL) {
        array[i++] = p;
        p = strtok (NULL, (const char *__restrict) symb);
    }

    printf("%s\n", array[1]);
    return *array;
}
*/

int main () {
	FILE * mycmd = popen(CMD, "r");
	char buf[250];

	fgets(buf, sizeof(buf), mycmd);
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

/*
	char *symb1 = " ";
	char *symb2 = ".";
	char *symb3 = "-";
	char * array = BSSID(buf2, symb1);
	char * array2 = BSSID(array, symb2);
	char * array3 = BSSID(array2, symb3);
*/
    char name[100] = "Blake ";
    char array4[10];
    strtok(array4, "\n");
    strcat(array4, array3[1]);
    strtok(array4, "\n");
    strcat(array4, "-");
	strtok(array4, "\n");    
    strcat(array4, array3[2]);
    printf("%s\n", array4);

    strcat(name, array4);
    printf("%s\n", name);
	pclose(mycmd2);

	return 0;
}