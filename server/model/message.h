#ifndef _HTTPSERVER_MESSAGE_H_
#define _HTTPSERVER_MESSAGE_H_

#include "../headers.h"

struct Message {
public:
    Message(const std::string& sender, const std::string& data);
    ~Message();
    std::string to_json();
private:
    std::string sender;
    std::string data;
};


#endif //_HTTPSERVER_MESSAGE_H_
