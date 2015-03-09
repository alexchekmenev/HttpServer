#include "response.h"

Response::Response(buffer_ptr buffer) {
    this->encoding = "utf-8";
    this->mime_type = "application/json";
    this->headers = std::vector <std::string>();
    this->buffer = buffer;
}
Response::response_ptr Response::set_data(const std::string& data) {
    this->data = data;
    return response_ptr(this);
}
Response::response_ptr Response::add_header(const std::string header) {
    this->headers.push_back(header+"\r\n");
    return response_ptr(this);
}

Response::buffer_ptr Response::to_buffer() {
    std::string result = "HTTP/1.1 200 OK\r\n";
    this->headers.push_back("Content-Type: "+this->mime_type+"; charset="+this->encoding+"\r\n");
    this->headers.push_back("Content-Length: "+std::to_string(this->data.size())+"\r\n\r\n");
    for(int i = 0; i < (int)this->headers.size(); i++) {
        result += this->headers[i];
    }
    this->headers.pop_back();
    this->headers.pop_back();
    result += data;
    buffer->clear();
    buffer->append(result);
    return buffer;
}