#include <sstream>
#include "request.h"

Request::Request(const buffer_ptr buffer) : buffer(buffer) {
    std::vector<std::string> strs;
    int pos, left = 0;
    while((pos = (*buffer).find("\r\n", left)) != -1) {
        std::string tmp = (*buffer).substr(left, pos - left);
        strs.push_back(tmp);
        if (tmp.size() > 0) {
            headers.push_back(tmp);
        }
        left = pos + 2;
    }
    strs.push_back((*buffer).substr(left));

    if (strs[0].substr(0, 3) == "GET") {
        method = "GET";
        data = "";
    } else if (strs[0].substr(0, 4) == "POST") {
        method = "POST";
        data = strs.back();

        std::string tmp = (data.size() >= 2 ? data.substr(1, data.size() - 2) : "");
        std::vector<std::string> elems;
        split(tmp, ',', elems);
        for(int i = 0; i < (int)elems.size(); i++) {
            std::vector<std::string> tuple;
            split(elems[i], ':', tuple);
            if (tuple.size() == 2) {
                if (tuple[0].size() >= 2) {
                    tuple[0] = tuple[0].substr(1, tuple[0].size() - 2);
                }
                if (tuple[1].size() >= 2) {
                    tuple[1] = tuple[1].substr(1, tuple[1].size() - 2);
                }
                this->parameters[tuple[0]] = tuple[1];
            }
        }
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
    if (route.size() > 1 && this->route.back() == '/') {
        this->route.pop_back();
    }

    std::vector<std::string> elems;
    this->split(this->data, '&', elems);
    for(int i = 0; i < (int)elems.size(); i++) {
        std::vector<std::string> tuple;
        this->split(elems[i], '=', tuple);
        if (tuple.size() == 2) {
            //std::cout << tuple[0] << ": " << tuple[1] << std::endl;
            this->parameters[tuple[0]] = tuple[1];
        }
    }
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


/* PRIVATE FUNCTIONS */

std::vector<std::string> Request::split(const std::string s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::string Request::get_parameter(std::string parameter) {
    return this->parameters[parameter];
}
