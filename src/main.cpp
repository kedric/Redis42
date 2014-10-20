#include "MySock.h"
#include <cstdio>
#include <unistd.h>

MySock Sock = MySock(12342);
std::map<std::string, std::string> memory;


void helloworld(s_SockCmd *cmd){
	std::cout << cmd->txt << std::endl;
}

void getvalue(s_SockCmd *cmd){
	std::cout << cmd->txt << std::endl;
	Sock.emit(cmd->src, memory[cmd->key]+ '\n');
}

void setvalue(s_SockCmd *cmd){
	std::cout << cmd->value << std::endl;
	memory[cmd->key] = cmd->value;
	Sock.emit(cmd->src, "+OK\r\n");
}

int main(){
	Sock.on("onConnect", helloworld);
	Sock.on("onDisconnect", helloworld);
	Sock.on("GET", getvalue);
	Sock.on("SET", setvalue);
	Sock.on("recv", helloworld);
	Sock.loop();

	return(0);

}


