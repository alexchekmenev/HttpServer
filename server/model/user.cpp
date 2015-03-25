#include "user.h"

User::User(const std::string &name) : name(name) {}
User::~User() {}

std::string User::to_json() {
    return (std::string)
            "{"+
            "\"name\":\""+name+"\""
            "}";
}

std::string User::get_name() const {
    return name;
}

