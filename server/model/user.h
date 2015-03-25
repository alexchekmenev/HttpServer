#ifndef _HTTPSERVER_USER_H_
#define _HTTPSERVER_USER_H_

#include "../headers.h"


struct User {
public:
    User(const std::string& name);
    ~User();
    std::string to_json();
    std::string get_name() const;
private:
    std::string name;
};


#endif //_HTTPSERVER_USER_H_
