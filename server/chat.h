#ifndef CHAT_H
#define CHAT_H

#include "headers.h"

struct Message {
public:
    Message(std::string sender, std::string data) : sender(sender), data(data) {}
    std::string sender;
    std::string data;
};

struct Chat {
public:
    Chat();
    static Chat* Instance();
    int addUser(std::string name);
    std::string getToken(std::string name);
    std::vector<std::string> getUsers();
    int disconnectUser(std::string);

    int addMessage(Message message);
    std::vector<Message> getMessages();
private:
    std::string generateToken(int length);
    std::map <std::string, std::string> users;
    std::vector <std::string> logins;
    std::vector <Message> messages;
};

#endif