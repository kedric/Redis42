
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <list>
#include <sys/select.h>
#include <map>
#include <unistd.h>

struct	s_SockCmd{
	std::string cmd;
	std::string key;
	std::string value;
	std::string txt;
	int			src;
};

class MySock
{
public:
	MySock(int port);
	~MySock();
	void	init_Accept();
	void	loop();
	void	sendto(int client, std::string buffer);
	void	DoSelect();
	void	init_fd(fd_set *to_set);
	void	checkFd(fd_set *to_check);
	void	on(std::string, void (*)(s_SockCmd *));
	void	disconect_client(int client);
	void	execCmd(int Client);
	void	Subscribe(s_SockCmd *cmd);
	void	Publish(s_SockCmd *Cmd);
	void	CmdParse(s_SockCmd *cmd);
	void	emit(std::string, std::string);
	void	emit(int to, std::string msg);
	void	broadcast(std::string msg);
private:
	int												Socket;
	int												Port;
	struct											sockaddr_in	Sock_in;
	std::list<int>									Read_lst;
	std::map<int, std::string>						Read_buff;
	std::map<int, bool>								connected;
	std::map<std::string, void(*)(s_SockCmd *)>	callback;
	int												Max_fd;
	struct timeval									tv;
	std::map<std::string,std::list<int> >			listener;

};