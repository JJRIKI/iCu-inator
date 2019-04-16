
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


// helper to access cmd line and hopefully use bssid list to grab current wap info

FILE *grabWap = popen(CMD, "r");

///System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport | grep BSSID | awk '{print $2}''

char buf[256];

fgets(buf, sizeof(buf), grabWap);

pclose(grabWap);

