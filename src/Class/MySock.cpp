#include "MySock.h"

using namespace std;

MySock::MySock(int port){

	int error = 0;
	//Inisialisation de la socket
	this->Socket =  socket(AF_INET, SOCK_STREAM, 0);
	if (this->Socket < 0)
		cout << "ERROR opening socket" << endl;
	//Copie du port dans la class
	this->Port = port;

	// Je parmettre la le bind Avec le port et le protocol tcp/ip
	this->Sock_in.sin_family = AF_INET;
	this->Sock_in.sin_addr.s_addr = INADDR_ANY;
	this->Sock_in.sin_port = htons(port);
	if (bind(this->Socket, (struct sockaddr *) &this->Sock_in, sizeof(this->Sock_in)) < 0)
		cout << "ERROR Binding" << endl;

	// je met la socket en attente de connection
	if ((error = listen(this->Socket,5)))
		cout << "error on listen" << endl;

	this->Read_lst.push_back(this->Socket);
	cout << "Socket Open port:" << port << endl;

	this->Max_fd= 0;

	this->tv.tv_sec = 5;
	this->tv.tv_usec = 0;

}

void MySock::init_Accept(){
	int client_len;
	struct	sockaddr_in	client_addr;
	s_SockCmd cmd;
	// renvoy un FD de reponce sur une nouvelle socket
	int Client_socket_fd = accept(this->Socket, (struct sockaddr *) &client_addr, (socklen_t *) &client_len);
	if (Client_socket_fd < 0)
		cout << "ERROR on accept" << endl;
	else
		printf("nouvelle utilisateur connecter Adress : %s FileDescriptor: %d\n", inet_ntoa(client_addr.sin_addr), Client_socket_fd);
		if (this->callback["onConnect"]){
			cmd.cmd = "connection";
			cmd.value = "connection";
			cmd.txt = "connection";
			cmd.src = Client_socket_fd;
			if (this->callback["onConnect"])
				this->callback["onConnect"](&cmd);
		}
		this->Read_lst.push_back(Client_socket_fd);
		this->connected[Client_socket_fd] = true;
		if (this->Max_fd < Client_socket_fd)
			this->Max_fd = Client_socket_fd;
};


void MySock::sendto(int client, std::string buffer){
	if (this->connected[client]){
		int ret = send(client, buffer.c_str(), buffer.length(), 0);
		if (ret < 0)
			cout << "SEND FAIL"<< endl;
	}
};

void MySock::init_fd(fd_set *to_set){
	list<int> lst;
	lst = this->Read_lst;
	FD_ZERO(to_set);
	list<int>::iterator it;
	it = lst.begin();
	while (it != lst.end()){
		FD_SET(*it, to_set);
		it++;
	}
}

/*
** DoSelect()
** it the function get if fd have write and have for time out this->tv
** if retval is == -1 select hav error
** if retval is == 0 select dont have file descriptore for read
** else select have a fd whith value
*/

void MySock::DoSelect(){
	fd_set Read_fds;
	int retval;

	this->init_fd(&Read_fds);

	retval = select(this->Max_fd + 1, &Read_fds, NULL, NULL, &this->tv);

	if (retval == -1)
		cout << "ERROR: Select()" << endl;
	else if (retval)
		this->checkFd(&Read_fds);

}
/*
** this function was called at any time if a select return if it not 0
** if the fd == Socket it was a client at this moment it Accept is called
*/
void MySock::checkFd(fd_set *Read){
	int ret;
	char buffer[4096];
	list<int>::iterator it;
	list<int> lst = this->Read_lst;

	it = lst.begin();
	while (it != lst.end()){
		if (FD_ISSET(*it, Read) && *it != this->Socket){
			ret = recv(*it, &buffer, 4096, 0);
			if (ret == 0)
				this->disconect_client(*it);
			else{
				buffer[ret]= '\0';
				this->Read_buff[*it] += buffer;
				this->execCmd(*it);
			}
		} else if (FD_ISSET(*it, Read) && *it == this->Socket){
			this->init_Accept();
		}
		it++;
	}
}

void MySock::execCmd(int Client){
	int nextl = Read_buff[Client].find_first_of('\n');
	while (nextl >= 0){
		s_SockCmd Cmd;
		Cmd.src = Client;
		Cmd.txt = this->Read_buff[Client].substr(0,nextl);
		cout << Cmd.txt << endl;
		this->CmdParse(&Cmd);
		if (this->callback[Cmd.cmd])
			this->callback[Cmd.cmd](&Cmd);
		else if (Cmd.cmd == "PUBLISH")
			this->Publish(&Cmd);
		else if (Cmd.cmd == "SUBSCRIBE")
			this->Subscribe(&Cmd);
		else
			this->sendto(Cmd.src, "Command not found\n");
		if (this->callback["recv"])
			this->callback[Cmd.cmd](&Cmd);

		this->Read_buff[Client] = this->Read_buff[Client].substr(nextl + 1);
		nextl = this->Read_buff[Client].find_first_of('\n');
	}

}

void MySock::on(string event, void (*fnc)(s_SockCmd *)){
	this->callback[event] = fnc;
}
/*
** loop est a appeler pour lancer la lecture des socket
** un premier accept est lancer pour initialiser le listener de la soket
*/
void MySock::loop(){
	this->init_Accept();
	while (1){
		this->DoSelect();
	}
};

/*
** la fomction est appeler lors d'un retour de 0 a la lecture des fd
*/
void MySock::disconect_client(int client){
	s_SockCmd cmd;
	cmd.cmd = "disconect";
	cmd.value = "disconect";
	cmd.txt = "disconect";
	cmd.src = client;
	// this->Max_fd = getMax();
	Read_lst.remove(client);

	this->connected[client] = false;
	close(client);
	if (this->callback["onDisconnect"])
		this->callback["onDisconnect"](&cmd);
}

void MySock::CmdParse(s_SockCmd *CmdParse){
	string entry = CmdParse->txt;
	int state = 0;
	int i = 0;
	while (entry[i] != '\0') {
		if (entry[i] != ' ') {
			if (state == 0)
				CmdParse->cmd += entry[i];
			else if (state == 1)
				CmdParse->key += entry[i];
		} else if (state == 1){
			if (entry[i + 1] != '\0'){
				CmdParse->value = entry.substr(i + 1);
			}
			break;
		} else {
			state++;
		}
		i++;
	}

}
void MySock::broadcast(string msg){
	list<int>::iterator it = this->Read_lst.begin();

	while (it != this->Read_lst.end()){
		this->emit(*it, msg);
		it++;
	}
};
void MySock::Publish(s_SockCmd *Cmd){
	list<int>::iterator it = this->listener[Cmd->key].begin();
	Cmd->value += '\n';
	while (it != this->listener[Cmd->key].end()){
		if (*it != Cmd->src)
			this->sendto(*it, Cmd->value);
		it++;
	}
	this->sendto(Cmd->src,"ok\n");
}

void MySock::Subscribe(s_SockCmd *cmd){
	this->listener[cmd->key].push_back(cmd->src);
	this->sendto(cmd->src,"ok\n");

}

void MySock::emit(string channel, string msg){
	s_SockCmd toSent;
	toSent.key = channel;
	toSent.src = 0;
	toSent.value = msg;
	this->Publish(&toSent);
}

void MySock::emit(int to, string msg){
	this->sendto(to, msg);
}

MySock::~MySock(){};