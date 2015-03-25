#include <iostream>
#include "response.h"

Response::Response(buffer_ptr buffer) {
    this->encoding = CHARSET_UTF_8;
    this->content_type = MIME_APPLICATION_JSON;
    this->headers = std::vector <std::string>();
    this->buffer = buffer;
}

void Response::set_content_type(const std::string content_type) {
    this->content_type = content_type;
}
void Response::write(const std::string &data) {
    this->data = data;
}
void Response::add_header(const std::string header) {
    this->headers.push_back(header);
}

Response::buffer_ptr Response::to_buffer() {

    /* building result */
    std::string result = "HTTP/1.1 200 OK\r\n";
    //result += "Content-Type: "+this->content_type+"; charset="+this->encoding+"\r\n";
    result += "Content-Type: "+this->content_type+"\r\n";
    for(int i = 0; i < (int)this->headers.size(); i++) {
        result += this->headers[i] + "\r\n";
    }
    result += "Content-Length: "+std::to_string(this->data.size()) + "\r\n";

    /*for(int i = 0; i < (int)this->data.size(); i++) {
        std::cout << "|"<<data[i]<<"|";
    }
    std::cout << std::endl;*/

    result += "\r\n"+data;
    buffer->clear();
    buffer->append(result);
    return buffer;
}
