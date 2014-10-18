#ifndef REDIS_H
#define REDIS_H

#include <iostream>
#include <map>
#include <list>

using namespace std;

struct	s_redisCmd{
	string cmd;
	string key;
	string value;
};

class Redis {
private:
	map<string,string> memory;
	map<string, string (*)(struct s_redisCmd)> callback;
	map<string,list<int> > listener;
	void (*publisher)(int, int, string);
protected:

public:
	Redis();
	// string SetMemory(string, string);
	// string GetMemory(struct s_redisCmd);
	// string CmdParse(int src, string entry);
	// string Subscribe(int src, s_redisCmd CmdParse);
	// string Publish(int src, s_redisCmd CmdParse);
	// void setPublisher(void (*publisher)(int, int, string));
	~Redis();
};

#endif
