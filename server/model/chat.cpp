#include "chat.h"

using namespace std;

Chat::Chat() : max_id(1) {
    srand(26);
}
Chat::~Chat() {}


int Chat::add_user(const User& user) {
    string name = user.get_name();
    int id = users[name];
    if (id == 0) {
        std::string token = generate_token(8);
        ids[token] = max_id;
        cout << "   NAME = " << name << endl;
        tokens.push_back(token);
        logins.push_back(name);
        return users[name] = max_id++;
    }
    return -1;
}

User Chat::get_user_by_id(const int id) {
    User user(logins[id - 1]);
    return user;
}

int Chat::get_user_id_by_token(const std::string &token) {
    return ids[token];
}

std::string Chat::get_token(const User& user) {
    string name = user.get_name();
    int id = users[name];
    if (id != 0) {
        return tokens[id - 1];
    }
    return "";
}

std::vector<User> Chat::get_users() {
    std::vector<User> res;
    for(int i = 0; i < (int)logins.size(); i++) {
        int id = users[logins[i]];
        if (!tokens[id - 1].empty()) {
            res.push_back(get_user_by_id(id));
        }
    }
    return res;
}

int Chat::disconnect_user(const User& user) {
    string name = user.get_name();
    int id = users[name];
    if (id != 0) {
        ids[tokens[id - 1]] = 0;
        tokens[id - 1].clear();
        return 0;
    }
    return -1;
}


int Chat::add_message(const Message& message) {
    messages.push_back(message);
    return 0;
}

vector<Message> Chat::get_messages() {
    return messages;
}

string Chat::generate_token(int length) {
    string token = "";
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