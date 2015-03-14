#ifndef RESPONSE_H
#define RESPONSE_H

#include "../headers.h"


struct Response {
public:
    typedef std::shared_ptr<Response> response_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;

    Response(buffer_ptr buffer);
    void add_header(const std::string header);
    void set_data(const std::string& data);
    void set_content_type(const std::string content_type);
    buffer_ptr to_buffer();
private:
    buffer_ptr buffer;
    std::string data;
    std::string content_type;
    std::string encoding;
    std::vector<std::string> headers;
};

#endif