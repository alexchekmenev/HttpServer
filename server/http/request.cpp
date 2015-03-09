#include "request.h"

Request::Request(const buffer_ptr buffer) : buffer(buffer) {
    std::vector<std::string> strs;
    int pos, left = 0;
    while((pos = (*buffer).find("\r\n", left)) != -1) {
        std::string tmp = (*buffer).substr(left, pos - left);
        strs.push_back(tmp);
        if (tmp.size() > 0) {
            this->headers.push_back(tmp);
        }
        left = pos + 2;
    }
    strs.push_back((*buffer).substr(left));

    if (strs[0].substr(0, 3) == "GET") {
        this->method = "GET";
        this->data = "";
    } else if (strs[0].substr(0, 4) == "POST") {
        this->method = "POST";
        this->data = strs.back();
    }
    bool question = false;
    for(int i = this->method.size() + 1; strs[0][i] != ' '; i++) {
        if (strs[0][i] == '?') {
            question = true;
            continue;
        }
        if (!question) this->route += strs[0][i];
        else this->data += strs[0][i];
    }

    printf("Request: method=%s, route=%s, data=%s\r\n", this->method.c_str(), this->route.c_str(), this->data.c_str());
}

std::string Request::get_route() {
    return this->route;
}
std::string Request::get_method() {
    return this->method;
}

std::string Request::get_header(const std::string header) {
    for(int i = 0; i < (int)this->headers.size(); i++) {
        if (this->headers[i].find(header) != -1) {
            int pos = header.size() + 2;
            return this->headers[i].substr(pos);
        }
    }
    return "";
}

std::string Request::get_data() {
    return this->data;
}


Request::buffer_ptr Request::get_buffer() {
    return buffer;
}