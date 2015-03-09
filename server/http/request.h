#ifndef REQUEST_H
#define REQUEST_H
#include "../headers.h"

struct Request {
public:
    typedef std::shared_ptr<Request> request_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;

    Request(const buffer_ptr buffer);
    buffer_ptr get_buffer();
    std::string get_method();
    std::string get_route();
    std::string get_header(const std::string header);
    std::string get_data();
private:
    buffer_ptr buffer;
    std::string data;
    std::string route;
    std::string method;
    std::vector<std::string> headers;
};

#endif