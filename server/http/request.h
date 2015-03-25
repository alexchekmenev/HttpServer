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
    std::string get_parameter(std::string parameter);
private:
    std::vector<std::string> split(const std::string s, char delim, std::vector<std::string> &elems);

    buffer_ptr buffer;
    std::string data;
    std::string route;
    std::string method;
    std::vector<std::string> headers;
    std::map<std::string, std::string> parameters;
};

#endif