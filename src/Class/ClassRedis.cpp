#include "redis.h"
#include <cstddef>


Redis::Redis(){
	cout << "class redis Constructor" << endl;
};

// string Redis::SetMemory(string key,string value){
// 	return this->memory[key] = value;
// };

// string Redis::GetMemory(string key){
// 	string ret = this->memory[cmd.key];
// 	return this->memory[cmd.key];
// };

// string Redis::CmdParse(int src, string entry){
// 	s_redisCmd CmdParse;
// 	int state = 0;
// 	int i = 0;
// 	while (entry[i] != '\0') {
// 		if (entry[i] != ' ') {

// 			if (state == 0)
// 				CmdParse.cmd += entry[i];
// 			else if (state == 1)
// 				CmdParse.key += entry[i];

// 		} else if (state == 1){
// 			if (entry[i + 1] != '\0'){
// 				CmdParse.value = entry.substr(i + 1);
// 			}
// 			break;
// 		} else {
// 			state++;
// 		}
// 		i++;
// 	}
// 	// if (CmdParse.cmd == "GET"){
// 	// 	return this->GetMemory(CmdParse);
// 	// } else if (CmdParse.cmd == "SET"){
// 	// 	return this->SetMemory(CmdParse.key, CmdParse.value);
// 	// } else if (CmdParse.cmd == "SUBSCRIBE"){
// 	// 	return this->Subscribe(src, CmdParse);
// 	// } else if (CmdParse.cmd == "PUBLISH"){
// 	// 	return this->Publish(src, CmdParse);
// 	// }
// 	// else{
// 	// 	return "Command not found";
// 	// }

// 	return "Commande not found";
// };

// string Redis::Subscribe(int src, string key){
// 	if (this->publisher){
// 		this->listener[key].push_back(src);
// 		return ("ok");
// 	}
// 	return ("no publishHandler");
// }

// void Redis::setPublisher(void (*publisher)(int, int, string)){
// 	this->publisher = publisher;
// }

// string Redis::Publish(int src, s_redisCmd CmdParse){
// 	if (this->publisher){
// 		list<int>::iterator it = this->listener[CmdParse.key].begin();

// 		while (it != this->listener[CmdParse.key].end()){
// 			this->publisher(src, *it, CmdParse.value);
// 			it++;
// 		}
// 		return ("ok");
// 	}
// 	return ("no publishHandler");
// }

Redis::~Redis(){
	// cout << "class redis Destructor" << endl;
};
