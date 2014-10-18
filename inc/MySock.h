
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <list>
#include <sys/select.h>
#include <map>
#include <unistd.h>

struct	s_cmd{
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
	void	init_fd(fd_set *to_set, fd_set *Write);
	void	checkFd(fd_set *to_check);
	void	on(std::string, void (*)(int, std::string));
	void	disconect_client(int client);
	void	execCmd(int Client);
	void	Subscribe(s_cmd *cmd);
	void	Publish(s_cmd *Cmd);
	s_cmd	CmdParse(s_cmd *cmd);
private:
	int												Socket;
	int												Port;
	struct											sockaddr_in	Sock_in;
	std::list<int>									Read_lst;
	// std::list<int>									Write_lst;
	std::map<int, std::string>						Read_buff;
	std::map<int, bool>								connected;
	std::map<std::string, void(*)(int,std::string)>	callback;
	int												Max_fd;
	struct timeval									tv;
	std::map<std::string,std::list<int> >			listener;

};