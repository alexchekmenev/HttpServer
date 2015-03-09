#include "chat.h"

Chat::Chat() {}
Chat* Chat::Instance() {
    static Chat chat;
    return &chat;
}

int Chat::addUser(std::string name) {
    if (users[name].empty()) {
        std::string token = this->generateToken(16);
        users[name] = token;
        logins.push_back(name);
        return 0;
    }
    return -1;
}
std::string Chat::getToken(std::string name) {
    if (users.find(name) != users.end()) {
        return users.at(name);
    }
    return "";
}
std::vector<std::string> Chat::getUsers() {
    std::vector<std::string> res;
    for(int i = 0; i < (int)this->logins.size(); i++) {
        std::string token = users.at(this->logins[i]);
        if (!token.empty()) {
            res.push_back(this->logins[i]);
        }
    }
    return res;
}
int Chat::disconnectUser(std::string name) {
    this->users.erase(this->users.find(name));
    return 0;
}

int Chat::addMessage(Message message) {
    this->messages.push_back(message);
}
std::vector<Message> Chat::getMessages() {
    return this->messages;
}

std::string Chat::generateToken(int length) {
    srand(26);
    std::string token = "";
    for (int i = 0; i < length; i++) {
        int id = rand() % 36;
        if (id < 26) {
            token += char('a' + id);
        } else {
            token += char('0' + (id - 26));
        }
    }
    return token;
}