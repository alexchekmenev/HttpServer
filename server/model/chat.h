#ifndef CHAT_H
#define CHAT_H

#include "../headers.h"
#include "message.h"
#include "user.h"

struct Chat {
public:
    Chat();
    ~Chat();
    int add_user(const User& user);
    User get_user_by_id(const int id);
    int get_user_id_by_token(const std::string& token);
    std::string get_token(const User& user);
    std::vector<User> get_users();
    int disconnect_user(const User& user);

    int add_message(const Message& message);
    std::vector<Message> get_messages();
private:
    std::string generate_token(int length);

    std::map <std::string, int> users;
    std::map <std::string, int> ids;

    std::vector <std::string> logins;
    std::vector <std::string> tokens;
    std::vector <Message> messages;

    int max_id;
};

#endif