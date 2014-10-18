#include "redis.h"
#include "MySock.h"
#include <cstdio>
#include <unistd.h>

MySock lilo = MySock(12341);
Redis lol = Redis();


void publishHandler(int src, int fd, string msg){
	if (src != fd)
		lilo.sendto(fd, msg + '\n');
}

void helloworld(int fd, string msg){
	cout << msg << endl;
}

void recvdata(int fd, string msg){
	// cout << msg;
	cout << msg << endl;
	lilo.sendto(fd, "lol\n");
}

int main(){


	string a;

	lilo.on("onConnect", helloworld);
	lilo.on("onDisconnect", helloworld);

	lilo.loop();

	return(0);

}


