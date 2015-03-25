#include "message.h"

Message::Message(const std::string &sender, const std::string &data) : sender(sender), data(data) {}
Message::~Message() {}

std::string Message::to_json() {
    return (std::string)
            "{"+
            "\"sender\":\""+sender+"\","
            "\"data\":\""+data+"\""
            "}";
}

