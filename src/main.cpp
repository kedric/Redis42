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
	lilo.sendto(fd, "lol" + '\n');
}

int main(){


	string a;

	// lol.SetMemory("salut", "sava");

	// cout << lol.CmdParse("get salut") << endl;

	// cout <<  lol.CmdParse("SET hello Comment tu va" ) << endl;
	// cout <<  lol.CmdParse("SET hell Comme65456545654nt tu v" ) << endl;
	// cout <<  lol.CmdParse("SET helo Codsadasdadasdadmment  va" ) << endl;
	// cout <<  lol.CmdParse("SET hlo Comment tu " ) << endl;


	// cout <<  lol.CmdParse("GET hello" ) << endl;
	// cout <<  lol.CmdParse("GET hell" ) << endl;
	// cout <<  lol.CmdParse("GET helo" ) << endl;
	// cout <<  lol.CmdParse("GET hlo" ) << endl;

	// lol.setPublisher (publishHandler);
	lilo.on("onConnect", helloworld);
	lilo.on("onDisconnect", helloworld);
	lilo.on("recv", recvdata);
	// lilo.on("GET", )

	lilo.loop();

	return(0);

}


